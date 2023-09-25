#include "sc2api/sc2_api.h"
#include "sc2utils/sc2_manage_process.h"
#include "sc2api/sc2_typeenums.h"
#include "bot_examples.h"
#include <iostream>
#include <string>

using namespace sc2;

class Bot : public Agent {
private:
    std::unordered_map<int, UnitTypeData> unit_type_data_;
    std::unordered_map<Tag, bool> production_building_status;
    std::unordered_map<int, UnitTypeData> production_buildings;
    std::unordered_map<int, std::string> ability_id_to_name_;
    std::unordered_map<ABILITY_ID, std::string> ability_to_unit = InitializeAbilityIDToUnitNameMapping();


public:

    // Runs once when the game starts
    virtual void OnGameStart() final {

        auto unit_types = Observation()->GetUnitTypeData();
        auto abilities = Observation()->GetAbilityData();

        for (const auto& ability : abilities) {
            ability_id_to_name_[ability.ability_id] = ability.link_name;
        }

        buildingTracking();
        std::cout << "Hello, World!" << std::endl;
    }


    bool IsProductionBuilding(const sc2::UnitTypeID& unit_type) {
        return unit_type == sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_BARRACKS ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_FACTORY ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_STARPORT ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_NEXUS ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_GATEWAY ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_WARPGATE ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_STARGATE ||
            unit_type == sc2::UNIT_TYPEID::ZERG_HATCHERY ||
            unit_type == sc2::UNIT_TYPEID::ZERG_LAIR ||
            unit_type == sc2::UNIT_TYPEID::ZERG_HIVE ||
            unit_type == sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL ||
            unit_type == sc2::UNIT_TYPEID::ZERG_ROACHWARREN ||
            unit_type == sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN ||
            unit_type == sc2::UNIT_TYPEID::ZERG_SPIRE ||
            unit_type == sc2::UNIT_TYPEID::ZERG_GREATERSPIRE ||
            unit_type == sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN ||
            unit_type == sc2::UNIT_TYPEID::ZERG_LURKERDENMP;
    }

    std::unordered_map< sc2::ABILITY_ID, std::string> InitializeAbilityIDToUnitNameMapping() {
        std::unordered_map<sc2::ABILITY_ID, std::string> ability_to_unit;

        // Terran Units
        ability_to_unit[sc2::ABILITY_ID::TRAIN_SCV] = "SCV";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_MARINE] = "Marine";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_MARAUDER] = "Marauder";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_REAPER] = "Reaper";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_GHOST] = "Ghost";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_HELLION] = "Hellion";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_HELLBAT] = "Hellbat";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_SIEGETANK] = "Siege Tank";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_CYCLONE] = "Cyclone";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_THOR] = "Thor";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_VIKINGFIGHTER] = "Viking";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_MEDIVAC] = "Medivac";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_LIBERATOR] = "Liberator";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_RAVEN] = "Raven";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_BANSHEE] = "Banshee";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_BATTLECRUISER] = "Battlecruiser";

        // Protoss Units
        ability_to_unit[sc2::ABILITY_ID::TRAIN_PROBE] = "Probe";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_ZEALOT] = "Zealot";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_STALKER] = "Stalker";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_SENTRY] = "Sentry";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_ADEPT] = "Adept";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_HIGHTEMPLAR] = "High Templar";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_DARKTEMPLAR] = "Dark Templar";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_IMMORTAL] = "Immortal";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_OBSERVER] = "Observer";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_WARPPRISM] = "Warp Prism";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_COLOSSUS] = "Colossus";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_DISRUPTOR] = "Disruptor";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_PHOENIX] = "Phoenix";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_ORACLE] = "Oracle";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_VOIDRAY] = "Void Ray";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_TEMPEST] = "Tempest";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_CARRIER] = "Carrier";

        // Zerg Units
        ability_to_unit[sc2::ABILITY_ID::TRAIN_DRONE] = "Drone";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_ZERGLING] = "Zergling";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_ROACH] = "Roach";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_HYDRALISK] = "Hydralisk";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_INFESTOR] = "Infestor";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_SWARMHOST] = "Swarm Host";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_ULTRALISK] = "Ultralisk";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_OVERLORD] = "Overlord";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_MUTALISK] = "Mutalisk";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_CORRUPTOR] = "Corruptor";
        ability_to_unit[sc2::ABILITY_ID::TRAIN_VIPER] = "Viper";


        return ability_to_unit;
    }

    void unitTracking() {
        Units my_units = Observation()->GetUnits(Unit::Alliance::Self);
        for (const auto& unit : my_units) {
            if (IsProductionBuilding(unit->unit_type)) {
                auto it = unit_type_data_.find(unit->unit_type);

                if (!unit->orders.empty()) {
                    auto ot = ability_to_unit.find(unit->orders[0].ability_id);
                    
                    std::cout << "Production building: " << it->second.name << " is producing a: " << ot->second << std::endl;
                }

            }
        }
    }



    // Return current in game time
    float getCurrentTime() {
        int time = Observation()->GetGameLoop() / 22.4;
        float minutes = time / 60;
        float seconds = (time % 60) * .01;

        return minutes + seconds;
    }


    // Track when buildings are purchased
    void buildingTracking() {
        auto unit_types = Observation()->GetUnitTypeData();
        
        for (const auto unit_type : unit_types) {
            unit_type_data_[unit_type.unit_type_id] = unit_type;
        }
    }

    virtual void OnUnitCreated(const Unit* unit) final {
        auto it = unit_type_data_.find(unit->unit_type);
        std::cout << "Unit Produced: " << it->second.name << std::endl;
    }


    // Runs 22.4 times per in-game second
    virtual void OnStep() final {
        unitTracking();
    }
};

int main(int argc, char* argv[]) {
    Coordinator coordinator;
    coordinator.LoadSettings(argc, argv);

    Bot bot;
    coordinator.SetParticipants({
        CreateParticipant(Race::Terran, &bot),
        CreateComputer(Race::Zerg)
        });

    // Setting game speed
    coordinator.SetRealtime(true); // Grants user control
    coordinator.SetStepSize(1);


    coordinator.LaunchStarcraft();
    coordinator.StartGame(sc2::kMapBelShirVestigeLE);

    while (coordinator.Update()) {
    }

    return 0;
}


