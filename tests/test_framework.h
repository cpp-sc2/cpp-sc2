#pragma once

#include "sc2api/sc2_coordinator.h"
#include "sc2api/sc2_agent.h"
#include "sc2api/sc2_args.h"

#include <vector>
#include <memory>

namespace sc2 {

struct TestSequence: ClientEvents {
    Agent* agent_;
    uint32_t wait_game_loops_;
    std::vector<std::string> errors_;
    std::string test_name_;

    TestSequence();

    virtual bool DidSucceed() const;

    // Override.
    virtual void OnTestStart() {}
    virtual void OnTestFinish() {}

    // Pushing errors will mark this test as failing.
    virtual void ReportError(const char* error = "Error");

   // Mark test as failed and cleanup environment.
    virtual void ReportErrorAndCleanup(const char* error);

    Point2D GetMapCenter() const;

    void KillAllUnits();
};

struct UnitTestBot: Agent {
    UnitTestBot():
        success_(true),
        current_sequence_(-1),
        game_loop_done_(2) {
    }

    bool IsFinished() const {
        return (current_sequence_ >= sequences_.size() && current_sequence_ != std::size_t(-1));
    }

    bool Success() { return success_; }

 protected:
    template<class T> void Add(const T& test) {
        std::unique_ptr<TestSequence> t = std::make_unique<T>(test);
        t->agent_ = this;
        sequences_.push_back(std::move(t));
    }

    virtual void OnTestsBegin () = 0;
    virtual void OnTestsEnd () = 0;
    virtual void OnPostStep () {}

    void OnError(const std::vector<ClientError>& /*client_errors*/, const std::vector<std::string>& /*protocol_errors*/ = {}) override { success_ = false; }

 private:
    void OnGameStart() final;
    void OnStep() final;
    void OnGameEnd() final;

    // Other forwarded events.
    void OnGameFullStart() final;
    void OnUnitDestroyed(const Unit* unit) final;
    void OnUnitCreated(const Unit* unit) final;
    void OnUnitIdle(const Unit* unit) final;
    void OnUnitEnterVision(const Unit* unit) final;
    void OnUpgradeCompleted(UpgradeID upgrade) final;
    void OnBuildingConstructionComplete(const Unit* unit) final;
    void OnNydusDetected() final;
    void OnNuclearLaunchDetected() final;

    bool success_;
    std::vector<std::unique_ptr<TestSequence>> sequences_;
    std::size_t current_sequence_;
    uint32_t game_loop_done_;
};

//
// Some common sequences.
//
template <int Loops> struct WaitT: TestSequence {
    void OnTestStart() override {
        wait_game_loops_ = Loops;
    }
};

}  // namespace sc2
