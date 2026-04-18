#include "state_demo.h"

#include <iostream>

int main() {
    VendingMachine vm(std::make_unique<IdleState>());
    std::cout << vm.current_state() << "\n";
    std::cout << vm.insert_coin() << "\n";
    std::cout << vm.current_state() << "\n";
    std::cout << vm.dispense() << "\n";
    std::cout << vm.current_state() << "\n";
    return 0;
}
