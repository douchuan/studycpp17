#include "bit_manipulation_demo.h"

#include <iostream>

int main() {
    std::cout << "is_power_of_two(16): " << std::boolalpha << is_power_of_two(16) << "\n";
    std::cout << "is_power_of_two(14): " << is_power_of_two(14) << "\n";

    std::cout << "count_bits(13): " << count_bits(13) << "\n";  // 1101 -> 3

    std::cout << "single_number({4,1,2,1,2}): " << single_number({4, 1, 2, 1, 2}) << "\n";

    int a = 3, b = 5;
    swap_xor(a, b);
    std::cout << "swap_xor(3,5): a=" << a << ", b=" << b << "\n";

    std::cout << "reverse_bits(43261596): " << reverse_bits(43261596) << "\n";

    return 0;
}
