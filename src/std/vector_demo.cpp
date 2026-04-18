#include "vector_demo.h"

#include <iostream>

int main() {
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5};

    std::cout << "sum: " << sum(nums) << "\n";

    auto unique = unique_copy(nums);
    std::cout << "unique: ";
    for (int n : unique) std::cout << n << " ";
    std::cout << "\n";

    auto found = find_first(nums, [](int x) { return x > 5; });
    if (found) {
        std::cout << "find_first(>5): " << *found << "\n";
    } else {
        std::cout << "find_first(>5): not found\n";
    }

    return 0;
}
