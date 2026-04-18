#include "x25519_exchange_demo.h"

#include <iostream>

int main() {
    std::cout << "=== X25519（Curve25519）密钥交换 ===\n\n";

    auto alice = x25519_generate();
    auto bob = x25519_generate();

    std::cout << "Alice pub: ";
    for (auto b : alice.pub) printf("%02x", b);
    std::cout << "\n";

    std::cout << "Bob pub:   ";
    for (auto b : bob.pub) printf("%02x", b);
    std::cout << "\n\n";

    auto alice_shared = x25519_shared(alice.priv, bob.pub);
    auto bob_shared = x25519_shared(bob.priv, alice.pub);

    std::cout << "Alice shared: ";
    for (auto b : alice_shared) printf("%02x", b);
    std::cout << "\n";

    std::cout << "Bob shared:   ";
    for (auto b : bob_shared) printf("%02x", b);
    std::cout << "\n";

    std::cout << "Keys match: " << (alice_shared == bob_shared ? "YES" : "NO") << "\n";

    return 0;
}
