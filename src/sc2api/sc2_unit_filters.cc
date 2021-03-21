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

bool IsBuilding::operator()(const Unit& unit_) const {
    return (*this)(unit_.unit_type);
}

bool IsBuilding::operator()(UNIT_TYPEID type_) const {
    switch (type_) {
        // Terran
        case UNIT_TYPEID::TERRAN_ARMORY:
        case UNIT_TYPEID::TERRAN_BARRACKS:
        case UNIT_TYPEID::TERRAN_BARRACKSFLYING:
        case UNIT_TYPEID::TERRAN_BARRACKSREACTOR:
        case UNIT_TYPEID::TERRAN_BARRACKSTECHLAB:
        case UNIT_TYPEID::TERRAN_BUNKER:
        case UNIT_TYPEID::TERRAN_COMMANDCENTER:
        case UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING:
        case UNIT_TYPEID::TERRAN_ENGINEERINGBAY:
        case UNIT_TYPEID::TERRAN_FACTORY:
        case UNIT_TYPEID::TERRAN_FACTORYFLYING:
        case UNIT_TYPEID::TERRAN_FACTORYREACTOR:
        case UNIT_TYPEID::TERRAN_FACTORYTECHLAB:
        case UNIT_TYPEID::TERRAN_FUSIONCORE:
        case UNIT_TYPEID::TERRAN_GHOSTACADEMY:
        case UNIT_TYPEID::TERRAN_MISSILETURRET:
        case UNIT_TYPEID::TERRAN_ORBITALCOMMAND:
        case UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING:
        case UNIT_TYPEID::TERRAN_PLANETARYFORTRESS:
        case UNIT_TYPEID::TERRAN_REFINERY:
        case UNIT_TYPEID::TERRAN_SENSORTOWER:
        case UNIT_TYPEID::TERRAN_STARPORT:
        case UNIT_TYPEID::TERRAN_STARPORTFLYING:
        case UNIT_TYPEID::TERRAN_STARPORTREACTOR:
        case UNIT_TYPEID::TERRAN_STARPORTTECHLAB:
        case UNIT_TYPEID::TERRAN_SUPPLYDEPOT:
        case UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED:
        case UNIT_TYPEID::TERRAN_REACTOR:
        case UNIT_TYPEID::TERRAN_TECHLAB:

        // Zerg
        case UNIT_TYPEID::ZERG_BANELINGNEST:
        case UNIT_TYPEID::ZERG_CREEPTUMOR:
        case UNIT_TYPEID::ZERG_CREEPTUMORBURROWED:
        case UNIT_TYPEID::ZERG_CREEPTUMORQUEEN:
        case UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER:
        case UNIT_TYPEID::ZERG_EXTRACTOR:
        case UNIT_TYPEID::ZERG_GREATERSPIRE:
        case UNIT_TYPEID::ZERG_HATCHERY:
        case UNIT_TYPEID::ZERG_HIVE:
        case UNIT_TYPEID::ZERG_HYDRALISKDEN:
        case UNIT_TYPEID::ZERG_INFESTATIONPIT:
        case UNIT_TYPEID::ZERG_LAIR:
        case UNIT_TYPEID::ZERG_LURKERDENMP:
        case UNIT_TYPEID::ZERG_NYDUSCANAL:
        case UNIT_TYPEID::ZERG_NYDUSNETWORK:
        case UNIT_TYPEID::ZERG_SPAWNINGPOOL:
        case UNIT_TYPEID::ZERG_SPINECRAWLER:
        case UNIT_TYPEID::ZERG_SPINECRAWLERUPROOTED:
        case UNIT_TYPEID::ZERG_SPIRE:
        case UNIT_TYPEID::ZERG_SPORECRAWLER:
        case UNIT_TYPEID::ZERG_SPORECRAWLERUPROOTED:
        case UNIT_TYPEID::ZERG_ULTRALISKCAVERN:

        // Protoss
        case sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR:
        case sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE:
        case sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE:
        case sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON:
        case sc2::UNIT_TYPEID::PROTOSS_FORGE:
        case sc2::UNIT_TYPEID::PROTOSS_GATEWAY:
        case sc2::UNIT_TYPEID::PROTOSS_NEXUS:
        case sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON:
        case sc2::UNIT_TYPEID::PROTOSS_PYLON:
        case sc2::UNIT_TYPEID::PROTOSS_PYLONOVERCHARGED:
        case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY:
        case sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY:
        case sc2::UNIT_TYPEID::PROTOSS_STARGATE:
        case sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE:
        case sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL:
        case sc2::UNIT_TYPEID::PROTOSS_WARPGATE:
        case sc2::UNIT_TYPEID::PROTOSS_SHIELDBATTERY:
            return true;

        default:
            return false;
    }
}

bool IsWorker::operator()(const Unit& unit_) const {
    return (*this)(unit_.unit_type);
}

bool IsWorker::operator()(UNIT_TYPEID type_) const {
    return type_ == sc2::UNIT_TYPEID::TERRAN_SCV ||
        type_ == sc2::UNIT_TYPEID::ZERG_DRONE ||
        type_ == sc2::UNIT_TYPEID::PROTOSS_PROBE;
}

bool IsVisible::operator()(const Unit& unit_) const {
    return unit_.display_type == Unit::Visible;
};

bool IsCarryingMinerals(const Unit& unit) {
    auto is_mineral = [](const BuffID& buff){
        return buff == BUFF_ID::CARRYMINERALFIELDMINERALS
            || buff == BUFF_ID::CARRYHIGHYIELDMINERALFIELDMINERALS;
    };
    return std::find_if(unit.buffs.begin(), unit.buffs.end(), is_mineral) != unit.buffs.end();
}

bool IsCarryingVespene(const Unit& unit) {
    auto is_vespene = [](const BuffID& buff){
        return buff == BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGAS
            || buff == BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGASPROTOSS
            || buff == BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGASZERG;
    };
    return std::find_if(unit.buffs.begin(), unit.buffs.end(), is_vespene) != unit.buffs.end();
}

}  // namespace sc2
