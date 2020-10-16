#include "test_unit_command_common.h"
#include "sc2api/sc2_api.h"
#include "sc2api/sc2_unit_filters.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"
#include "test_observation_interface.h"

#include <iostream>
#include <random>
#include <string>


namespace sc2 {

    class TestGetAbilityData : public TestSequence{
    void OnTestFinish() {
        const ObservationInterface* obs = agent_->Observation();
        AbilityData ability = obs->GetAbilityData().at(static_cast<int>(ABILITY_ID::EFFECT_BLINK_STALKER));
        if (ability.link_name != "Blink") {
            std::string errorString = "Wrong Ability is pulled from function EFFECT_Blink is " + ability.link_name;
            ReportError(errorString.c_str());
        }

        if (ability.ability_id != ABILITY_ID::EFFECT_BLINK_STALKER) {
            ReportError("Wrong AbilityID");
        }

        if (ability.hotkey != "B") {
            std::string errorStr = "Wrong Hotkey " + ability.hotkey;
            ReportError(errorStr.c_str());
        }

        if (ability.is_building) {
            ReportError("is_building is reporting an incorrect value Blink does not create a building");
        }

        if (ability.target != sc2::AbilityData::Target::Point) {
            ReportError("Wrong targetValue");
        }

        if (ability.allow_autocast) {
            ReportError("Blink is not autocast");
        }

        AbilityData building_ability = obs->GetAbilityData().at(static_cast<int>(ABILITY_ID::BUILD_NEXUS));

        if (!building_ability.is_building) {
            ReportError("is_building is reporting an incorrect value BUILD_NEXUS creates a building");
        }
        
        if (building_ability.footprint_radius != 2.5f) {
            ReportError("footprint_radius is incorrect, should be 2.5");
        }

        AbilityData Autocast_ability = obs->GetAbilityData().at(static_cast<int>(ABILITY_ID::EFFECT_REPAIR));
        if (!Autocast_ability.allow_autocast) {
            ReportError("Repair is autocast");
        }

        AbilityData instant_placement_ability = obs->GetAbilityData().at(static_cast<int>(ABILITY_ID::BUILD_TECHLAB));
        if (!instant_placement_ability.is_instant_placement) {
            ReportError("build techlab should be instant placement");
        }

        KillAllUnits();
    }
    };

    class TestGetFoodCount : public TestSequence{
    void OnTestStart() {
        wait_game_loops_ = 10;
        Point2D origin_pt_ = GetMapCenter();
        Point2D offset_ = Point2D(10.0f, 10.0f);
        agent_->Debug()->DebugCreateUnit(UNIT_TYPEID::PROTOSS_ZEALOT, origin_pt_, agent_->Observation()->GetPlayerID(), 10);
        agent_->Debug()->DebugCreateUnit(UNIT_TYPEID::PROTOSS_PROBE, origin_pt_, agent_->Observation()->GetPlayerID(), 10);
        agent_->Debug()->DebugCreateUnit(UNIT_TYPEID::PROTOSS_PYLON, origin_pt_ + offset_, agent_->Observation()->GetPlayerID(), 2);
        agent_->Debug()->DebugCreateUnit(UNIT_TYPEID::PROTOSS_WARPGATE, origin_pt_ + offset_, agent_->Observation()->GetPlayerID(), 1);
        agent_->Debug()->SendDebug();
    }

    void OnTestFinish() {
        const ObservationInterface* obs = agent_->Observation();

        if (obs->GetArmyCount() != 10) {
            ReportError("Army Count is Incorrect");
        }
        if (obs->GetFoodArmy() != 20) {
            ReportError("Army Food is Incorrect");
        }
        if (obs->GetFoodWorkers() != 10) {
            ReportError("Worker Supply is Incorrect");
        }
        if (obs->GetIdleWorkerCount() != 10) {
            ReportError("Idle Worker Count is Incorrect");
        }
        if (obs->GetFoodUsed() != 30) {
            ReportError("Supply Count is Incorrect");
        }
        if (obs->GetFoodCap() != 16) {
            std::string errorStr = "Supply cap is Incorrect the supply is reporting 16 instead of " + std::to_string(obs->GetFoodCap());
            ReportError(errorStr.c_str());
        }
        if (obs->GetWarpGateCount() != 1) {
            ReportError("Warp gate Count is Incorrect");
        }
        if (obs->GetPowerSources().empty()) {
            ReportError("Reporting no Power sources when, there are pylons available.");
        }
        KillAllUnits();
    }
    };

    class TestGetBuffData : public TestSequence {
        void OnTestFinish() {
            const Buffs buffs = agent_->Observation()->GetBuffData();
            BuffData stim = buffs.at(static_cast<uint32_t>(BUFF_ID::STIMPACK));
            if (stim.buff_id != static_cast<uint32_t>(BUFF_ID::STIMPACK)) {
                ReportError("Wrong Buff ID returned");
            }
            if (stim.name != "Stimpack") {
                std::string errorStr = "Wrong Buff Name : " + stim.name;
                ReportError(errorStr.c_str());
            }
        }
    };

