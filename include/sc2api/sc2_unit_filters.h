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

}  // namespace sc2
