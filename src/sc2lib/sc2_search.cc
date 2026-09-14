#include "sc2_search.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <optional>
#include <utility>

#include "sc2api/sc2_data.h"
#include "sc2api/sc2_map_info.h"
#include "sc2api/sc2_typeenums.h"

namespace sc2::search {
namespace {
const float kHeightMergeDelta = 10.0F / 8.0F;
const float kMinOppositeGeyserDistance = 3.0F;
const int kOffsetRange = 7;
const int kTownHallHalfSize = 2;
const size_t kMaxResourcesPerExpansion = 12;

bool UnitHasVespene(const Unit& unit, const UnitTypes& unit_types) {
    const uint32_t id = unit.unit_type;
    return id < unit_types.size() && unit_types[id].has_vespene;
}

bool IsWallMineralType(UNIT_TYPEID type) {
    return type == UNIT_TYPEID::NEUTRAL_MINERALFIELD450 || type == UNIT_TYPEID::MINERALFIELDOPAQUE ||
           type == UNIT_TYPEID::MINERALFIELDOPAQUE900;
}

bool HasExpansionMineral(const Units& minerals) {
    for (const auto* mineral : minerals) {
        if (!IsWallMineralType(mineral->unit_type)) {
            return true;
        }
    }
    return false;
}

Units GatherExpansionResources(const ObservationInterface& observation) {
    const UnitTypes& unit_types = observation.GetUnitTypeData();
    return observation.GetUnits([&](const Unit& unit) {
        const uint32_t id = unit.unit_type;
        if (id >= unit_types.size()) {
            return false;
        }
        const UnitTypeData& data = unit_types[id];
        return data.has_minerals || data.has_vespene;
    });
}

std::vector<Point2D> ExpansionOffsets() {
    // Integer offsets with hypot in (4, 8]. Squaring those bounds (16 and 64)
    // yields the same points; a single radius test is equivalent as hypot or as
    // distance-squared. Cluster() already uses DistanceSquared2D the same way
    // (closest pair vs a threshold). Do not replace the FindExpansionLocation
    // score — sum of Distance2D — with a sum of squares. That is a different
    // objective and can select a different town hall cell.
    std::vector<Point2D> offsets;
    for (int x = -kOffsetRange; x <= kOffsetRange; ++x) {
        for (int y = -kOffsetRange; y <= kOffsetRange; ++y) {
            const float radius = std::hypot(static_cast<float>(x), static_cast<float>(y));
            if (radius > 4.0F && radius <= 8.0F) {
                offsets.emplace_back(static_cast<float>(x), static_cast<float>(y));
            }
        }
    }
    return offsets;
}

bool IsTownHallFootprintPlacable(const PlacementGrid& placement, const Point2D& point) {
    const Point2DI center(point);
    for (int x = -kTownHallHalfSize; x <= kTownHallHalfSize; ++x) {
        for (int y = -kTownHallHalfSize; y <= kTownHallHalfSize; ++y) {
            if (!placement.IsPlacable(Point2DI(center.x + x, center.y + y))) {
                return false;
            }
        }
    }
    return true;
}

std::optional<Point3D> FindExpansionLocation(const Units& resources, const std::vector<Point2D>& offsets,
                                             const PlacementGrid& placement, const UnitTypes& unit_types) {
    if (resources.empty()) {
        return std::nullopt;
    }

    float sum_x = 0.0F;
    float sum_y = 0.0F;
    for (const auto* resource : resources) {
        sum_x += resource->pos.x;
        sum_y += resource->pos.y;
    }
    const auto amount = static_cast<float>(resources.size());
    // Town halls are 5x5, so valid centers sit on .5/.5.
    const float center_x = std::floor(sum_x / amount) + 0.5F;
    const float center_y = std::floor(sum_y / amount) + 0.5F;

    std::optional<Point2D> best;
    float best_score = std::numeric_limits<float>::max();
    for (const auto& offset : offsets) {
        const Point2D point(center_x + offset.x, center_y + offset.y);
        if (!IsTownHallFootprintPlacable(placement, point)) {
            continue;
        }

        bool far_enough = true;
        float score = 0.0F;
        for (const auto* resource : resources) {
            const float distance = Distance2D(point, resource->pos);
            const float min_distance = UnitHasVespene(*resource, unit_types) ? 7.0F : 6.0F;
            if (distance < min_distance) {
                far_enough = false;
                break;
            }
            score += distance;
        }
        if (!far_enough) {
            continue;
        }
        if (score < best_score) {
            best_score = score;
            best = point;
        }
    }

    if (!best) {
        return std::nullopt;
    }
    return Point3D(best->x, best->y, resources.front()->pos.z);
}

bool HasOppositeSideGeyserLayout(const Units& minerals, const Units& geysers) {
    if (geysers.size() != 2 || minerals.size() < 6) {
        return false;
    }

    float max_distance = 0.0F;
    const Unit* mineral_1 = minerals[0];
    const Unit* mineral_2 = minerals[1];
    for (size_t i = 0; i < minerals.size(); ++i) {
        for (size_t j = i + 1; j < minerals.size(); ++j) {
            const float distance = Distance2D(minerals[i]->pos, minerals[j]->pos);
            if (distance > max_distance) {
                max_distance = distance;
                mineral_1 = minerals[i];
                mineral_2 = minerals[j];
            }
        }
    }
    if (max_distance < 4.0F) {
        return false;
    }

    const float dx = mineral_2->pos.x - mineral_1->pos.x;
    const float dy = mineral_2->pos.y - mineral_1->pos.y;
    const float length_sq = dx * dx + dy * dy;
    if (length_sq <= 0.0F) {
        return false;
    }

    const auto side = [&](const Unit& geyser) {
        return dx * (geyser.pos.y - mineral_1->pos.y) - dy * (geyser.pos.x - mineral_1->pos.x);
    };
    const float side_1 = side(*geysers[0]);
    const float side_2 = side(*geysers[1]);
    if (side_1 * side_2 >= 0.0F) {
        return false;
    }

    const float length = std::sqrt(length_sq);
    return std::abs(side_1) / length > kMinOppositeGeyserDistance &&
           std::abs(side_2) / length > kMinOppositeGeyserDistance;
}

void SplitMineralsAndGeysers(const Units& resources, const UnitTypes& unit_types, Units& minerals, Units& geysers) {
    minerals.clear();
    geysers.clear();
    for (const auto* resource : resources) {
        if (UnitHasVespene(*resource, unit_types)) {
            geysers.push_back(resource);
        } else {
            minerals.push_back(resource);
        }
    }
}

std::vector<Units> SplitByTerrainHeight(const Units& group, const HeightMap& height) {
    if (group.size() <= 1) {
        return {group};
    }

    struct OrderedUnit {
        float height;
        Tag tag;
        const Unit* unit;
    };

    std::vector<OrderedUnit> ordered;
    ordered.reserve(group.size());
    for (const auto* unit : group) {
        ordered.push_back(OrderedUnit{height.TerrainHeight(Point2DI(unit->pos)), unit->tag, unit});
    }
    std::sort(ordered.begin(), ordered.end(), [](const OrderedUnit& a, const OrderedUnit& b) {
        if (a.height != b.height) {
            return a.height < b.height;
        }
        return a.tag < b.tag;
    });

    if (ordered.back().height - ordered.front().height <= kHeightMergeDelta) {
        return {group};
    }

    std::vector<Units> result;
    Units current{ordered.front().unit};
    for (size_t i = 1; i < ordered.size(); ++i) {
        if (ordered[i].height - ordered[i - 1].height > kHeightMergeDelta) {
            result.push_back(std::move(current));
            current = Units{ordered[i].unit};
        } else {
            current.push_back(ordered[i].unit);
        }
    }
    result.push_back(std::move(current));
    return result;
}

}  // namespace

std::vector<Units> Cluster(const Units& units, float distance_apart) {
    struct Group {
        Units units;
        Point2D center;
        Tag tie_tag;
    };

    const auto group_less = [](const Group& a, const Group& b) {
        if (a.center.x != b.center.x) {
            return a.center.x < b.center.x;
        }
        if (a.center.y != b.center.y) {
            return a.center.y < b.center.y;
        }
        return a.tie_tag < b.tie_tag;
    };

    std::vector<Group> groups;
    groups.reserve(units.size());
    for (const auto* unit : units) {
        groups.push_back(Group{Units{unit}, Point2D(unit->pos), unit->tag});
    }

    const float max_distance_sq = distance_apart * distance_apart;
    while (groups.size() > 1) {
        std::optional<std::pair<size_t, size_t>> best;
        float best_distance_sq = 0.0F;

        for (size_t i = 0; i < groups.size(); ++i) {
            for (size_t j = i + 1; j < groups.size(); ++j) {
                const float distance_sq = DistanceSquared2D(groups[i].center, groups[j].center);
                if (distance_sq > max_distance_sq) {
                    continue;
                }

                const size_t lo = group_less(groups[i], groups[j]) ? i : j;
                const size_t hi = lo == i ? j : i;
                if (!best || distance_sq < best_distance_sq ||
                    (distance_sq == best_distance_sq &&
                     (group_less(groups[lo], groups[best->first]) || (!group_less(groups[best->first], groups[lo]) &&
                                                                      group_less(groups[hi], groups[best->second]))))) {
                    best = {lo, hi};
                    best_distance_sq = distance_sq;
                }
            }
        }

        if (!best) {
            break;
        }

        const size_t keep = std::min(best->first, best->second);
        const size_t drop = std::max(best->first, best->second);
        auto& a = groups[keep];
        const auto& b = groups[drop];
        const float size_a = static_cast<float>(a.units.size());
        const float size_b = static_cast<float>(b.units.size());
        a.center = (a.center * size_a + b.center * size_b) / (size_a + size_b);
        a.units.insert(a.units.end(), b.units.begin(), b.units.end());
        a.tie_tag = std::min(a.tie_tag, b.tie_tag);
        groups.erase(groups.begin() + static_cast<std::ptrdiff_t>(drop));
    }

    std::vector<Units> result;
    result.reserve(groups.size());
    for (auto& group : groups) {
        result.push_back(std::move(group.units));
    }
    return result;
}

std::vector<Point3D> CalculateExpansionLocations(const ObservationInterface* observation,
                                                 ExpansionParameters parameters) {
    if (!observation) {
        return {};
    }

    const Units resources = GatherExpansionResources(*observation);
    if (resources.empty()) {
        return {};
    }

    const GameInfo& game_info = observation->GetGameInfo();
    if (game_info.placement_grid.width <= 0 || game_info.placement_grid.height <= 0 ||
        game_info.placement_grid.data.empty()) {
        return {};
    }

    const PlacementGrid placement(game_info);
    const HeightMap height(game_info);
    const UnitTypes& unit_types = observation->GetUnitTypeData();
    const std::vector<Point2D> offsets = ExpansionOffsets();
    const std::vector<Units> groups = Cluster(resources, parameters.cluster_distance_);

    std::vector<Point3D> expansion_locations;
    for (const auto& group : groups) {
        for (const auto& height_group : SplitByTerrainHeight(group, height)) {
            if (height_group.size() > kMaxResourcesPerExpansion) {
                continue;
            }

            Units minerals;
            Units geysers;
            SplitMineralsAndGeysers(height_group, unit_types, minerals, geysers);
            if (!HasExpansionMineral(minerals)) {
                continue;
            }

            auto append_location = [&](const Units& local_resources) {
                const auto location = FindExpansionLocation(local_resources, offsets, placement, unit_types);
                if (!location) {
                    return;
                }
                if (parameters.debug_) {
                    parameters.debug_->DebugSphereOut(*location, 0.35F, Colors::Red);
                }
                expansion_locations.push_back(*location);
            };

            if (HasOppositeSideGeyserLayout(minerals, geysers)) {
                for (const auto* geyser : geysers) {
                    Units local = minerals;
                    local.push_back(geyser);
                    append_location(local);
                }
                continue;
            }

            append_location(height_group);
        }
    }
    return expansion_locations;
}

}  // namespace sc2::search
