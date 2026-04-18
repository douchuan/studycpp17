#include "if_constexpr_demo.h"

#include <iostream>
#include <vector>

int main() {
    std::cout << describe(42) << "\n";
    std::cout << describe(3.14) << "\n";
    std::cout << describe(std::string("hello")) << "\n";
    std::cout << describe(std::vector<int>{}) << "\n";

    std::cout << "int is container? " << std::boolalpha << is_container_like<int>() << "\n";
    std::cout << "string is container? " << is_container_like<std::string>() << "\n";

    return 0;
}
