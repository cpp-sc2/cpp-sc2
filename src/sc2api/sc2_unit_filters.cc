#include "sc2api/sc2_unit_filters.h"

namespace sc2 {

IsUnit::IsUnit(UNIT_TYPEID type_): m_type(type_) {
}

bool IsUnit::operator()(const Unit& unit_) {
    return unit_.unit_type == m_type;
}

IsUnits::IsUnits(const std::vector<UNIT_TYPEID>& types_): m_types(types_) {
}

bool IsUnits::operator()(const Unit& unit_) {
    for (const auto& type : m_types) {
        if (unit_.unit_type == type)
            return true;
    }

    return false;
}

}  // namespace sc2
