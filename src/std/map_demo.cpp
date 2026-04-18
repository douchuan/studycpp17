#include "map_demo.h"

#include <iostream>

int main() {
    // map (ordered)
    auto m = build_map();
    std::cout << "ordered map: ";
    for (const auto& [k, v] : m) {
        std::cout << k << "=" << v << " ";
    }
    std::cout << "\n";

    // unordered_map
    auto um = build_unordered_map();
    std::cout << "unordered_map['apple'] = " << um["apple"] << "\n";

    // word count
    auto counts = word_count({"hello", "world", "hello", "cpp", "world", "hello"});
    std::cout << "word_count('hello'): " << counts["hello"] << "\n";
    std::cout << "word_count('cpp'): " << counts["cpp"] << "\n";

    // get_or_default
    std::cout << "get_or_default('missing', 42) = " << get_or_default(counts, "missing", 42)
              << "\n";
    std::cout << "get_or_default('cpp', 42) = " << get_or_default(counts, "cpp", 42) << "\n";

    return 0;
}
