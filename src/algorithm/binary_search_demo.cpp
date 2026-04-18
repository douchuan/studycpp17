#include "binary_search_demo.h"

#include <iostream>

int main() {
    std::vector<int> nums = {1, 2, 3, 5, 7, 9};
    std::cout << "binary_search(5): " << binary_search_manual(nums, 5) << "\n";
    std::cout << "binary_search(4): " << binary_search_manual(nums, 4) << "\n";

    std::cout << "lower_bound(4): " << lower_bound_manual(nums, 4) << "\n";
    std::cout << "upper_bound(5): " << upper_bound_manual(nums, 5) << "\n";

    std::vector<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    std::cout << "min of rotated: " << find_min_rotated(rotated) << "\n";
    std::cout << "search_rotated(0): " << search_rotated(rotated, 0) << "\n";
    std::cout << "search_rotated(3): " << search_rotated(rotated, 3) << "\n";

    return 0;
}
