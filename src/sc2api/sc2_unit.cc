#include "sc2api/sc2_unit.h"

#include <iostream>
#include <cassert>

#include "s2clientprotocol/sc2api.pb.h"

namespace sc2 {

Unit::Unit() {
}

Unit* UnitPool::CreateUnit(Tag tag) {
    Unit* existing = GetUnit(tag);
    if (existing) {
        tag_to_existing_unit_[tag] = existing;
        return existing;
    }

    if (unit_pool_.empty() || unit_pool_.size() == available_index_.first) {
        unit_pool_.push_back(std::vector<Unit>(ENTRY_SIZE));
    }

    std::vector<Unit>& pool = unit_pool_[available_index_.first];
    Unit* unit = &pool[available_index_.second];
    unit->last_seen_game_loop = 0; // initialization required for OnUnitEnterVision
    tag_to_unit_[tag] = unit;
    tag_to_existing_unit_[tag] = unit;
    AddNewUnit(unit);
    IncrementIndex();
    return unit;
}

Unit* UnitPool::GetUnit(Tag tag) const {
    auto found = tag_to_unit_.find(tag);
    return found == tag_to_unit_.end() ? nullptr : found->second;
}

Unit* UnitPool::GetExistingUnit(Tag tag) const {
    auto found = tag_to_existing_unit_.find(tag);
    return found == tag_to_existing_unit_.end() ? nullptr : found->second;
}

void UnitPool::IncrementIndex() {
    ++available_index_.second;
    if (available_index_.second == ENTRY_SIZE) {
        ++available_index_.first;
        available_index_.second = 0;
    }
}

void UnitPool::MarkDead(Tag tag) {
    Unit* unit = GetUnit(tag);
    if (!unit) {
        return;
    }
    unit->is_alive = false;
    // CHeck if this is necessary, bro
    tag_to_existing_unit_.erase(tag);
}

void UnitPool::ForEachExistingUnit(const std::function<void(Unit& unit)>& functor) const {
    for (auto& u : tag_to_existing_unit_) {
        assert(u.second);
        functor(*u.second);
    }
}

void UnitPool::ClearExisting() {
    tag_to_existing_unit_.clear();
    units_newly_created_.clear();
    units_entering_vision_.clear();
    buildings_constructed_.clear();
    units_idled_.clear();
    units_damaged_.clear();
}

bool UnitPool::UnitExists(Tag tag) {
    return tag_to_existing_unit_.find(tag) != tag_to_existing_unit_.end();
}

}
