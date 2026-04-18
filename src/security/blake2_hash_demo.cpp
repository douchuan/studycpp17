#include "blake2_hash_demo.h"

#include <iostream>

int main() {
    std::string data = "BLAKE2 performance test";

    std::cout << "=== BLAKE2 高性能哈希 ===\n";
    std::cout << "Input: \"" << data << "\"\n\n";

    auto bs = blake2s(data);
    std::cout << "BLAKE2s-256: ";
    for (auto b : bs) printf("%02x", b);
    std::cout << "\n";

    auto bb = blake2b(data);
    std::cout << "BLAKE2b-512: ";
    for (auto b : bb) printf("%02x", b);
    std::cout << "\n";

    auto keyed = blake2b_keyed(data, "secret-key");
    std::cout << "BLAKE2b-keyed: ";
    for (auto b : keyed) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
