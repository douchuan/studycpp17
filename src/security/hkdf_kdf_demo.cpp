#include "hkdf_kdf_demo.h"

#include <iostream>

int main() {
    std::cout << "=== HKDF 密钥派生（Extract-then-Expand） ===\n\n";

    std::string ikm = "initial-key-material-secret";  // 输入密钥材料
    std::string salt = "random-salt-value";           // 盐
    std::string info = "app-v1-key-derivation";       // 上下文信息

    auto key = hkdf(ikm, salt, info, 32);
    std::cout << "IKM:  \"" << ikm << "\"\n";
    std::cout << "Salt: \"" << salt << "\"\n";
    std::cout << "Info: \"" << info << "\"\n\n";
    std::cout << "Derived key (32 bytes): ";
    for (auto b : key) printf("%02x", b);
    std::cout << "\n\n";

    // 派生多把子密钥
    auto enc_key = hkdf(ikm, salt, "encryption-key", 32);
    auto mac_key = hkdf(ikm, salt, "mac-key", 32);
    std::cout << "Encryption key: ";
    for (auto b : enc_key) printf("%02x", b);
    std::cout << "\n";
    std::cout << "MAC key:        ";
    for (auto b : mac_key) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
