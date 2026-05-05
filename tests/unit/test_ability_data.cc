#include <doctest/doctest.h>

#include "s2clientprotocol/sc2api.pb.h"
#include "sc2api/sc2_data.h"

TEST_CASE("AbilityData.is_instant_placement reads the value, not has_X") {
    SC2APIProtocol::AbilityData proto;
    proto.set_ability_id(123);
    proto.set_is_instant_placement(true);

    sc2::AbilityData pod;
    pod.ReadFromProto(proto);

    CHECK(pod.is_instant_placement == true);
}

TEST_CASE("AbilityData.is_instant_placement is false when set to false") {
    SC2APIProtocol::AbilityData proto;
    proto.set_ability_id(124);
    proto.set_is_instant_placement(false);

    sc2::AbilityData pod;
    pod.ReadFromProto(proto);

    CHECK(pod.is_instant_placement == false);
}

TEST_CASE("AbilityData.is_instant_placement defaults to false when absent") {
    SC2APIProtocol::AbilityData proto;
    proto.set_ability_id(125);

    sc2::AbilityData pod;
    pod.ReadFromProto(proto);

    CHECK(pod.is_instant_placement == false);
}
