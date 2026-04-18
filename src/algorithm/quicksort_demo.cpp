#include "quicksort_demo.h"

#include <iostream>

int main() {
    std::vector<int> a = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    quick_sort(a);
    std::cout << "quick_sort: ";
    for (int x : a) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> b = {3, 2, 1, 5, 6, 4};
    std::cout << "2nd largest: " << quick_select(b, 2) << "\n";

    return 0;
}
