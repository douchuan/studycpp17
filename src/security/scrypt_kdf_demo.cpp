#include "scrypt_kdf_demo.h"

#include <iostream>

int main() {
    std::cout << "=== scrypt 密钥派生 ===\n\n";

    std::string password = "secure-password";
    std::string salt = "unique-salt-value";

    auto key = scrypt_derive(password, salt, 16384, 8, 1, 32);
    std::cout << "Password: \"" << password << "\"\n";
    std::cout << "Salt:     \"" << salt << "\"\n";
    std::cout << "Params:   N=16384, r=8, p=1\n\n";
    std::cout << "Derived key (32 bytes): ";
    for (auto b : key) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
