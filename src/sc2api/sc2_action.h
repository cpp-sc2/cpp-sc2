#pragma once

#include <stdint.h>

#include <vector>

#include "sc2_common.h"
#include "sc2_gametypes.h"
#include "sc2_typeenums.h"

namespace sc2 {

//! An action (command or ability) applied to a unit or set of units.
struct ActionRaw {
    //! Type of target. Target types are mutually exclusive.
    enum class TargetType : uint8_t {
        //! No target generally means 'self', e.g., a order to make a unit.
        None = 1,
        //! The target is a point.
        Position = 2,
        //! The target is a unit tag, could also be a snapshot in the fog-of-war.
        UnitTag = 3,

        TargetNone [[deprecated("Use \"None\" instead.")]] = 1,          // Temporary; wil be removed in the future.
        TargetPosition [[deprecated("Use \"Position\" instead.")]] = 2,  // Temporary; wil be removed in the future.
        TargetUnitTag [[deprecated("Use \"UnitTag\" instead.")]] = 3,    // Temporary; wil be removed in the future.

    };

    //! The ID of the ability to invoke.
    AbilityID ability_id = 0;
    //! Units this action applies to. In normal use, this would be the currently selected units.
    std::vector<Tag> unit_tags;
    //! Which target fields are valid.
    TargetType target_type{TargetType::None};
    //! The target of this action. Valid only when target_type == TargetUnitTag.
    Tag target_tag = NullTag;
    //! The target point for this action. Valid only when target_type == TargetPosition.
    Point2D target_point;

    //! Comparison overload.

    bool operator==(const ActionRaw& a) const {
        if (ability_id != a.ability_id) {
            return false;
        }
        if (target_type != a.target_type) {
            return false;
        }
        if (target_tag != a.target_tag) {
            return false;
        }
        if (target_point.x != a.target_point.x) {
            return false;
        }
        if (target_point.y != a.target_point.y) {
            return false;
        }
        return true;
    }
};

using RawActions = std::vector<ActionRaw>;
using RawTargetType = ActionRaw::TargetType;

//! An action (command or ability) applied to selected units when using feature layers or the rendered interface.
struct SpatialUnitCommand {
    //! If this action should apply to the screen or minimap.
    enum class TargetType : uint8_t {
        //! Apply this action to the main game screen.
        ScreenCoord = 1,
        //! Apply this action to the minimap.
        MinimapCoord = 2,

        TargetScreen [[deprecated("Use \"ScreenCoord\" instead.")]] = 1,    // Temporary; wil be removed in the future.
        TargetMinimap [[deprecated("Use \"MinimapCoord\" instead.")]] = 2,  // Temporary; wil be removed in the future.
    };

    //! The ID of the ability to invoke.
    AbilityID ability_id;
    //! If this action should be applied to the main game screen or the minimap.
    TargetType target_type;
    //! Target point on the screen or minimap, if required.
    Point2DI target;
    //! Indicates if this action should replace or queue behind other actions.
    bool queued;
};

using SpatialTargetType = SpatialUnitCommand::TargetType;

//! Where to move the camera to on the minimap.
struct SpatialCameraMove {
    Point2DI center_minimap;
};

//! Types of selection.
enum class PointSelectionType : uint8_t {
    Invalid = 0,
    Select = 1,      // Equivalent to normal click. Changes selection to unit.
    Toggle = 2,      // Equivalent to shift+click. Toggle selection of unit.
    AllType = 3,     // Equivalent to control+click. Selects all units of a given type.
    AddAllType = 4,  // Equivalent to shift+control+click. Selects all units of a given type.

    PtSelect [[deprecated("Use \"Select\" instead.")]] = 1,          // Temporary; wil be removed in the future.
    PtToggle [[deprecated("Use \"Toggle\" instead.")]] = 2,          // Temporary; wil be removed in the future.
    PtAllType [[deprecated("Use \"AllType\" instead.")]] = 3,        // Temporary; wil be removed in the future.
    PtAddAllType [[deprecated("Use \"AddAllType\" instead.")]] = 4,  // Temporary; wil be removed in the future.
};

//! Point selection.
struct SpatialSelectPoint {
    Point2DI select_screen;
    PointSelectionType type;
};

//! Rectangle selection. Equivalent to click-drag with the mouse. Multiple rectangles
//! are allowed as the feature layer projection is orthogonal, and may not exactly work
//! for the regular in-game perspective view.
struct SpatialSelectRect {
    std::vector<Rect2DI> select_screen;
    bool select_add;
};

//! Possible actions for feature layers.
struct SpatialActions {
    //! Commands to selected units.
    std::vector<SpatialUnitCommand> unit_commands;
    //! Camera movement.
    std::vector<SpatialCameraMove> camera_moves;
    //! Selecting by point.
    std::vector<SpatialSelectPoint> select_points;
    //! Selecting by rectangles.
    std::vector<SpatialSelectRect> select_rects;
};

}  // namespace sc2
