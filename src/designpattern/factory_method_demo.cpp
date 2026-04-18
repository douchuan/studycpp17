#include "factory_method_demo.h"

#include <iostream>

int main() {
    std::unique_ptr<Factory> fa = std::make_unique<FactoryA>();
    auto pa = fa->create();
    std::cout << pa->name() << "\n";

    std::unique_ptr<Factory> fb = std::make_unique<FactoryB>();
    auto pb = fb->create();
    std::cout << pb->name() << "\n";
    return 0;
}
