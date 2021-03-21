#pragma once

#include "sc2_typeenums.h"
#include "sc2_unit.h"

#include <vector>

namespace sc2 {
//! Determines if the unit matches the unit type.
struct IsUnit {
    explicit IsUnit(UNIT_TYPEID type_);

    bool operator()(const Unit& unit_) const;

 private:
    UNIT_TYPEID m_type;
};

//! Determines if units matches the unit type.
struct IsUnits {
    explicit IsUnits(const std::vector<UNIT_TYPEID>& types_);

    bool operator()(const Unit& unit_) const ;

 private:
    std::vector<UNIT_TYPEID> m_types;
};

//! Determines if the unit is town hall (command center, hatchery etc).
struct IsTownHall {
    bool operator()(const Unit& unit_) const;

    bool operator()(UNIT_TYPEID type_) const;
};

//! Determines if the unit is mineral patch,
//! includes 'foggy' minerals (hidden under the fog of war).
struct IsMineralPatch {
    bool operator()(const Unit& unit_) const;

    bool operator()(UNIT_TYPEID type_) const;
};

//! Determines if the unit is visible mineral patch.
//! All the visible mineral patches has non-zero mineral
//! contents while the mineral patches covered by the fog of war don't have
//! such parameter (it is always zero) and can't be selected/targeted.
//! This filter returns only the visible and not depleted mineral patches.
struct IsVisibleMineralPatch {
    bool operator()(const Unit& unit_) const;
};

//! Determines if the unit is vespene geyser,
//! includes 'foggy' geysers (hidden under the fog of war).
struct IsGeyser {
    bool operator()(const Unit& unit_) const;

    bool operator()(UNIT_TYPEID type_) const;
};

//! Determines if the unit is visible vespene geyser.
//! All the geysers has non-zero vespene contents while
//! the geysers covered by the fog of war don't have such parameter
//! (it is always zero) and can't be selected/targeted.
//! This filter returns only the visible and not depleted geysers.
struct IsVisibleGeyser {
    bool operator()(const Unit& unit_) const;
};

//! Determines if the unit is a building.
struct IsBuilding {
    bool operator()(const Unit& unit_) const;

    bool operator()(UNIT_TYPEID type_) const;
};

//! Determines if the unit is a worker.
//! Good to use in generic bots supporting all races.
//! For bots supporting only one race IsUnit is recommended as it is
//! a bit faster, e.g. sc2::IsUnit(sc2::UNIT_TYPEID::TERRAN_SCV).
struct IsWorker {
    bool operator()(const Unit& unit_) const;

    bool operator()(UNIT_TYPEID type_) const;
};

//! Determines if the unit is visible.
//! See sc2::Unit::DisplayType.
struct IsVisible {
    bool operator()(const Unit& unit_) const;
};

//! Helper function used to discover whether a unit is carrying minerals or not. You could use this function in GetUnits
//! to get all units carrying minerals: Units units = GetUnits(Alliance::Self, IsCarryingMinerals);
//!< \param unit The unit.
//!< \param observation Not needed for this function, only exists for Filter parameters, leave nullptr (its default).
//!< \return Returns true if the unit is carrying minerals, false otherwise.
bool IsCarryingMinerals(const Unit& unit);

//! Helper function used to discover whether a unit is carrying vespene or not. You could use this function in GetUnits
//! to get all units carrying vespene: Units units = GetUnits(Alliance::Self, IsCarryingVespene);
//!< \param unit The unit.
//!< \param observation Not needed for this function, only exists for Filter parameters, leave nullptr (its default).
//!< \return Returns true if the unit is carrying vespene, false otherwise.
bool IsCarryingVespene(const Unit& unit);

}  // namespace sc2
