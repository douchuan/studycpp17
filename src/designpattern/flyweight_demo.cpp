#include "flyweight_demo.h"

#include <iostream>

int main() {
    FontFactory factory;
    auto f1 = factory.get_font("Arial");
    auto f2 = factory.get_font("Arial");
    auto f3 = factory.get_font("Times");
    std::cout << "shared: " << (f1 == f2) << "\n";
    std::cout << "different: " << (f1 == f3) << "\n";
    return 0;
}
