#include "sc2api/sc2_unit_filters.h"

namespace sc2 {

IsUnit::IsUnit(UNIT_TYPEID type_): m_type(type_) {
}

bool IsUnit::operator()(const Unit& unit_) const {
    return unit_.unit_type == m_type;
}

IsUnits::IsUnits(const std::vector<UNIT_TYPEID>& types_): m_types(types_) {
}

bool IsUnits::operator()(const Unit& unit_) const {
    for (const auto& type : m_types) {
        if (unit_.unit_type == type)
            return true;
    }

    return false;
}

bool IsTownHall::operator()(const Unit& unit_) const {
    return (unit_.unit_type);
}

bool IsTownHall::operator()(UNIT_TYPEID type_) const {
    return type_ == sc2::UNIT_TYPEID::PROTOSS_NEXUS ||
           type_ == sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER ||
           type_ == sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING ||
           type_ == sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND ||
           type_ == sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING ||
           type_ == sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS ||
           type_ == sc2::UNIT_TYPEID::ZERG_HATCHERY ||
           type_ == sc2::UNIT_TYPEID::ZERG_HIVE ||
           type_ == sc2::UNIT_TYPEID::ZERG_LAIR;
}

}  // namespace sc2
