#include "if_initializer_demo.h"

#include <iostream>

int main() {
    std::map<std::string, int> m = {{"apple", 1}, {"banana", 2}};
    std::cout << map_lookup(m, "banana") << "\n";
    std::cout << map_lookup(m, "cherry") << "\n";

    std::cout << classify_status(200) << "\n";
    std::cout << classify_status(404) << "\n";
    std::cout << classify_status(999) << "\n";

    std::cout << "10/3 = " << safe_divide_str(10.0, 3.0) << "\n";
    std::cout << "10/0 = " << safe_divide_str(10.0, 0.0) << "\n";

    return 0;
}
