#include "inline_variables_demo.h"

#include <iostream>

int main() {
    std::cout << "PI = " << PI << "\n";
    std::cout << "E = " << E << "\n";

    increment_counter();
    increment_counter();
    std::cout << "counter = " << get_counter() << "\n";

    std::cout << "is_special_v<int>: " << std::boolalpha << is_special_v<int> << "\n";
    std::cout << "is_special_v<std::string>: " << is_special_v<std::string> << "\n";

    return 0;
}
