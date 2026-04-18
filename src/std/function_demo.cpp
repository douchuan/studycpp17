#include "function_demo.h"

#include <iostream>

int main() {
    // std::function
    auto add = make_adder();
    std::cout << "add(3, 4) = " << add(3, 4) << "\n";

    // runtime strategy
    auto sum_fn = make_aggregator("sum");
    auto max_fn = make_aggregator("max");
    std::vector<int> nums = {3, 1, 4, 1, 5};
    std::cout << "sum: " << sum_fn(nums) << "\n";
    std::cout << "max: " << max_fn(nums) << "\n";
    std::cout << "unknown: " << make_aggregator("avg")(nums) << "\n";

    // map_vec
    auto squared = map_vec(nums, [](int x) { return x * x; });
    std::cout << "squared: ";
    for (int x : squared) std::cout << x << " ";
    std::cout << "\n";

    // bind
    auto doubler = make_doubler();
    std::cout << "doubler(7) = " << doubler(7) << "\n";

    return 0;
}
