#include "stringstream_demo.h"

#include <iostream>

int main() {
    // join
    std::cout << join({"a", "b", "c"}, '-') << "\n";
    std::cout << join({"hello", "world"}, ' ') << "\n";

    // parse_int
    int n;
    if (parse_int("42", n)) {
        std::cout << "parsed: " << n << "\n";
    }
    if (!parse_int("abc", n)) {
        std::cout << "failed to parse 'abc'\n";
    }

    // parse CSV
    auto values = parse_csv_line("1,2,3,4,5");
    std::cout << "csv values: ";
    for (int v : values) std::cout << v << " ";
    std::cout << "\n";

    // format
    std::cout << format_record(1, "Alice", 95.5) << "\n";

    return 0;
}
