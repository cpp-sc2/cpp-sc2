#pragma once

#include <stdint.h>

#include <vector>

#include "sc2_common.h"
#include "sc2_gametypes.h"
#include "sc2_typeenums.h"

namespace sc2 {

//! HUD / observation alerts. Matches SC2APIProtocol::Alert. Enum only — no unit tag or extra payload.
//! Failed commands with a unit/ability/result are ActionError (ResponseObservation.action_errors).
enum class Alert : int {
    Unknown = 0,  // Not a protocol value. Missing or unrecognized Alert.
    NuclearLaunchDetected = 1,
    NydusWormDetected = 2,
    AlertError = 3,
    AddOnComplete = 4,
    BuildingComplete = 5,
    BuildingUnderAttack = 6,
    LarvaHatched = 7,
    MergeComplete = 8,
    MineralsExhausted = 9,
    MorphComplete = 10,
    MothershipComplete = 11,
    MULEExpired = 12,
    NukeComplete = 13,
    ResearchComplete = 14,
    TrainError = 15,
    TrainUnitComplete = 16,
    TrainWorkerComplete = 17,
    TransformationComplete = 18,
    UnitUnderAttack = 19,
    UpgradeComplete = 20,
    VespeneExhausted = 21,
    WarpInComplete = 22
};

//! Result of an issued action. Matches SC2APIProtocol::ActionResult.
enum class ActionResult {
    Unknown = 0,  // Not a protocol value. Missing or unrecognized ActionResult.
    Success = 1,
    NotSupported = 2,
    Error = 3,
    CantQueueThatOrder = 4,
    Retry = 5,
    Cooldown = 6,
    QueueIsFull = 7,
    RallyQueueIsFull = 8,
    NotEnoughMinerals = 9,
    NotEnoughVespene = 10,
    NotEnoughTerrazine = 11,
    NotEnoughCustom = 12,
    NotEnoughFood = 13,
    FoodUsageImpossible = 14,
    NotEnoughLife = 15,
    NotEnoughShields = 16,
    NotEnoughEnergy = 17,
    LifeSuppressed = 18,
    ShieldsSuppressed = 19,
    EnergySuppressed = 20,
    NotEnoughCharges = 21,
    CantAddMoreCharges = 22,
    TooMuchMinerals = 23,
    TooMuchVespene = 24,
    TooMuchTerrazine = 25,
    TooMuchCustom = 26,
    TooMuchFood = 27,
    TooMuchLife = 28,
    TooMuchShields = 29,
    TooMuchEnergy = 30,
    MustTargetUnitWithLife = 31,
    MustTargetUnitWithShields = 32,
    MustTargetUnitWithEnergy = 33,
    CantTrade = 34,
    CantSpend = 35,
    CantTargetThatUnit = 36,
    CouldntAllocateUnit = 37,
    UnitCantMove = 38,
    TransportIsHoldingPosition = 39,
    BuildTechRequirementsNotMet = 40,
    CantFindPlacementLocation = 41,
    CantBuildOnThat = 42,
    CantBuildTooCloseToDropOff = 43,
    CantBuildLocationInvalid = 44,
    CantSeeBuildLocation = 45,
    CantBuildTooCloseToCreepSource = 46,
    CantBuildTooCloseToResources = 47,
    CantBuildTooFarFromWater = 48,
    CantBuildTooFarFromCreepSource = 49,
    CantBuildTooFarFromBuildPowerSource = 50,
    CantBuildOnDenseTerrain = 51,
    CantTrainTooFarFromTrainPowerSource = 52,
    CantLandLocationInvalid = 53,
    CantSeeLandLocation = 54,
    CantLandTooCloseToCreepSource = 55,
    CantLandTooCloseToResources = 56,
    CantLandTooFarFromWater = 57,
    CantLandTooFarFromCreepSource = 58,
    CantLandTooFarFromBuildPowerSource = 59,
    CantLandTooFarFromTrainPowerSource = 60,
    CantLandOnDenseTerrain = 61,
    AddOnTooFarFromBuilding = 62,
    MustBuildRefineryFirst = 63,
    BuildingIsUnderConstruction = 64,
    CantFindDropOff = 65,
    CantLoadOtherPlayersUnits = 66,
    NotEnoughRoomToLoadUnit = 67,
    CantUnloadUnitsThere = 68,
    CantWarpInUnitsThere = 69,
    CantLoadImmobileUnits = 70,
    CantRechargeImmobileUnits = 71,
    CantRechargeUnderConstructionUnits = 72,
    CantLoadThatUnit = 73,
    NoCargoToUnload = 74,
    LoadAllNoTargetsFound = 75,
    NotWhileOccupied = 76,
    CantAttackWithoutAmmo = 77,
    CantHoldAnyMoreAmmo = 78,
    TechRequirementsNotMet = 79,
    MustLockdownUnitFirst = 80,
    MustTargetUnit = 81,
    MustTargetInventory = 82,
    MustTargetVisibleUnit = 83,
    MustTargetVisibleLocation = 84,
    MustTargetWalkableLocation = 85,
    MustTargetPawnableUnit = 86,
    YouCantControlThatUnit = 87,
    YouCantIssueCommandsToThatUnit = 88,
    MustTargetResources = 89,
    RequiresHealTarget = 90,
    RequiresRepairTarget = 91,
    NoItemsToDrop = 92,
    CantHoldAnyMoreItems = 93,
    CantHoldThat = 94,
    TargetHasNoInventory = 95,
    CantDropThisItem = 96,
    CantMoveThisItem = 97,
    CantPawnThisUnit = 98,
    MustTargetCaster = 99,
    CantTargetCaster = 100,
    MustTargetOuter = 101,
    CantTargetOuter = 102,
    MustTargetYourOwnUnits = 103,
    CantTargetYourOwnUnits = 104,
    MustTargetFriendlyUnits = 105,
    CantTargetFriendlyUnits = 106,
    MustTargetNeutralUnits = 107,
    CantTargetNeutralUnits = 108,
    MustTargetEnemyUnits = 109,
    CantTargetEnemyUnits = 110,
    MustTargetAirUnits = 111,
    CantTargetAirUnits = 112,
    MustTargetGroundUnits = 113,
    CantTargetGroundUnits = 114,
    MustTargetStructures = 115,
    CantTargetStructures = 116,
    MustTargetLightUnits = 117,
    CantTargetLightUnits = 118,
    MustTargetArmoredUnits = 119,
    CantTargetArmoredUnits = 120,
    MustTargetBiologicalUnits = 121,
    CantTargetBiologicalUnits = 122,
    MustTargetHeroicUnits = 123,
    CantTargetHeroicUnits = 124,
    MustTargetRoboticUnits = 125,
    CantTargetRoboticUnits = 126,
    MustTargetMechanicalUnits = 127,
    CantTargetMechanicalUnits = 128,
    MustTargetPsionicUnits = 129,
    CantTargetPsionicUnits = 130,
    MustTargetMassiveUnits = 131,
    CantTargetMassiveUnits = 132,
    MustTargetMissile = 133,
    CantTargetMissile = 134,
    MustTargetWorkerUnits = 135,
    CantTargetWorkerUnits = 136,
    MustTargetEnergyCapableUnits = 137,
    CantTargetEnergyCapableUnits = 138,
    MustTargetShieldCapableUnits = 139,
    CantTargetShieldCapableUnits = 140,
    MustTargetFlyers = 141,
    CantTargetFlyers = 142,
    MustTargetBuriedUnits = 143,
    CantTargetBuriedUnits = 144,
    MustTargetCloakedUnits = 145,
    CantTargetCloakedUnits = 146,
    MustTargetUnitsInAStasisField = 147,
    CantTargetUnitsInAStasisField = 148,
    MustTargetUnderConstructionUnits = 149,
    CantTargetUnderConstructionUnits = 150,
    MustTargetDeadUnits = 151,
    CantTargetDeadUnits = 152,
    MustTargetRevivableUnits = 153,
    CantTargetRevivableUnits = 154,
    MustTargetHiddenUnits = 155,
    CantTargetHiddenUnits = 156,
    CantRechargeOtherPlayersUnits = 157,
    MustTargetHallucinations = 158,
    CantTargetHallucinations = 159,
    MustTargetInvulnerableUnits = 160,
    CantTargetInvulnerableUnits = 161,
    MustTargetDetectedUnits = 162,
    CantTargetDetectedUnits = 163,
    CantTargetUnitWithEnergy = 164,
    CantTargetUnitWithShields = 165,
    MustTargetUncommandableUnits = 166,
    CantTargetUncommandableUnits = 167,
    MustTargetPreventDefeatUnits = 168,
    CantTargetPreventDefeatUnits = 169,
    MustTargetPreventRevealUnits = 170,
    CantTargetPreventRevealUnits = 171,
    MustTargetPassiveUnits = 172,
    CantTargetPassiveUnits = 173,
    MustTargetStunnedUnits = 174,
    CantTargetStunnedUnits = 175,
    MustTargetSummonedUnits = 176,
    CantTargetSummonedUnits = 177,
    MustTargetUser1 = 178,
    CantTargetUser1 = 179,
    MustTargetUnstoppableUnits = 180,
    CantTargetUnstoppableUnits = 181,
    MustTargetResistantUnits = 182,
    CantTargetResistantUnits = 183,
    MustTargetDazedUnits = 184,
    CantTargetDazedUnits = 185,
    CantLockdown = 186,
    CantMindControl = 187,
    MustTargetDestructibles = 188,
    CantTargetDestructibles = 189,
    MustTargetItems = 190,
    CantTargetItems = 191,
    NoCalldownAvailable = 192,
    WaypointListFull = 193,
    MustTargetRace = 194,
    CantTargetRace = 195,
    MustTargetSimilarUnits = 196,
    CantTargetSimilarUnits = 197,
    CantFindEnoughTargets = 198,
    AlreadySpawningLarva = 199,
    CantTargetExhaustedResources = 200,
    CantUseMinimap = 201,
    CantUseInfoPanel = 202,
    OrderQueueIsFull = 203,
    CantHarvestThatResource = 204,
    HarvestersNotRequired = 205,
    AlreadyTargeted = 206,
    CantAttackWeaponsDisabled = 207,
    CouldntReachTarget = 208,
    TargetIsOutOfRange = 209,
    TargetIsTooClose = 210,
    TargetIsOutOfArc = 211,
    CantFindTeleportLocation = 212,
    InvalidItemClass = 213,
    CantFindCancelOrder = 214
};

//! Failed command from ResponseObservation.action_errors (UI "red text").
//! unit_tag is only populated with the raw interface.
struct ActionError {
    Tag unit_tag = NullTag;
    AbilityID ability_id = 0;
    ActionResult result = ActionResult::Unknown;
};

//! An action (command or ability) applied to a unit or set of units.
struct ActionRaw {
    //! Type of target. Target types are mutually exclusive.
    enum TargetType {
        //! No target generally means 'self', e.g., a order to make a unit.
        TargetNone,
        //! The target is a unit tag, could also be a snapshot in the fog-of-war.
        TargetUnitTag,
        //! The target is a point.
        TargetPosition
    };

    //! The ID of the ability to invoke.
    AbilityID ability_id = 0;
    //! Units this action applies to. In normal use, this would be the currently selected units.
    std::vector<Tag> unit_tags;
    //! Which target fields are valid.
    TargetType target_type = TargetNone;
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

//! An action (command or ability) applied to selected units when using feature layers or the rendered interface.
struct SpatialUnitCommand {
    //! If this action should apply to the screen or minimap.
    enum TargetType {
        //! Apply this action to the main game screen.
        TargetScreen,
        //! Apply this action to the minimap.
        TargetMinimap
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

//! Where to move the camera to on the minimap.
struct SpatialCameraMove {
    Point2DI center_minimap;
};

//! Types of selection.
enum class PointSelectionType {
    //! Equivalent to normal click. Changes selection to unit.
    PtSelect = 1,
    //! Equivalent to shift+click. Toggle selection of unit.
    PtToggle = 2,
    //! Equivalent to control+click. Selects all units of a given type.
    PtAllType = 3,
    //! Equivalent to shift+control+click. Selects all units of a given type.
    PtAddAllType = 4
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
