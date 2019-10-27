#pragma once

#include "sc2_typeenums.h"
#include "sc2_unit.h"

#include <vector>

namespace sc2 {
//! Determines if the unit matches the unit type.
struct IsUnit {
    explicit IsUnit(UNIT_TYPEID type_);

    bool operator()(const Unit& unit_);

 private:
    UNIT_TYPEID m_type;
};

//! Determines if units matches the unit type.
struct IsUnits {
    explicit IsUnits(const std::vector<UNIT_TYPEID>& types_);

    bool operator()(const Unit& unit_);

 private:
    std::vector<UNIT_TYPEID> m_types;
};

}  // namespace sc2
