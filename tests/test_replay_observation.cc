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
constexpr float kCameraNearSq = 16.0f;

bool CameraNear(const Point2D& a, const Point2D& b) {
    return DistanceSquared2D(a, b) < kCameraNearSq;
}

Point2D Offset(const Point2D& origin, float dx, float dy) {
    return Point2D(origin.x + dx, origin.y + dy);
}

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
    ReplayCaptureBot(std::string path, Point2D* recorded_target)
        : replay_path_(std::move(path)), recorded_target_(recorded_target) {
    }

    bool saved() const {
        return saved_;
    }
    bool saw_camera_event() const {
        return saw_camera_event_;
    }
    bool saw_camera_observation() const {
        return saw_camera_observation_;
    }
    bool camera_near_target() const {
        return camera_near_target_;
    }
    bool camera_pos_near_target() const {
        return camera_pos_near_target_;
    }
    Point2D last_raw_camera() const {
        return last_raw_camera_;
    }
    Point2D last_camera_pos() const {
        return last_camera_pos_;
    }

    void OnCameraMove(const RawCameraMove& move) override {
        saw_camera_event_ = true;
        last_raw_camera_ = Point2D(move.center_world_space);
        if (aimed_ && CameraNear(last_raw_camera_, *recorded_target_)) {
            camera_near_target_ = true;
        }
    }

    void OnStep() override {
        const uint32_t loop = Observation()->GetGameLoop();
        last_camera_pos_ = Observation()->GetCameraPos();
        if (!aimed_) {
            const GameInfo& info = Observation()->GetGameInfo();
            if (info.playable_max.x > info.playable_min.x && info.playable_max.y > info.playable_min.y) {
                *recorded_target_ = (info.playable_max - info.playable_min) * 0.5f + info.playable_min;
                aimed_ = true;
            }
        }
        if (aimed_ && !panned_ && loop >= 2) {
            Actions()->SendChat(kChatLine, ChatChannel::All);
            Debug()->DebugMoveCamera(*recorded_target_);
            Debug()->SendDebug();
            panned_ = true;
        }
        if (!Observation()->GetRawCameraMoves().empty()) {
            saw_camera_observation_ = true;
        }
        if (panned_ && CameraNear(last_camera_pos_, *recorded_target_)) {
            camera_pos_near_target_ = true;
        }
        if (loop >= 64 && !saved_) {
            saved_ = Control()->SaveReplay(replay_path_);
        }
    }

private:
    std::string replay_path_;
    Point2D* recorded_target_;
    Point2D last_raw_camera_;
    Point2D last_camera_pos_;
    bool saved_ = false;
    bool aimed_ = false;
    bool panned_ = false;
    bool saw_camera_event_ = false;
    bool saw_camera_observation_ = false;
    bool camera_near_target_ = false;
    bool camera_pos_near_target_ = false;
};

class ReplayInfoObserver : public ReplayObserver {
public:
    ReplayInfoObserver(std::ostringstream& errors, Point2D recorded_target, Point2D observer_target)
        : errors_(errors), recorded_target_(recorded_target), observer_target_(observer_target) {
    }

    bool info_ok() const {
        return info_ok_;
    }

    bool IgnoreReplay(const ReplayInfo& replay_info, uint32_t) override {
        info_ok_ = AssertReplayInfoComplete(replay_info, errors_);
        return false;
    }

    void OnCameraMove(const RawCameraMove& move) override {
        saw_camera_event_ = true;
        last_raw_camera_ = Point2D(move.center_world_space);
        if (CameraNear(last_raw_camera_, recorded_target_)) {
            recorded_move_near_target_ = true;
        }
        if (CameraNear(last_raw_camera_, observer_target_)) {
            raw_move_looks_like_observer_ = true;
        }
    }

    void OnStep() override {
        stepped_ = true;
        const uint32_t loop = Observation()->GetGameLoop();
        if (!issued_observer_camera_ && loop >= 8) {
            ObserverAction()->CameraMove(observer_target_);
            issued_observer_camera_ = true;
        }
        if (!Observation()->GetRawCameraMoves().empty()) {
            saw_camera_observation_ = true;
        }
        if (CameraNear(Observation()->GetCameraPos(), recorded_target_)) {
            replay_pos_near_recorded_ = true;
        }
    }

