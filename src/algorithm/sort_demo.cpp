#include "sort_demo.h"

#include <iostream>

int main() {
    std::vector<int> nums = {5, 2, 8, 1, 9, 3};

    auto asc = sort_asc(nums);
    std::cout << "sort_asc: ";
    for (int n : asc) std::cout << n << " ";
    std::cout << "\n";

    auto desc = sort_desc(nums);
    std::cout << "sort_desc: ";
    for (int n : desc) std::cout << n << " ";
    std::cout << "\n";

    auto top3 = top_k(nums, 3);
    std::cout << "top_k(3): ";
    for (int n : top3) std::cout << n << " ";
    std::cout << "\n";

    std::cout << "is_sorted({1,2,3}): " << std::boolalpha << is_sorted({1, 2, 3}) << "\n";
    std::cout << "is_sorted({3,1,2}): " << is_sorted({3, 1, 2}) << "\n";

    return 0;
}
