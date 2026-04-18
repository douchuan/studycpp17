#include "iterator_demo.h"

#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};

    // advance
    std::cout << "element at index 2: " << nth_element(v, 2) << "\n";

    // next
    auto it = find_n_steps(v.begin(), 3);
    std::cout << "next(begin, 3): " << *it << "\n";

    // back_inserter
    auto doubled = copy_and_double(v);
    std::cout << "doubled: ";
    for (int x : doubled) std::cout << x << " ";
    std::cout << "\n";

    // distance
    std::cout << "distance to 30: " << count_until(v, 30) << "\n";
    std::cout << "distance to 99: " << count_until(v, 99) << "\n";

    // for_each
    std::cout << "sum via for_each: " << sum_via_for_each(v) << "\n";

    return 0;
}
