#include "search_demo.h"

#include <iostream>

int main() {
    std::vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "binary_search(5): " << std::boolalpha << binary_search(sorted, 5) << "\n";
    std::cout << "binary_search(10): " << binary_search(sorted, 10) << "\n";

    auto [min_val, max_val] = minmax(sorted);
    std::cout << "minmax: [" << min_val << ", " << max_val << "]\n";

    std::vector<int> with_dup = {1, 2, 2, 3, 2, 4};
    std::cout << "count_value(2): " << count_value(with_dup, 2) << "\n";

    return 0;
}
