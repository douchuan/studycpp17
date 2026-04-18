#include "sliding_window_demo.h"

#include <iostream>

int main() {
    std::cout << "longest_ones({1,1,0,1,1,1,0,1}, k=1): "
              << longest_ones({1, 1, 0, 1, 1, 1, 0, 1}, 1) << "\n";

    std::cout << "longest_substring_no_repeat('abcabcbb'): "
              << longest_substring_no_repeat("abcabcbb") << "\n";

    auto maxes = sliding_window_max({1, 3, -1, -3, 5, 3, 6, 7}, 3);
    std::cout << "sliding_window_max(k=3): ";
    for (int x : maxes) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
