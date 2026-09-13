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

// Calculates expansion locations from the placement/height grids on GameInfo. Call once and cache.
std::vector<Point3D> CalculateExpansionLocations(const ObservationInterface* observation,
                                                 ExpansionParameters parameters = ExpansionParameters());

}  // namespace sc2::search
