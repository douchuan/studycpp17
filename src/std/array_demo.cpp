#include "array_demo.h"

#include <iostream>

int main() {
    auto a = make_array();
    std::cout << "array: ";
    for (int x : a) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "sum: " << array_sum(a) << "\n";
    std::cout << "max: " << array_max(a) << "\n";

    array_sort(a);
    std::cout << "sorted: ";
    for (int x : a) std::cout << x << " ";
    std::cout << "\n";

    auto filled = filled_array(7);
    std::cout << "filled(7): ";
    for (int x : filled) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
