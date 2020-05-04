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
    return (*this)(unit_.unit_type);
}

bool IsTownHall::operator()(UNIT_TYPEID type_) const {
    return type_ == UNIT_TYPEID::PROTOSS_NEXUS ||
           type_ == UNIT_TYPEID::TERRAN_COMMANDCENTER ||
           type_ == UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING ||
           type_ == UNIT_TYPEID::TERRAN_ORBITALCOMMAND ||
           type_ == UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING ||
           type_ == UNIT_TYPEID::TERRAN_PLANETARYFORTRESS ||
           type_ == UNIT_TYPEID::ZERG_HATCHERY ||
           type_ == UNIT_TYPEID::ZERG_HIVE ||
           type_ == UNIT_TYPEID::ZERG_LAIR;
}

bool IsMineralPatch::operator()(const Unit& unit_) const {
    return (*this)(unit_.unit_type);
}

bool IsMineralPatch::operator()(UNIT_TYPEID type_) const {
    return type_ == UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD750 ||
           type_ == UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD ||
           type_ == UNIT_TYPEID::NEUTRAL_LABMINERALFIELD750 ||
           type_ == UNIT_TYPEID::NEUTRAL_LABMINERALFIELD ||
           type_ == UNIT_TYPEID::NEUTRAL_MINERALFIELD750 ||
           type_ == UNIT_TYPEID::NEUTRAL_MINERALFIELD ||
           type_ == UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD750 ||
           type_ == UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD ||
           type_ == UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD750 ||
           type_ == UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD ||
           type_ == UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750 ||
           type_ == UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD;
}

bool IsVisibleMineralPatch::operator()(const Unit& unit_) const {
    return unit_.mineral_contents > 0;
}

bool IsGeyser::operator()(const Unit& unit_) const {
    return (*this)(unit_.unit_type);
}

bool IsGeyser::operator()(UNIT_TYPEID type_) const {
    return type_ == UNIT_TYPEID::NEUTRAL_VESPENEGEYSER ||
           type_ == UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER ||
           type_ == UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER ||
           type_ == UNIT_TYPEID::NEUTRAL_PURIFIERVESPENEGEYSER ||
           type_ == UNIT_TYPEID::NEUTRAL_SHAKURASVESPENEGEYSER ||
           type_ == UNIT_TYPEID::NEUTRAL_RICHVESPENEGEYSER;
}

bool IsVisibleGeyser::operator()(const Unit& unit_) const {
    return unit_.vespene_contents > 0;
}

}  // namespace sc2
