#include <doctest/doctest.h>

#include "s2clientprotocol/sc2api.pb.h"
#include "sc2api/sc2_score.h"

namespace sc2 {
bool Convert(const SC2APIProtocol::VitalScoreDetails& details_proto, VitalScoreDetails& vital_score_details);
}  // namespace sc2

TEST_CASE("Convert(VitalScoreDetails) populates life/shields/energy") {
    SC2APIProtocol::VitalScoreDetails proto;
    proto.set_life(100.5f);
    proto.set_shields(50.25f);
    proto.set_energy(25.0f);

    sc2::VitalScoreDetails pod;
    REQUIRE(sc2::Convert(proto, pod));

    CHECK(pod.life == doctest::Approx(100.5f));
    CHECK(pod.shields == doctest::Approx(50.25f));
    CHECK(pod.energy == doctest::Approx(25.0f));
}

TEST_CASE("ScoreDetails.collected_vespene is a writable member with default 0") {
    sc2::ScoreDetails sd;
    CHECK(sd.collected_vespene == doctest::Approx(0.0f));

    sd.collected_vespene = 12345.0f;
    CHECK(sd.collected_vespene == doctest::Approx(12345.0f));
}