    bool stepped() const {
        return stepped_;
    }
    bool saw_camera_event() const {
        return saw_camera_event_;
    }
    bool saw_camera_observation() const {
        return saw_camera_observation_;
    }
    bool recorded_move_near_target() const {
        return recorded_move_near_target_;
    }
    bool raw_move_looks_like_observer() const {
        return raw_move_looks_like_observer_;
    }
    bool replay_pos_near_recorded() const {
        return replay_pos_near_recorded_;
    }
    Point2D last_raw_camera() const {
        return last_raw_camera_;
    }

private:
    std::ostringstream& errors_;
    Point2D recorded_target_;
    Point2D observer_target_;
    Point2D last_raw_camera_;
    bool info_ok_ = false;
    bool stepped_ = false;
    bool saw_camera_event_ = false;
    bool saw_camera_observation_ = false;
    bool recorded_move_near_target_ = false;
    bool raw_move_looks_like_observer_ = false;
    bool issued_observer_camera_ = false;
    bool replay_pos_near_recorded_ = false;
};

}  // namespace

bool TestReplayObservation(int argc, char** argv) {
    const std::filesystem::path replay_dir = std::filesystem::path(GetLibraryMapsDirectory()) / "ReplayFixtures";
    std::error_code ec;
    std::filesystem::create_directories(replay_dir, ec);
    const std::string replay_path = (replay_dir / "cpp_sc2_fixture.SC2Replay").string();
    std::filesystem::remove(replay_path, ec);

    Point2D recorded_target;
    {
        Coordinator coordinator;
        if (!coordinator.LoadSettings(argc, argv)) {
            std::cerr << "TestReplayObservation: LoadSettings failed\n";
            return false;
        }
        coordinator.SetTimeoutMS(120000);

        ReplayCaptureBot bot(replay_path, &recorded_target);
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
        if (!bot.saw_camera_event()) {
            std::cerr << "TestReplayObservation: live OnCameraMove never fired after DebugMoveCamera\n";
            return false;
        }
        if (!bot.saw_camera_observation()) {
            std::cerr << "TestReplayObservation: live GetRawCameraMoves was empty after DebugMoveCamera\n";
            return false;
        }
        if (!bot.camera_near_target()) {
            std::cerr << "TestReplayObservation: live raw camera move not near pan target got ("
                      << bot.last_raw_camera().x << ", " << bot.last_raw_camera().y << ") want (" << recorded_target.x
                      << ", " << recorded_target.y << ")\n";
            return false;
        }
        if (!bot.camera_pos_near_target()) {
            std::cerr << "TestReplayObservation: live GetCameraPos not near pan target got (" << bot.last_camera_pos().x
                      << ", " << bot.last_camera_pos().y << ") want (" << recorded_target.x << ", " << recorded_target.y
                      << ")\n";
            return false;
        }
    }

    const Point2D observer_target = Offset(recorded_target, -35.0f, -35.0f);

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

    ReplayInfoObserver observer(errors, recorded_target, observer_target);
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
    if (!observer.replay_pos_near_recorded()) {
        std::cerr << "TestReplayObservation: replay GetCameraPos never reached the recorded pan (" << recorded_target.x
                  << ", " << recorded_target.y << ")\n";
        success = false;
    }
    if (observer.raw_move_looks_like_observer()) {
        std::cerr << "TestReplayObservation: GetRawCameraMoves contained the spectator ObserverAction pan\n";
        success = false;
    }
    if (!observer.saw_camera_event()) {
        std::cerr << "TestReplayObservation: replay OnCameraMove never fired for the recorded pan\n";
        success = false;
    }
    if (!observer.saw_camera_observation()) {
        std::cerr << "TestReplayObservation: replay GetRawCameraMoves was empty for every step\n";
        success = false;
    }
    if (observer.saw_camera_event() && !observer.recorded_move_near_target()) {
        std::cerr << "TestReplayObservation: replay raw camera move not near recorded pan ("
                  << observer.last_raw_camera().x << ", " << observer.last_raw_camera().y << ")\n";
        success = false;
    }
    return success;
}

}  // namespace sc2
