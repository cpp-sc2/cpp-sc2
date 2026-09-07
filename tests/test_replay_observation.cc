#include "test_replay_observation.h"

#include <filesystem>
#include <iostream>
#include <string>

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"

namespace sc2 {

namespace {

const char* kPlayerAlpha = "HelixAlpha";
const char* kPlayerBravo = "HelixBravo";
const char* kChatLine = "cpp-sc2 replay chat probe";
const Point2D kCameraTarget(24.0f, 28.0f);

void Report(std::string* errors, const std::string& message) {
    std::cerr << "TestReplayObservation: " << message << std::endl;
    if (errors->empty()) {
        *errors = message;
    } else {
        *errors += "; " + message;
    }
}

bool HasPlayerNamed(const ReplayInfo& info, const std::string& name, Race expected_race) {
    for (int i = 0; i < info.num_players; ++i) {
        const ReplayPlayerInfo& player = info.players[i];
        if (player.name == name) {
            return player.race == expected_race || player.race_selected == expected_race;
        }
    }
    return false;
}

bool AssertReplayInfoComplete(const ReplayInfo& info, const std::string& replay_path, std::string* errors) {
    bool ok = true;
    if (info.num_players != 2) {
        Report(errors, "expected 2 players, got " + std::to_string(info.num_players));
        ok = false;
    }
    if (info.map_name.empty()) {
        Report(errors, "map_name is empty");
        ok = false;
    }
    if (info.replay_path.empty()) {
        Report(errors, "replay_path is empty");
        ok = false;
    }
    if (info.version.empty()) {
        Report(errors, "version is empty");
        ok = false;
    }
    if (info.data_version.empty()) {
        Report(errors, "data_version is empty");
        ok = false;
    }
    if (info.duration <= 0.0f) {
        Report(errors, "duration is not positive");
        ok = false;
    }
    if (info.duration_gameloops == 0) {
        Report(errors, "duration_gameloops is 0");
        ok = false;
    }
    if (info.data_build == 0) {
        Report(errors, "data_build is 0");
        ok = false;
    }
    if (info.base_build == 0) {
        Report(errors, "base_build is 0");
        ok = false;
    }
    if (!HasPlayerNamed(info, kPlayerAlpha, Race::Terran)) {
        Report(errors, std::string("missing named Terran player ") + kPlayerAlpha);
        ok = false;
    }
    if (!HasPlayerNamed(info, kPlayerBravo, Race::Zerg)) {
        Report(errors, std::string("missing named Zerg player ") + kPlayerBravo);
        ok = false;
    }
    (void)replay_path;
    return ok;
}

class ReplayCaptureBot : public Agent {
public:
    explicit ReplayCaptureBot(std::string path) : replay_path_(std::move(path)) {
    }

    bool saved() const {
        return saved_;
    }

    void OnStep() override {
        const uint32_t loop = Observation()->GetGameLoop();
        if (loop == 2) {
            Actions()->SendChat(kChatLine, ChatChannel::All);
            Debug()->DebugMoveCamera(kCameraTarget);
            Debug()->SendDebug();
        }
        if (loop >= 64 && !saved_) {
            saved_ = Control()->SaveReplay(replay_path_);
        }
    }

private:
    std::string replay_path_;
    bool saved_ = false;
};

class ReplayInfoObserver : public ReplayObserver {
public:
    explicit ReplayInfoObserver(std::string* errors) : errors_(errors) {
    }

    bool info_ok() const {
        return info_ok_;
    }

    bool IgnoreReplay(const ReplayInfo& replay_info, uint32_t) override {
        info_ok_ = AssertReplayInfoComplete(replay_info, replay_info.replay_path, errors_);
        return false;
    }

    void OnStep() override {
        stepped_ = true;
        const auto& chat = Observation()->GetChatMessages();
        if (!chat.empty()) {
            saw_chat_ = true;
            for (const auto& message : chat) {
                if (message.message == kChatLine) {
                    saw_chat_text_ = true;
                }
            }
        } else if (saw_chat_text_) {
            chat_cleared_ = true;
        }
    }

    bool stepped() const {
        return stepped_;
    }
    bool saw_chat_text() const {
        return saw_chat_text_;
    }
    bool chat_cleared() const {
        return chat_cleared_;
    }

private:
    std::string* errors_;
    bool info_ok_ = false;
    bool stepped_ = false;
    bool saw_chat_ = false;
    bool saw_chat_text_ = false;
    bool chat_cleared_ = false;
};

}  // namespace

bool TestReplayObservation(int argc, char** argv) {
    const std::filesystem::path replay_dir = std::filesystem::path(GetLibraryMapsDirectory()) / "ReplayFixtures";
    std::error_code ec;
    std::filesystem::create_directories(replay_dir, ec);
    const std::string replay_path = (replay_dir / "cpp_sc2_fixture.SC2Replay").string();
    std::filesystem::remove(replay_path, ec);

    {
        Coordinator coordinator;
        if (!coordinator.LoadSettings(argc, argv)) {
            std::cerr << "TestReplayObservation: LoadSettings failed" << std::endl;
            return false;
        }
        coordinator.SetTimeoutMS(120000);

        ReplayCaptureBot bot(replay_path);
        coordinator.SetParticipants({
            CreateParticipant(Race::Terran, &bot, kPlayerAlpha),
            CreateComputer(Race::Zerg, Difficulty::Easy, AIBuild::RandomBuild, kPlayerBravo),
        });
        coordinator.LaunchStarcraft();
        if (!coordinator.StartGame(kMapBelShirVestigeLE)) {
            std::cerr << "TestReplayObservation: StartGame failed" << std::endl;
            return false;
        }
        while (coordinator.Update()) {
            SleepFor(20);
            if (bot.saved()) {
                break;
            }
            if (bot.Observation()->GetGameLoop() > 256) {
                break;
            }
        }
        const auto size = std::filesystem::exists(replay_path) ? std::filesystem::file_size(replay_path) : 0;
        if (!bot.saved() || size < 1000) {
            std::cerr << "TestReplayObservation: SaveReplay failed at " << replay_path << " size=" << size
                      << " loop=" << bot.Observation()->GetGameLoop() << std::endl;
            return false;
        }
    }

    std::string errors;
    Coordinator replay_coordinator;
    if (!replay_coordinator.LoadSettings(argc, argv)) {
        std::cerr << "TestReplayObservation: replay LoadSettings failed" << std::endl;
        return false;
    }
    if (!replay_coordinator.SetReplayPath(replay_dir.string())) {
        std::cerr << "TestReplayObservation: SetReplayPath failed" << std::endl;
        return false;
    }

    ReplayInfoObserver observer(&errors);
    replay_coordinator.AddReplayObserver(&observer);
    while (replay_coordinator.Update()) {
    }

    bool success = observer.info_ok() && observer.stepped();
    if (!observer.info_ok()) {
        std::cerr << "TestReplayObservation: ReplayInfo incomplete: " << errors << std::endl;
    }
    if (!observer.stepped()) {
        std::cerr << "TestReplayObservation: ReplayObserver never stepped" << std::endl;
        success = false;
    }
    // Camera and chat assertions land in later topic PRs. This test only
    // requires a complete ReplayInfo including both player names.
    (void)observer.saw_chat_text();
    (void)observer.chat_cleared();
    return success;
}

}  // namespace sc2
