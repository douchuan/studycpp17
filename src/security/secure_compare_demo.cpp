#include "secure_compare_demo.h"

#include <iostream>

int main() {
    std::cout << "=== 恒定时间比较 / 安全内存操作 ===\n\n";

    std::string a = "secret-token-abc123";
    std::string b = "secret-token-abc123";
    std::string c = "secret-token-xyz789";

    std::cout << "constant_time_compare(same):  "
              << (constant_time_compare(a, b) ? "EQUAL" : "DIFFERENT") << "\n";
    std::cout << "constant_time_compare(diff):  "
              << (constant_time_compare(a, c) ? "EQUAL" : "DIFFERENT") << "\n";

    std::vector<uint8_t> va = {0x01, 0x02, 0x03};
    std::vector<uint8_t> vb = {0x01, 0x02, 0x03};
    std::vector<uint8_t> vc = {0x01, 0x02, 0xFF};
    std::cout << "vec compare(same): " << (constant_time_compare(va, vb) ? "EQUAL" : "DIFFERENT")
              << "\n";
    std::cout << "vec compare(diff): " << (constant_time_compare(va, vc) ? "EQUAL" : "DIFFERENT")
              << "\n";

    // 安全清零
    std::vector<uint8_t> sensitive = {0xDE, 0xAD, 0xBE, 0xEF};
    std::cout << "Before wipe: ";
    for (auto b : sensitive) printf("%02x", b);
    std::cout << "\n";
    secure_zero(sensitive);
    std::cout << "After wipe:  size=" << sensitive.size() << "\n";

    return 0;
}
