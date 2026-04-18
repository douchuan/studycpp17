#include "variant_demo.h"

#include <iostream>

int main() {
    std::vector<JsonValue> values = {make_int(42), 3.14, std::string("hello"), true};

    for (const auto& v : values) {
        std::cout << describe(v) << " | is_string=" << std::boolalpha << is_string(v)
                  << " | is_number=" << is_number(v) << "\n";
    }

    JsonValue n = make_int(99);
    std::cout << "to_number(99): " << to_number(n) << "\n";
    JsonValue d = 2.5;
    std::cout << "to_number(2.5): " << to_number(d) << "\n";

    return 0;
}
