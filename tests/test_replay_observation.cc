#include "test_replay_observation.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"

namespace sc2 {

namespace {

constexpr const char kPlayerAlpha[] = "HelixAlpha";
constexpr const char kPlayerBravo[] = "HelixBravo";
constexpr const char kChatLine[] = "cpp-sc2 replay chat probe";
const Point2D kCameraTarget(24.0f, 28.0f);

void Report(std::ostringstream& errors, std::string_view message) {
    std::cerr << "TestReplayObservation: " << message << '\n';

    if (errors.tellp() > 0) {
        errors << "; ";
    }

    errors << message;
}

bool HasPlayerNamed(const ReplayInfo& info, const std::string& name, Race expected_race) {
    const auto begin = info.players;
    const auto end = info.players + info.num_players;
    const auto it = std::find_if(begin, end, [&name](const ReplayPlayerInfo& player) { return player.name == name; });
    return it != end && (it->race == expected_race || it->race_selected == expected_race);
}

bool AssertReplayInfoComplete(const ReplayInfo& info, std::ostringstream& errors) {
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
    explicit ReplayInfoObserver(std::ostringstream& errors) : errors_(errors) {
    }

    bool info_ok() const {
        return info_ok_;
    }

    bool IgnoreReplay(const ReplayInfo& replay_info, uint32_t) override {
        info_ok_ = AssertReplayInfoComplete(replay_info, errors_);
        return false;
    }

    void OnStep() override {
        stepped_ = true;
    }

    bool stepped() const {
        return stepped_;
    }

private:
    std::ostringstream& errors_;
    bool info_ok_ = false;
    bool stepped_ = false;
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
            std::cerr << "TestReplayObservation: LoadSettings failed\n";
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
            std::cerr << "TestReplayObservation: StartGame failed\n";
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
                      << " loop=" << bot.Observation()->GetGameLoop() << '\n';
            return false;
        }
    }

    std::ostringstream errors;
    Coordinator replay_coordinator;
    if (!replay_coordinator.LoadSettings(argc, argv)) {
        std::cerr << "TestReplayObservation: replay LoadSettings failed\n";
        return false;
    }
    if (!replay_coordinator.SetReplayPath(replay_dir.string())) {
        std::cerr << "TestReplayObservation: SetReplayPath failed\n";
        return false;
    }

    ReplayInfoObserver observer(errors);
    replay_coordinator.AddReplayObserver(&observer);
    while (replay_coordinator.Update()) {
    }

    bool success = observer.info_ok() && observer.stepped();
    if (!observer.info_ok()) {
        std::cerr << "TestReplayObservation: ReplayInfo incomplete: " << errors.str() << '\n';
    }
    if (!observer.stepped()) {
        std::cerr << "TestReplayObservation: ReplayObserver never stepped\n";
        success = false;
    }
    return success;
}

}  // namespace sc2
