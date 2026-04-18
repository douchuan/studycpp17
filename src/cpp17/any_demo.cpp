#include "any_demo.h"

#include <iostream>

int main() {
    std::any a = make_any_int(42);
    std::cout << describe_any(a) << "\n";

    a = make_any_str("hello");
    std::cout << describe_any(a) << "\n";

    a = 3.14;
    std::cout << describe_any(a) << "\n";

    // bad_any_cast 演示
    std::any x = 42;
    std::cout << "safe_get_string(42): " << safe_get_string(x) << "\n";
    std::any y = std::string("world");
    std::cout << "safe_get_string('world'): " << safe_get_string(y) << "\n";

    return 0;
}
