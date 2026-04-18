#include "secure_random_demo.h"

#include <iostream>

int main() {
    std::cout << "=== CSPRNG 安全随机数 ===\n\n";

    auto bytes = secure_random_bytes(16);
    std::cout << "16 random bytes: ";
    for (auto b : bytes) printf("%02x", b);
    std::cout << "\n";

    std::cout << "Random [0, 100): " << secure_random_uint32(100) << "\n";
    std::cout << "Random hex(8): " << secure_random_hex(8) << "\n";
    std::cout << "Random base64url(24): " << secure_random_base64(24) << "\n";

    auto priv = secure_priv_bytes(32);
    std::cout << "Private key material(32): ";
    for (auto b : priv) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
