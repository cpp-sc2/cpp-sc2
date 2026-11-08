#include <iostream>

#include "sc2api/sc2_unit.h"

int main() {
    sc2::UnitPool pool;

    sc2::Unit* first = pool.CreateUnit(1);
    if (!first) {
        std::cerr << "CreateUnit returned null\n";
        return 1;
    }
    if (first->User() != nullptr) {
        std::cerr << "new unit user pointer must be null\n";
        return 1;
    }

    int marker = 42;
    first->SetUser(&marker);

    sc2::Unit* same = pool.CreateUnit(1);
    if (same != first) {
        std::cerr << "same tag must reuse the Unit\n";
        return 1;
    }
    if (same->User() != &marker) {
        std::cerr << "user pointer must survive CreateUnit for a living tag\n";
        return 1;
    }

    sc2::Unit* second = pool.CreateUnit(2);
    if (!second || second == first) {
        std::cerr << "new tag must allocate a different Unit\n";
        return 1;
    }
    if (second->User() != nullptr) {
        std::cerr << "unrelated unit must not inherit user pointer\n";
        return 1;
    }

    std::cout << "test_unit_pool succeeded.\n";
    return 0;
}
