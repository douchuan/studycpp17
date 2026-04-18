#include "sha3_hash_demo.h"

#include <iostream>

int main() {
    std::string data = "SHA-3 test message";

    std::cout << "=== SHA-3 系列哈希（Keccak） ===\n";
    std::cout << "Input: \"" << data << "\"\n\n";

    auto h3_256 = sha3_256(data);
    std::cout << "SHA3-256: ";
    for (auto b : h3_256) printf("%02x", b);
    std::cout << "\n";

    auto h3_512 = sha3_512(data);
    std::cout << "SHA3-512: ";
    for (auto b : h3_512) printf("%02x", b);
    std::cout << "\n";

    auto s128 = shake128(data, 32);
    std::cout << "SHAKE128 (32 bytes): ";
    for (auto b : s128) printf("%02x", b);
    std::cout << "\n";

    auto s256 = shake256(data, 32);
    std::cout << "SHAKE256 (32 bytes): ";
    for (auto b : s256) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
