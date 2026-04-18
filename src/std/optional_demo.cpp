#include "optional_demo.h"

#include <iostream>

int main() {
    // dict_lookup
    std::unordered_map<std::string, int> dict = {{"apple", 1}, {"banana", 2}};
    auto result = dict_lookup(dict, "apple");
    if (result) {
        std::cout << "dict_lookup('apple'): " << *result << "\n";
    }
    result = dict_lookup(dict, "cherry");
    if (!result) {
        std::cout << "dict_lookup('cherry'): not found\n";
    }

    // safe_divide
    auto div = safe_divide(10.0, 3.0);
    if (div) std::cout << "safe_divide(10, 3): " << *div << "\n";
    div = safe_divide(10.0, 0.0);
    if (!div) std::cout << "safe_divide(10, 0): undefined\n";

    // add_optionals
    auto s = add_optionals(3, 4);
    if (s) std::cout << "add_optionals(3, 4): " << *s << "\n";
    s = add_optionals(3, std::nullopt);
    if (!s) std::cout << "add_optionals(3, nullopt): nullopt\n";

    return 0;
}
