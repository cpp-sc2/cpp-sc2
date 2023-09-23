#include "sc2api/sc2_api.h"
#include "sc2utils/sc2_manage_process.h"

#include "bot_examples.h"

#include <iostream>
#include <string>
//
//int main(int argc, char* argv[]) {
//    sc2::Coordinator coordinator;
//
//
//
//    if (!coordinator.LoadSettings(argc, argv)) {
//        return 1;
//    }
//
//    coordinator.SetMultithreaded(true);
//    // Add the custom bot, it will control the players.
//    sc2::ProtossMultiplayerBot bot1;
//    sc2::ZergMultiplayerBot bot2;
//    sc2::TerranMultiplayerBot bot3;
//
//    coordinator.SetParticipants({
//        CreateParticipant(sc2::Race::Protoss, &bot1),
//        CreateComputer(sc2::Race::Terran,sc2::Difficulty::Hard)
//        });
//
//    coordinator.SetRealtime(true);
//    coordinator.SetStepSize(1);
//    // Start the game.
//    coordinator.LaunchStarcraft();
//    bool do_break = false;
//
//    for (; !do_break;) {
//        coordinator.StartGame(sc2::kMapBelShirVestigeLE);
//        //bot1.air_build_ = !bot1.air_build_;
//        bot1.air_build_ = false;
//        bot2.mutalisk_build_ = false;
//
//        while (coordinator.Update() && !do_break) {
//            if (sc2::PollKeyPress()) {
//                do_break = true;
//            }
//        }
//    }
//    bot1.Control()->DumpProtoUsage();
//    bot2.Control()->DumpProtoUsage();
//    return 0;
//}

using namespace sc2;

class Bot : public Agent {
private:
    std::unordered_map<int, UnitTypeData> unit_type_data_;

public:

    // Runs once when the game starts
    virtual void OnGameStart() final {
        auto unit_types = Observation()->GetUnitTypeData();
        for (const auto unit_type : unit_types) {
            unit_type_data_[unit_type.unit_type_id] = unit_type;
        }
        std::cout << "Hello, World!" << std::endl;
    }

    // Return current in game time
    float getCurrentTime() {
        int time = Observation()->GetGameLoop() / 22.4;
        float minutes = time / 60;
        float seconds = (time % 60) * .01;

        return minutes + seconds;
    }

    virtual void OnUnitCreated(const Unit* unit) final {

        auto it = unit_type_data_.find(unit->unit_type);
        std::cout << "Unit Produced: " << it->second.name << std::endl;
    }


    // Runs 22.4 times per in-game second
    virtual void OnStep() final {
        if (Observation()->GetMinerals() == 1000) {
            std::cout << getCurrentTime() << std::endl;
            
        }
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


