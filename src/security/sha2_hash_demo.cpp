#include "sha2_hash_demo.h"

#include <iostream>

int main() {
    std::string data = "The quick brown fox jumps over the lazy dog";

    std::cout << "=== SHA-2 系列哈希 ===\n";
    std::cout << "Input: \"" << data << "\"\n\n";

    auto h256 = sha256(data);
    std::cout << "SHA-256:   ";
    for (auto b : h256) printf("%02x", b);
    std::cout << "\n";

    auto h384 = sha384(data);
    std::cout << "SHA-384:   ";
    for (auto b : h384) printf("%02x", b);
    std::cout << "\n";

    auto h512 = sha512(data);
    std::cout << "SHA-512:   ";
    for (auto b : h512) printf("%02x", b);
    std::cout << "\n";

    auto h512_256 = sha512_256(data);
    std::cout << "SHA-512/256:";
    for (auto b : h512_256) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
