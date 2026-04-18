#include "iterator_pattern_demo.h"

#include <iostream>

int main() {
    std::vector<int> nums = {10, 20, 30, 40};
    VectorIterator<int> it(nums);
    while (it.has_next()) std::cout << it.next() << " ";
    std::cout << "\n";
    return 0;
}
