#pragma once

#include <vector>

#include "sc2api/sc2_common.h"
#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_unit.h"

namespace sc2::search {

// Clusters units within some distance of each other and returns a list of them and their center of mass.
std::vector<std::pair<Point3D, std::vector<Unit> > > Cluster(const Units& units, float distance_apart);

struct ExpansionParameters {
    // By default we use values that generally work but may require tuning for certain maps.

    // The various radius to check at from the center of an expansion.
    std::vector<float> radiuses_ = {6.4F, 5.3F};

    // With what granularity to step the circumference of the circle.
    float circle_step_size_ = 0.5F;

    // With what distance to cluster mineral/vespene in, this will be used for center of mass calulcation.
    float cluster_distance_ = 15.0F;

    // If filled out CalculateExpansionLocations will render spheres to show what it calculated.
    DebugInterface* debug_ = nullptr;
};

// Calculates expansion locations, this call can take on the order of 100ms since it makes blocking queries to SC2 so
// call it once and cache the reults.
std::vector<Point3D> CalculateExpansionLocations(const ObservationInterface* observation, QueryInterface* query,
                                                 ExpansionParameters parameters = ExpansionParameters());

}  // namespace sc2::search
