#include "two_pointers_demo.h"

#include <iostream>

int main() {
    // two sum sorted
    auto [a, b] = two_sum_sorted({2, 7, 11, 15}, 9);
    std::cout << "two_sum_sorted(9): [" << a << ", " << b << "]\n";

    // 3 sum
    auto triples = three_sum({-1, 0, 1, 2, -1, -4});
    std::cout << "three_sum: ";
    for (const auto& t : triples) {
        std::cout << "[" << t[0] << "," << t[1] << "," << t[2] << "] ";
    }
    std::cout << "\n";

    // max area
    std::cout << "max_area({1,8,6,2,5,4,8,3,7}): " << max_area({1, 8, 6, 2, 5, 4, 8, 3, 7}) << "\n";

    // trap
    std::cout << "trap({0,1,0,2,1,0,1,3,2,1,2,1}): " << trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1})
              << "\n";

    return 0;
}
