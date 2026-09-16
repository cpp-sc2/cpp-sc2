#include "sc2_unit.h"

#include <cassert>
#include <iostream>

#include "s2clientprotocol/sc2api.pb.h"

namespace sc2 {

bool Unit::IsBuildFinished() const {
    return build_progress >= 1.0F;
}

Tags ConvertToTags(const Units& units) {
    Tags tags;
    std::transform(std::begin(units), std::end(units), std::back_inserter(tags),
                   [](const Unit* unit) { return unit->tag; });

    return tags;
}

namespace {

void ResetUnit(Unit* unit) {
    *unit = Unit{};
}

}  // namespace

Unit* UnitPool::CreateUnit(Tag tag) {
    Unit* existing = GetUnit(tag);
    if (existing) {
        tag_to_existing_unit_[tag] = existing;
        return existing;
    }

    Unit* unit = nullptr;
    if (!free_units_.empty()) {
        unit = free_units_.back();
        free_units_.pop_back();
        ResetUnit(unit);
    } else {
        if (unit_pool_.empty() || unit_pool_.size() == available_index_.first) {
            unit_pool_.push_back(std::vector<Unit>(ENTRY_SIZE));
        }

        std::vector<Unit>& pool = unit_pool_[available_index_.first];
        unit = &pool[available_index_.second];
        ResetUnit(unit);
        IncrementIndex();
    }

    unit->last_seen_game_loop = 0;  // initialization required for OnUnitEnterVision
    unit->is_alive = true;
    unit->tag = tag;
    tag_to_unit_[tag] = unit;
    tag_to_existing_unit_[tag] = unit;
    AddNewUnit(unit);
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
    MarkDead(tag, 0);
}

void UnitPool::MarkDead(Tag tag, uint32_t game_loop) {
    Unit* unit = GetUnit(tag);
    if (!unit) {
        return;
    }
    unit->is_alive = false;
    unit->died_game_loop = game_loop;
    tag_to_existing_unit_.erase(tag);
}

void UnitPool::SweepDead(uint32_t game_loop) {
    for (auto it = tag_to_unit_.begin(); it != tag_to_unit_.end();) {
        Unit* unit = it->second;
        if (unit->is_alive || game_loop < unit->died_game_loop + kDeadUnitCacheLoops) {
            ++it;
            continue;
        }
        it = tag_to_unit_.erase(it);
        free_units_.push_back(unit);
    }
}

void UnitPool::ForEachExistingUnit(const std::function<void(Unit& unit)>& functor) const {
    for (const auto& u : tag_to_existing_unit_) {
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

}  // namespace sc2
