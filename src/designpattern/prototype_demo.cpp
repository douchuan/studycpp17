#include "prototype_demo.h"

#include <iostream>

int main() {
    Circle original(5.0, "red");
    auto cloned = original.clone();
    std::cout << "original: " << original.desc() << "\n";
    std::cout << "cloned: " << cloned->desc() << "\n";
    return 0;
}
