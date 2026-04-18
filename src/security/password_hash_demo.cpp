#include "password_hash_demo.h"

#include <iostream>

int main() {
    std::string password = "MyP@ssw0rd!";
    std::string salt = "random-salt-16bytes!";

    std::cout << "=== 密码哈希（存储用） ===\n";
    std::cout << "Password: " << password << "\n\n";

    // PBKDF2
    auto pbkdf2_out = pbkdf2_hash(password, salt, 100000, 32);
    std::cout << "PBKDF2-SHA256 (100k iter): ";
    for (auto b : pbkdf2_out) printf("%02x", b);
    std::cout << "\n";
    std::cout << "PBKDF2 verify: "
              << (pbkdf2_verify(password, salt,
                                std::string_view(reinterpret_cast<char*>(pbkdf2_out.data()),
                                                 pbkdf2_out.size()))
                      ? "OK"
                      : "FAIL")
              << "\n\n";

    // scrypt
    auto sc = scrypt_hash(password, salt, 16384, 8, 1, 32);
    std::cout << "scrypt (N=16384, r=8, p=1): ";
    for (auto b : sc) printf("%02x", b);
    std::cout << "\n";
    std::cout << "scrypt verify: "
              << (scrypt_verify(password, salt,
                                std::string_view(reinterpret_cast<char*>(sc.data()), sc.size()))
                      ? "OK"
                      : "FAIL")
              << "\n";

    std::cout << "\n注意：Argon2id 需安装 libargon2（不在 OpenSSL 中）\n";
    std::cout << "  bcrypt 需独立库（不在 OpenSSL 中）\n";

    return 0;
}
