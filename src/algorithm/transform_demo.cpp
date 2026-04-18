#include "transform_demo.h"

#include <iostream>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // map: 平方
    auto squared = transform(nums, [](int x) { return x * x; });
    std::cout << "squared: ";
    for (int n : squared) std::cout << n << " ";
    std::cout << "\n";

    // filter: 偶数
    auto evens = filter(nums, [](int x) { return x % 2 == 0; });
    std::cout << "evens: ";
    for (int n : evens) std::cout << n << " ";
    std::cout << "\n";

    // reduce: 累加
    auto total = reduce(nums, 0, std::plus<>{});
    std::cout << "sum: " << total << "\n";

    // reduce: 累乘
    auto product = reduce(nums, 1, std::multiplies<>{});
    std::cout << "product: " << product << "\n";

    return 0;
}
