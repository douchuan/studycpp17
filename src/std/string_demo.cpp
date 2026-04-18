#include "string_demo.h"

#include <iostream>

int main() {
    // split
    auto tokens = split("hello,world,cpp", ',');
    std::cout << "split: ";
    for (const auto& t : tokens) {
        std::cout << "[" << t << "] ";
    }
    std::cout << "\n";

    // trim
    std::cout << "trim: '" << trim("  hello world  ") << "'\n";

    // palindrome
    std::cout << "is_palindrome('racecar'): " << std::boolalpha << is_palindrome("racecar") << "\n";
    std::cout << "is_palindrome('hello'): " << is_palindrome("hello") << "\n";

    return 0;
}
