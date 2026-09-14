#include "test_expansion_locations.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "test_framework.h"

namespace sc2 {
namespace {
const float kStartMatchDistance = 2.0F;
const float kCentroidMatchDistance = 2.0F;
const int kNeighborhoodRange = 2;
const int kTimingRuns = 5;
const size_t kExpectedBelShirExpansions = 10;
const AbilityID kTownHallAbility = ABILITY_ID::BUILD_COMMANDCENTER;

std::vector<Point2D> OfficialStartLocations(const ObservationInterface& observation) {
    std::vector<Point2D> starts;
    starts.push_back(observation.GetStartLocation());
    for (const auto& point : observation.GetGameInfo().enemy_start_locations) {
        bool duplicate = false;
        for (const auto& existing : starts) {
            if (Distance2D(existing, point) < 1.0F) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            starts.push_back(point);
        }
    }
    return starts;
}

bool HasNearbyExpansion(const Point2D& start, const std::vector<Point3D>& expansions, float max_distance) {
    for (const auto& expansion : expansions) {
        if (Distance2D(start, Point2D(expansion)) <= max_distance) {
            return true;
        }
    }
    return false;
}

bool IsNearAny(const Point2D& point, const std::vector<Point2D>& locations, float max_distance) {
    for (const auto& location : locations) {
        if (Distance2D(point, location) <= max_distance) {
            return true;
        }
    }
    return false;
}

std::vector<Point2D> Neighborhood(const Point2D& center, int range) {
    std::vector<Point2D> points;
    for (int x = -range; x <= range; ++x) {
        for (int y = -range; y <= range; ++y) {
            points.emplace_back(center.x + static_cast<float>(x), center.y + static_cast<float>(y));
        }
    }
    return points;
}

std::vector<Point3D> TimeExpansionLocations(const ObservationInterface& observation, std::vector<double>& times_ms) {
    times_ms.clear();
    times_ms.reserve(static_cast<size_t>(kTimingRuns));
    std::vector<Point3D> expansions;
    for (int i = 0; i < kTimingRuns; ++i) {
        const auto start = std::chrono::steady_clock::now();
        expansions = search::CalculateExpansionLocations(&observation);
        const auto end = std::chrono::steady_clock::now();
        times_ms.push_back(std::chrono::duration<double, std::milli>(end - start).count());
    }
    return expansions;
}

void PrintExpansionTiming(const std::vector<Point3D>& expansions, const std::vector<double>& times_ms) {
    double sum_ms = 0.0;
    double min_ms = times_ms.front();
    double max_ms = times_ms.front();
    for (double t : times_ms) {
        sum_ms += t;
        min_ms = std::min(min_ms, t);
        max_ms = std::max(max_ms, t);
    }
    const double mean_ms = sum_ms / static_cast<double>(times_ms.size());

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "[expansion-locations] " << kMapBelShirVestigeLE << '\n';
    std::cout << "[expansion-locations] count: " << expansions.size() << '\n';
    std::cout << "[expansion-locations] times_ms:";
    for (double t : times_ms) {
        std::cout << ' ' << t;
    }
    std::cout << '\n';
    std::cout << "[expansion-locations] mean_ms: " << mean_ms << " min_ms: " << min_ms << " max_ms: " << max_ms << '\n';
}

void CheckStartLocations(TestSequence& test, const ObservationInterface& observation,
                         const std::vector<Point3D>& expansions) {
    const std::vector<Point2D> starts = OfficialStartLocations(observation);
    if (starts.empty()) {
        test.ReportError("No official start locations on Bel'Shir");
        return;
    }

    for (const auto& start : starts) {
        if (!HasNearbyExpansion(start, expansions, kStartMatchDistance)) {
            test.ReportError(("No expansion within " + std::to_string(kStartMatchDistance) + " of start location (" +
                              std::to_string(start.x) + ", " + std::to_string(start.y) + ")")
                                 .c_str());
        }
    }
}

void CheckUnoccupiedPlacement(TestSequence& test, QueryInterface& query, const std::vector<Point2D>& starts,
                              const std::vector<Point3D>& expansions) {
    std::vector<QueryInterface::PlacementQuery> queries;
    std::vector<size_t> expansion_index;
    std::vector<size_t> expansion_query_begin;
    for (size_t e = 0; e < expansions.size(); ++e) {
        const Point2D center(expansions[e]);
        if (IsNearAny(center, starts, kStartMatchDistance)) {
            continue;
        }
        expansion_index.push_back(e);
        expansion_query_begin.push_back(queries.size());
        for (const auto& point : Neighborhood(center, kNeighborhoodRange)) {
            queries.emplace_back(kTownHallAbility, point);
        }
    }

    if (queries.empty()) {
        test.ReportError("No unoccupied expansions to Query Placement");
        return;
    }

    const std::vector<bool> results = query.Placement(queries);
    const size_t neighborhood_size =
        static_cast<size_t>(2 * kNeighborhoodRange + 1) * static_cast<size_t>(2 * kNeighborhoodRange + 1);
    const size_t center_offset =
        static_cast<size_t>(kNeighborhoodRange * (2 * kNeighborhoodRange + 1) + kNeighborhoodRange);

    for (size_t i = 0; i < expansion_index.size(); ++i) {
        const size_t begin = expansion_query_begin[i];
        const Point2D center(expansions[expansion_index[i]]);
        if (begin + center_offset >= results.size()) {
            test.ReportError("Placement query results shorter than expected");
            continue;
        }

        float sum_x = 0.0F;
        float sum_y = 0.0F;
        int placeable = 0;
        for (size_t q = 0; q < neighborhood_size; ++q) {
            if (!results[begin + q]) {
                continue;
            }
            sum_x += queries[begin + q].target_pos.x;
            sum_y += queries[begin + q].target_pos.y;
            ++placeable;
        }

        if (placeable == 0) {
            continue;
        }

        if (!results[begin + center_offset]) {
            test.ReportError(("Query Placement failed at expansion (" + std::to_string(center.x) + ", " +
                              std::to_string(center.y) + ") but a neighboring cell is placeable")
                                 .c_str());
            continue;
        }

        const Point2D centroid(sum_x / static_cast<float>(placeable), sum_y / static_cast<float>(placeable));
        const float distance = Distance2D(center, centroid);
        if (distance > kCentroidMatchDistance) {
            test.ReportError(("Expansion (" + std::to_string(center.x) + ", " + std::to_string(center.y) +
                              ") is not the local best placement; neighborhood centroid is " +
                              std::to_string(distance) + " away")
                                 .c_str());
        }
    }
}

}  // namespace

class TestBelShirExpansionLocations : public TestSequence {
    void OnTestStart() override {
        wait_game_loops_ = 1;
        const ObservationInterface* obs = agent_->Observation();

        std::vector<double> times_ms;
        const std::vector<Point3D> expansions = TimeExpansionLocations(*obs, times_ms);
        PrintExpansionTiming(expansions, times_ms);

        if (expansions.size() != kExpectedBelShirExpansions) {
            ReportError(("Expected " + std::to_string(kExpectedBelShirExpansions) + " expansions, found " +
                         std::to_string(expansions.size()))
                            .c_str());
        }

        const std::vector<Point2D> starts = OfficialStartLocations(*obs);
        CheckStartLocations(*this, *obs, expansions);
        CheckUnoccupiedPlacement(*this, *agent_->Query(), starts, expansions);
    }
};

class TestExpansionLocationsBot : public UnitTestBot {
public:
    TestExpansionLocationsBot() {
        Add(TestBelShirExpansionLocations());
    }

private:
    void OnTestsBegin() final {
        Debug()->DebugEnemyControl();
        Debug()->SendDebug();
    }
    void OnTestsEnd() final {
    }
};

bool TestExpansionLocations(int argc, char** argv) {
    Coordinator coordinator;
    if (!coordinator.LoadSettings(argc, argv)) {
        return false;
    }

    TestExpansionLocationsBot bot;
    coordinator.SetParticipants({
        CreateParticipant(Race::Terran, &bot),
        CreateComputer(Race::Terran),
    });

    coordinator.LaunchStarcraft();
    coordinator.StartGame(kMapBelShirVestigeLE);

    while (!bot.IsFinished()) {
        coordinator.Update();
    }

    return bot.Success();
}

}  // namespace sc2
