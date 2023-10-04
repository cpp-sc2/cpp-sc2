#include "sc2api/sc2_api.h"
#include "sc2utils/sc2_manage_process.h"
#include "sc2api/sc2_typeenums.h"
#include "bot_examples.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace sc2;

class Bot : public Agent {
private:
    std::unordered_map<int, UnitTypeData> unit_type_data_;
    std::unordered_map<Tag, bool> production_building_status;
    std::unordered_map<int, UnitTypeData> production_buildings;
    std::unordered_map<int, std::string> ability_id_to_name_;
    std::unordered_map<ABILITY_ID, std::string> ability_to_unit = InitializeAbilityIDToUnitNameMapping();
    std::unordered_map<ABILITY_ID, std::string> ability_to_upgrade = InitializeUpgradeMapping();
    std::ofstream outFile;


public:

    // Maps all army units IDs to their correct names
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

    // Maps all upgrade IDs to their corect names
    std::unordered_map<sc2::ABILITY_ID, std::string> InitializeUpgradeMapping() {
        std::unordered_map<sc2::ABILITY_ID, std::string> upgrade_mapping;

        // Protoss Upgrades
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_WARPGATE] = "Warp Gate";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL1] = "Protoss Air Weapons Level 1";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL2] = "Protoss Air Weapons Level 2";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSAIRWEAPONSLEVEL3] = "Protoss Air Weapons Level 3";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1] = "Protoss Ground Weapons Level 1";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2] = "Protoss Ground Weapons Level 2";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3] = "Protoss Ground Weapons Level 3";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1] = "Protoss Shields Level 1";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2] = "Protoss Shields Level 2";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3] = "Protoss Shields Level 3";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_CHARGE] = "Charge";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_BLINK] = "Blink";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ADEPTRESONATINGGLAIVES] = "Resonating Glaives";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PSISTORM] = "Psionic Storm";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_GRAVITICBOOSTER] = "Gravitic Boosters";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_GRAVITICDRIVE] = "Gravitic Drive";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_EXTENDEDTHERMALLANCE] = "Extended Thermal Lance";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_SHADOWSTRIKE] = "Shadow Stride";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PHOENIXANIONPULSECRYSTALS] = "Anion Pulse-Crystals";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_VOIDRAYSPEEDUPGRADE] = "Flux Vanes";
        // Add more Protoss upgrades "Tetonic Destabilizers" here when you have their Ability IDs

        // Terran Upgrades
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_STIMPACK] = "Stimpack";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_COMBATSHIELD] = "Combat Shield";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_CONCUSSIVESHELLS] = "Concussive Shells";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONS] = "Terran Infantry Weapons";
        upgrade_mapping[sc2::ABILITY_ID::MORPH_ORBITALCOMMAND] = "Orbital Command";
        upgrade_mapping[sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS] = "Planetary Fortress";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_NEOSTEELFRAME] = "Neosteel Armor";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_HISECAUTOTRACKING] = "Hi-sec Auto Tracking";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_SMARTSERVOS] = "Smart Servos";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_BATTLECRUISERWEAPONREFIT] = "Weapon Refit";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_RAPIDREIGNITIONSYSTEM] = "Rapid Reignition System";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ADVANCEDBALLISTICS] = "Advanced Ballistics";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_BANSHEECLOAKINGFIELD] = "Cloaking Field";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_BANSHEEHYPERFLIGHTROTORS] = "Hyperflight Rotors";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PERSONALCLOAKING] = "Personal Cloaking";

        // Zerg Upgrades
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL1] = "Zerg Melee Weapons Level 1";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL2] = "Zerg Melee Weapons Level 2";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL3] = "Zerg Melee Weapons Level 3";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ZERGLINGMETABOLICBOOST] = "Zergling Metabolic Boost";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ZERGLINGADRENALGLANDS] = "Zergling Adrenal Glands";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_CENTRIFUGALHOOKS] = "Centrifugal Hooks";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PNEUMATIZEDCARAPACE] = "Pneumatized Carapace";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_BURROW] = "Burrow";
        upgrade_mapping[sc2::ABILITY_ID::MORPH_LAIR] = "Lair";
        upgrade_mapping[sc2::ABILITY_ID::MORPH_HIVE] = "Hive";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_GLIALREGENERATION] = "Glial Regeneration";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_TUNNELINGCLAWS] = "Tunneling Claws";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_PATHOGENGLANDS] = "Pathogen Glands";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_NEURALPARASITE] = "Neural Parasite";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_GROOVEDSPINES] = "Grooved Spines";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_MUSCULARAUGMENTS] = "Muscular Augments";
        upgrade_mapping[sc2::ABILITY_ID::MORPH_GREATERSPIRE] = "Greater Spire";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ADAPTIVETALONS] = "Adaptive Talons";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_LURKERRANGE] = "Seismic Spines";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_CHITINOUSPLATING] = "Chitinous Plating";
        upgrade_mapping[sc2::ABILITY_ID::RESEARCH_ANABOLICSYNTHESIS] = "Anabolic Synthesis";

        return upgrade_mapping;
    }

    // Checks to see if the unit is a production building
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
            unit_type == sc2::UNIT_TYPEID::PROTOSS_STARGATE;
    }

    // Checks to see if the unit is an upgrade building
    bool IsUpgradeBuilding(const sc2::UnitTypeID& unit_type) {
        return
            // Terran upgrade buildings
            unit_type == sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_ARMORY ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_FUSIONCORE ||
            unit_type == sc2::UNIT_TYPEID::TERRAN_TECHLAB ||

            // Protoss upgrade buildings
            unit_type == sc2::UNIT_TYPEID::PROTOSS_FORGE ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY ||
            unit_type == sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON ||

            // Zerg upgrade buildings
            unit_type == sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER ||
            unit_type == sc2::UNIT_TYPEID::ZERG_SPIRE ||
            unit_type == sc2::UNIT_TYPEID::ZERG_GREATERSPIRE ||
            unit_type == sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN ||
            unit_type == sc2::UNIT_TYPEID::ZERG_LURKERDENMP ||
            unit_type == sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT ||
            unit_type == sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN ||
            unit_type == sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL ||
            unit_type == sc2::UNIT_TYPEID::ZERG_ROACHWARREN ||
            unit_type == sc2::UNIT_TYPEID::ZERG_BANELINGNEST ||
            unit_type == sc2::UNIT_TYPEID::ZERG_HATCHERY ||
            unit_type == sc2::UNIT_TYPEID::ZERG_LAIR ||
            unit_type == sc2::UNIT_TYPEID::ZERG_HIVE;
    }

    // Returns what unit is currently being built out of a production building
    std::string unitTracking() {

        Units my_units = Observation()->GetUnits(Unit::Alliance::Self);
        for (const auto& unit : my_units) {
            if (IsProductionBuilding(unit->unit_type)) {
                auto it = unit_type_data_.find(unit->unit_type);
                if (!unit->orders.empty()) {               
                    auto ot = ability_to_unit.find(unit->orders[0].ability_id);
                    return ot->second;
                }

            }
        }
        return "empty";
    }

    // Tracks what upgrade is currently built out of a production building
    std::string upgradeTracking() {
        Units my_units = Observation()->GetUnits(Unit::Alliance::Self);
        for (const auto& unit : my_units) {
            if (IsUpgradeBuilding(unit->unit_type)) {
                auto it = unit_type_data_.find(unit->unit_type);
                if (!unit->orders.empty()) {
                    auto ot = ability_to_upgrade.find(unit->orders[0].ability_id);
                    return ot->second;
                }

            }
        }
        return "empty";
;
    }

    // Name needs updating
    void buildingTracking() {
        auto unit_types = Observation()->GetUnitTypeData();
        
        for (const auto unit_type : unit_types) {
            unit_type_data_[unit_type.unit_type_id] = unit_type;
        }
    }

    // Return current in game time
    float getCurrentTime() {
        int time = Observation()->GetGameLoop() / 22.4;
        float minutes = time / 60;
        float seconds = (time % 60) * .01;

        return minutes + seconds;
    }

    // Runs whenever a unit is being created
    virtual void OnUnitCreated(const Unit* unit) final {
        auto it = unit_type_data_.find(unit->unit_type);
        // Tracks when non-army units are created
        if (IsProductionBuilding(unit->unit_type) || IsUpgradeBuilding(unit->unit_type)) {
            outFile << it->second.name << "," << getCurrentTime() << std::endl;
        }


    }

    // Runs 22.4 times per in-game second
    virtual void OnStep() final {
        std::string unit = unitTracking();
        float time = getCurrentTime();

        if (unit != "empty") {
            outFile << unit << "," << time << std::endl;
        }

        if (unit != "empty") {
            outFile << unit << "," << time << std::endl;
        }
    }

    // Runs once when the game starts
    virtual void OnGameStart() final {

        auto unit_types = Observation()->GetUnitTypeData();
        auto abilities = Observation()->GetAbilityData();
        for (const auto& ability : abilities) {
            ability_id_to_name_[ability.ability_id] = ability.link_name;
        }
        buildingTracking();


        outFile.open("output.csv");
        if (!outFile.is_open()) {
            std::cerr << "Failed to open the file for writing!" << std::endl;
        }
        outFile << "Item,Time\n";


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


