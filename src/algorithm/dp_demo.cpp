#include "dp_demo.h"

#include <iostream>

int main() {
    std::cout << "fib(10): " << fib(10) << "\n";
    std::cout << "climb_stairs(5): " << climb_stairs(5) << "\n";

    // knapsack
    std::vector<int> w = {2, 3, 4, 5};
    std::vector<int> v = {3, 4, 5, 7};
    std::cout << "knapsack(cap=7): " << knapsack(w, v, 7) << "\n";

    // LCS
    std::cout << "LCS('abcde','ace'): " << longest_common_subsequence("abcde", "ace") << "\n";

    // LIS
    std::cout << "LIS({10,9,2,5,3,7,101}): "
              << longest_increasing_subsequence({10, 9, 2, 5, 3, 7, 101, 18}) << "\n";

    // Kadane
    std::cout << "max_subarray({-2,1,-3,4,-1,2,1}): "
              << max_subarray({-2, 1, -3, 4, -1, 2, 1, -5, 4}) << "\n";

    return 0;
}
