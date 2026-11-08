#include <iostream>

#include "sc2api/sc2_unit.h"

int main() {
    sc2::UnitPool pool;

    sc2::Unit* first = pool.CreateUnit(1);
    if (!first) {
        std::cerr << "CreateUnit returned null\n";
        return 1;
    }
    first->alliance = sc2::Unit::Alliance::Enemy;

    // Fog: left observation without a death event. Must stay GetUnit-able.
    pool.ClearExisting();
    if (pool.GetUnit(1) != first || !first->is_alive) {
        std::cerr << "units that leave vision without MarkDead must stay cached\n";
        return 1;
    }
    pool.SweepDead(10000);
    if (pool.GetUnit(1) != first) {
        std::cerr << "SweepDead must not recycle units without a death event\n";
        return 1;
    }

    // Same tag after an alliance rewrite is still the same living unit (mind control).
    first->alliance = sc2::Unit::Alliance::Self;
    sc2::Unit* taken = pool.CreateUnit(1);
    if (taken != first || !taken->is_alive) {
        std::cerr << "mind-controlled unit must keep its tag and slot\n";
        return 1;
    }

    pool.MarkDead(1, 10);
    if (pool.GetUnit(1) != first || first->is_alive) {
        std::cerr << "confirmed-dead unit must stay GetUnit-able until the grace period\n";
        return 1;
    }
    pool.SweepDead(10);
    if (pool.GetUnit(1) != first) {
        std::cerr << "must not recycle on the death frame\n";
        return 1;
    }
    pool.SweepDead(10 + sc2::UnitPool::kDeadUnitCacheLoops - 1);
    if (pool.GetUnit(1) != first) {
        std::cerr << "must not recycle before kDeadUnitCacheLoops\n";
        return 1;
    }
    pool.SweepDead(10 + sc2::UnitPool::kDeadUnitCacheLoops);
    if (pool.GetUnit(1) != nullptr) {
        std::cerr << "confirmed-dead unit must leave the cache after the grace period\n";
        return 1;
    }

    sc2::Unit* recycled = pool.CreateUnit(2);
    if (recycled != first) {
        std::cerr << "CreateUnit should reuse the confirmed-dead slot\n";
        return 1;
    }
    if (!recycled->is_alive || recycled->tag != 2) {
        std::cerr << "recycled slot must be reset for the new tag\n";
        return 1;
    }

    std::cout << "test_unit_pool succeeded.\n";
    return 0;
}
