#include "mergesort_demo.h"

#include <iostream>

int main() {
    std::vector<int> a = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    merge_sort(a);
    std::cout << "merge_sort: ";
    for (int x : a) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> b = {2, 4, 1, 3, 5};
    std::cout << "inversions: " << count_inversions(b) << "\n";  // (2,1),(4,1),(4,3) = 3

    return 0;
}
