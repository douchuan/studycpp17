#include "apply_demo.h"

#include <iostream>

int main() {
    std::cout << "apply_add({1,2,3}): " << apply_add({1, 2, 3}) << "\n";
    std::cout << "apply_greet({'Alice', 30}): " << apply_greet({"Alice", 30}) << "\n";
    std::cout << "make_point_label({10, 20}): " << make_point_label({10, 20}) << "\n";

    return 0;
}