    class TestGetResources : public TestSequence {
        void OnTestStart() {
            wait_game_loops_ = 10;
            agent_->Debug()->DebugGiveAllResources();
            agent_->Debug()->SendDebug();
        }
        void OnTestFinish() {
            const ObservationInterface* obs = agent_->Observation();
            if (obs->GetMinerals() != 5000) {
                ReportError("Incorrect Mineral Count");
            }
            if (obs->GetVespene() != 5000) {
                ReportError("Incorrect Vespene Count");
            }
        }
    };

    class TestGetUnitData : public TestSequence {
        void OnTestStart() {
            const ObservationInterface* obs = agent_->Observation();
            const UnitTypes unit_data = obs->GetUnitTypeData();
            UnitTypeData stalker_data = unit_data.at(static_cast<uint32_t>(UNIT_TYPEID::PROTOSS_STALKER));
            UnitTypeData Overlord_data = unit_data.at(static_cast<uint32_t>(UNIT_TYPEID::ZERG_OVERLORDTRANSPORT));
            Point2D origin_pt_ = GetMapCenter();
            agent_->Debug()->DebugCreateUnit(UNIT_TYPEID::PROTOSS_STALKER, origin_pt_, agent_->Observation()->GetPlayerID(), 1);
            agent_->Debug()->SendDebug();

            if (stalker_data.attributes.empty()) {
                std::string errorStr = "UnitTypeData is reporting an no attributes";
                ReportError(errorStr.c_str());
            }
            if (!stalker_data.available) {
                std::string errorStr = "UnitTypeData is reporting stalkers are unavailable";
                ReportError(errorStr.c_str());
            }
            if (stalker_data.cargo_size != 2) {
                std::string errorStr = "UnitTypeData is reporting an incorrect cargo value. Expected : 0 Result : " + std::to_string(stalker_data.cargo_size);
                ReportError(errorStr.c_str());
            }
            if (stalker_data.mineral_cost != 125) {
                std::string errorStr = "UnitTypeData is reporting an incorrect mineral cost value. Expected : 125 Result : " + std::to_string(stalker_data.mineral_cost);
                ReportError(errorStr.c_str());
            }
            if (stalker_data.vespene_cost != 50) {
                std::string errorStr = "UnitTypeData is reporting an incorrect vespene value. Expected : 50 Result : " + std::to_string(stalker_data.vespene_cost);
                ReportError(errorStr.c_str());
            }
            if (stalker_data.name != "Stalker") {
                std::string errorStr = "UnitTypeData is reporting an incorrect name. Expected : Stalker Result : " + stalker_data.name;
                ReportError(errorStr.c_str());
            }
            if (stalker_data.unit_type_id != UNIT_TYPEID::PROTOSS_STALKER) {
                std::string errorStr = "UnitTypeData is reporting an incorrect unittypeID Expected : 74 Result : " + std::to_string(stalker_data.unit_type_id);
                ReportError(errorStr.c_str());
            }
            if (stalker_data.weapons.empty()) {
                std::string errorStr = "UnitTypeData is reporting no weapons";
                ReportError(errorStr.c_str());
            }
            if (!Overlord_data.weapons.empty()) {
                std::string errorStr = "UnitTypeData is reporting weapons for an overlord";
                ReportError(errorStr.c_str());
            }
        }
        
        void OnTestFinish() {
            KillAllUnits();
        }
    };

struct TestGetCloakedEnemyUnit: TestSequence {
    void OnTestStart() {
        wait_game_loops_ = 10;
        Point2D origin_pt_ = GetMapCenter();

        agent_->Debug()->DebugCreateUnit(
            UNIT_TYPEID::PROTOSS_VOIDRAY,
            origin_pt_,
            agent_->Observation()->GetPlayerID(),
            1
        );

        agent_->Debug()->DebugCreateUnit(
            UNIT_TYPEID::PROTOSS_DARKTEMPLAR,
            origin_pt_,
            agent_->Observation()->GetPlayerID() + 1,
            10
        );

        agent_->Debug()->SendDebug();
    }

    void OnTestFinish() {
        const ObservationInterface* obs = agent_->Observation();

        Units found_dark_templars = obs->GetUnits(
            Unit::Alliance::Enemy, IsUnit(UNIT_TYPEID::PROTOSS_DARKTEMPLAR));

        if (found_dark_templars.size() != 10) {
            ReportErrorAndCleanup("Dark Templars Count is Incorrect");
            return;
        }

        if (found_dark_templars.front()->cloak != Unit::CloakState::Cloaked) {
            ReportErrorAndCleanup("Dark Templars Cloak Value is Incorrect");
            return;
        }

        KillAllUnits();
    }
};

struct TestUnitUpgradesLevel: TestSequence {
    void OnTestStart() {
        wait_game_loops_ = 10;
        Point2D origin_pt_ = GetMapCenter();

        agent_->Debug()->DebugCreateUnit(
            UNIT_TYPEID::PROTOSS_ZEALOT,
            origin_pt_,
            agent_->Observation()->GetPlayerID(),
            1
        );
        agent_->Debug()->DebugGiveAllUpgrades();

        agent_->Debug()->SendDebug();
    }

