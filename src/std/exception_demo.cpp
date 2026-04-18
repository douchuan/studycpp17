#include "exception_demo.h"

#include <iostream>

int main() {
    // safe_divide
    try {
        std::cout << "10 / 3 = " << checked_divide(10, 3) << "\n";
        std::cout << "10 / 0 = " << checked_divide(10, 0) << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "caught: " << e.what() << "\n";
    }

    // clamp_range
    try {
        std::cout << "clamp(5, 1, 10) = " << clamp_range(5, 1, 10) << "\n";
        std::cout << "clamp(20, 1, 10) = " << clamp_range(20, 1, 10) << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "caught: " << e.what() << "\n";
    }

    // validate_positive
    try {
        validate_positive(10);
        validate_positive(-5);
    } catch (const ValidationError& e) {
        std::cout << "validation: " << e.what() << "\n";
    }

    // noexcept parse
    int result;
    std::cout << "try_parse_int('42'): " << std::boolalpha << try_parse_int("42", result) << " -> "
              << result << "\n";
    std::cout << "try_parse_int('abc'): " << try_parse_int("abc", result) << "\n";

    return 0;
}
