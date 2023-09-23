#include <sc2api/sc2_api.h>

#include <iostream>

using namespace sc2;

class Bot : public Agent {
private:
    std::unordered_map<int, UnitTypeData> unit_type_data_;

public:
<<<<<<< Updated upstream
    virtual void OnGameStart() final {
        std::cout << "Hello, World!" << std::endl;
    }

    virtual void OnStep() final {
        std::cout << Observation()->GetGameLoop() << std::endl;
=======

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
>>>>>>> Stashed changes
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

    coordinator.LaunchStarcraft();
    coordinator.StartGame(sc2::kMapBelShirVestigeLE);

    while (coordinator.Update()) {
    }

    return 0;
}