    void OnTestFinish() {
        const ObservationInterface* obs = agent_->Observation();

        Units found_zealots = obs->GetUnits(
            Unit::Alliance::Self, IsUnit(UNIT_TYPEID::PROTOSS_ZEALOT));

        if (found_zealots.size() != 1) {
            ReportErrorAndCleanup("Zealots Count is Incorrect");
            return;
        }

        if (found_zealots.front()->attack_upgrade_level != 2) {
            ReportErrorAndCleanup("Zealots Attack Upgrades Level is Incorrect");
            return;
        }

        if (found_zealots.front()->armor_upgrade_level != 2) {
            ReportErrorAndCleanup("Zealots Armor Upgrades Level is Incorrect");
            return;
        }

        if (found_zealots.front()->shield_upgrade_level != 2) {
            ReportErrorAndCleanup("Zealots Shield Upgrades Level is Incorrect");
            return;
        }

        KillAllUnits();
    }
};

struct TestUnitHallucinationAttribute: TestSequence {
    TestUnitHallucinationAttribute(): TestSequence(), test_unit_(nullptr) {
    }

    void OnTestStart() override {
        wait_game_loops_ = 10;
        Point2D origin_pt_ = GetMapCenter();

        agent_->Debug()->DebugCreateUnit(
            UNIT_TYPEID::PROTOSS_SENTRY,
            origin_pt_,
            agent_->Observation()->GetPlayerID(),
            1
        );

        agent_->Debug()->SendDebug();
    }

    void OnStep() override {
        const ObservationInterface* obs = agent_->Observation();

        if (!test_unit_) {
            sc2::Units found_sentries = obs->GetUnits(
                Unit::Alliance::Self, IsUnit(UNIT_TYPEID::PROTOSS_SENTRY));

            if (found_sentries.empty())
                return;

            test_unit_ = found_sentries.front();

            agent_->Debug()->DebugSetEnergy(75.0f, test_unit_);
            agent_->Debug()->SendDebug();
            return;
        }

        if (test_unit_ && test_unit_->energy >= 75.0f)
            agent_->Actions()->UnitCommand(test_unit_, ABILITY_ID::HALLUCINATION_PHOENIX);
    }

    void OnTestFinish() override{
        const ObservationInterface* obs = agent_->Observation();

        if (!test_unit_) {
            ReportErrorAndCleanup("Sentry not found");
            return;
        }

        if (test_unit_->is_hallucination) {
            ReportErrorAndCleanup("A unit is erroneously marked as hallucination");
            return;
        }

        sc2::Units found_phoenixes = obs->GetUnits(
            Unit::Alliance::Self, IsUnit(UNIT_TYPEID::PROTOSS_PHOENIX));

        if (found_phoenixes.size() != 1) {
            ReportErrorAndCleanup("Illusion of phoenix not found");
            return;
        }

        if (!found_phoenixes.front()->is_hallucination) {
            ReportErrorAndCleanup("An illusion is not marked as hallucination");
            return;
        }

        KillAllUnits();
    }

 private:
    const sc2::Unit* test_unit_;
};

//
// TestObservationBot
//

class TestObservationBot : public UnitTestBot {
public:
    TestObservationBot();

private:
    void OnTestsBegin () final;
    void OnTestsEnd () final;
};

TestObservationBot::TestObservationBot() :
    UnitTestBot() {
    // Sequences.
    Add(TestGetUnitData());
    Add(TestGetAbilityData());
    Add(TestGetFoodCount());
    Add(TestGetBuffData());
    Add(TestGetResources());
    Add(TestGetCloakedEnemyUnit());
    Add(TestUnitUpgradesLevel());
    Add(TestUnitHallucinationAttribute());
}

void TestObservationBot::OnTestsBegin() {
    Debug()->DebugGiveAllUpgrades();
};

void TestObservationBot::OnTestsEnd () {

}

//
// TestUnitCommand
//

bool TestObservationInterface(int argc, char** argv) {
    Coordinator coordinator;
    if (!coordinator.LoadSettings(argc, argv)) {
        return false;
    }

    // Add the custom bot, it will control the players.
    TestObservationBot bot;

    coordinator.SetParticipants({
        CreateParticipant(sc2::Race::Terran, &bot),
    });

    // Start the game.
    coordinator.LaunchStarcraft();
    coordinator.StartGame(sc2::kMapEmpty);

    // Step forward the game simulation.
    while (!bot.IsFinished()) {
        coordinator.Update();
    }

    return bot.Success();
}

}
