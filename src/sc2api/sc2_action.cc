#include "sc2api/sc2_action.h"

#include <iostream>
#include <cassert>

#include "s2clientprotocol/sc2api.pb.h"

namespace sc2 {

ActionRawUnitCommand::ActionRawUnitCommand() :
    ability_id(0),
    raw_ability_id(0),
    target_type(TargetNone),
    target_tag(NullTag) {
}

ActionRawUnitCommand::~ActionRawUnitCommand() {

}

ActionRawToggleAutocast::ActionRawToggleAutocast() : ability_id(0), raw_ability_id(0) {

}

ActionRawCameraMove::ActionRawCameraMove() : x(0.0), y(0.0) {

}

ActionRawCameraMove::~ActionRawCameraMove() {

}

}
