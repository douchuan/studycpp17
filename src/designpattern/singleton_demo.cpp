#include "singleton_demo.h"

#include <iostream>

int main() {
    Logger::instance().log("first message");
    Logger::instance().log("second message");
    for (const auto& m : Logger::instance().history()) std::cout << m << "\n";
    return 0;
}
