#include "backtracking_demo.h"

#include <iostream>

int main() {
    // permute
    auto perms = permute({1, 2, 3});
    std::cout << "permutations of {1,2,3} (" << perms.size() << "):\n";
    for (const auto& p : perms) {
        std::cout << "  [";
        for (size_t i = 0; i < p.size(); ++i) {
            if (i > 0) std::cout << ",";
            std::cout << p[i];
        }
        std::cout << "]\n";
    }

    // subsets
    auto subs = subsets({1, 2});
    std::cout << "subsets of {1,2} (" << subs.size() << "): ";
    for (const auto& s : subs) {
        std::cout << "[";
        for (size_t i = 0; i < s.size(); ++i) {
            if (i > 0) std::cout << ",";
            std::cout << s[i];
        }
        std::cout << "] ";
    }
    std::cout << "\n";

    // n-queens
    std::cout << "4-queens solutions: " << n_queens(4) << "\n";
    std::cout << "8-queens solutions: " << n_queens(8) << "\n";

    return 0;
}
