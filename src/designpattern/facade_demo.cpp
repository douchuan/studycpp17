#include "facade_demo.h"

#include <iostream>

int main() {
    ComputerFacade computer;
    std::cout << computer.start() << "\n";
    return 0;
}
