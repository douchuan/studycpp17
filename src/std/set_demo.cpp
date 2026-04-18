#include "set_demo.h"

#include <iostream>

int main() {
    std::set<int> s = unique_set({3, 1, 4, 1, 5, 9, 2, 6, 5});
    std::cout << "unique_set: ";
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";

    std::set<int> a = {1, 2, 3, 4, 5};
    std::set<int> b = {4, 5, 6, 7, 8};

    auto inter = set_intersection(a, b);
    std::cout << "intersection: ";
    for (int x : inter) std::cout << x << " ";
    std::cout << "\n";

    auto diff = set_difference(a, b);
    std::cout << "a - b: ";
    for (int x : diff) std::cout << x << " ";
    std::cout << "\n";

    std::unordered_set<std::string> tags = {"cpp", "learning", "demo"};
    std::cout << "contains('cpp'): " << std::boolalpha << contains(tags, "cpp") << "\n";
    std::cout << "contains('rust'): " << contains(tags, "rust") << "\n";

    return 0;
}
