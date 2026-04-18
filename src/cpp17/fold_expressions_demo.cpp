#include "fold_expressions_demo.h"

#include <iostream>
#include <string>

int main() {
    std::cout << "sum(1,2,3,4): " << sum(1, 2, 3, 4) << "\n";
    std::cout << "product(2,3,4): " << product(2, 3, 4) << "\n";
    std::cout << "sum_with_offset(10, 1,2,3): " << sum_with_offset(10, 1, 2, 3) << "\n";
    std::cout << "all_true(T,T,T): " << std::boolalpha << all_true(true, true, true) << "\n";
    std::cout << "all_true(T,F,T): " << all_true(true, false, true) << "\n";

    return 0;
}
