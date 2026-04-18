#include "pbkdf2_kdf_demo.h"

#include <iostream>

int main() {
    std::cout << "=== PBKDF2 密钥派生 ===\n\n";

    std::string password = "user-password-123";
    std::string salt = "random-salt-here!!";

    auto key32 = pbkdf2_derive(password, salt, 100000, 32);
    std::cout << "Password: \"" << password << "\"\n";
    std::cout << "Salt:     \"" << salt << "\"\n";
    std::cout << "Iter:     100000\n\n";
    std::cout << "Derived key (32 bytes): ";
    for (auto b : key32) printf("%02x", b);
    std::cout << "\n";

    // 不同迭代次数产生不同密钥
    auto key16 = pbkdf2_derive(password, salt, 10000, 16);
    std::cout << "Derived key (16 bytes, 10k iter): ";
    for (auto b : key16) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
