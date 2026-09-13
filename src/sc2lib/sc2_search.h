#pragma once

#include <vector>

#include "sc2api/sc2_common.h"
#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_unit.h"

namespace sc2::search {

// Groups units whose centroids are within distance_apart.
std::vector<Units> Cluster(const Units& units, float distance_apart);

struct ExpansionParameters {
    // Distance used to group mineral/vespene fields into one expansion.
    float cluster_distance_ = 10.5F;

    // If filled out CalculateExpansionLocations will render spheres to show what it calculated.
    DebugInterface* debug_ = nullptr;
};

// Calculates expansion locations from resource units and the placement/height grids on GameInfo.
// Call once and cache.
//
// Resources are units whose catalog UnitTypeData has has_minerals or has_vespene. Contents
// fields are not used (unset on snapshots). Clusters whose minerals are only wall types
// (MineralField450 / opaque) are skipped; a real base keeps at least one full or 750 field,
// and that unit type does not change as the patch is mined.
//
// Remaining clusters are split on terrain-height jumps. Each group of at most 12 resources
// gets a 5x5-placable .5/.5 town hall on an annulus of hypot radius (4, 8] around the
// resource centroid, minimizing the sum of Euclidean distances (min 6 from minerals, 7 from
// geysers). Opposite-side double geyser lines emit two locations (minerals + each geyser).
std::vector<Point3D> CalculateExpansionLocations(const ObservationInterface* observation,
                                                 ExpansionParameters parameters = ExpansionParameters());

}  // namespace sc2::search
