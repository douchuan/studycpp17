#include "dh_exchange_demo.h"

#include <iostream>

int main() {
    std::cout << "=== Diffie-Hellman 密钥交换 ===\n\n";

    std::cout << "Generating DH parameters and key pairs (may take a moment)...\n";
    dh_classic_demo();
    std::cout << "Shared keys match: both parties derived the same secret\n";

    return 0;
}
