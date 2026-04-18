#include "aes_ctr_demo.h"

#include <iostream>

int main() {
    std::string key(32, '\0');
    for (int i = 0; i < 32; ++i) key[i] = static_cast<char>(i + 1);

    std::string data = "Hello, AES-CTR stream cipher!";

    std::cout << "=== AES-256-CTR 流密码模式 ===\n";
    std::cout << "Data: \"" << data << "\"\n\n";

    auto encrypted = aes_ctr_encrypt(key, data);
    std::cout << "Encrypted (nonce+CT, " << encrypted.size() << " bytes): ";
    for (auto b : encrypted) printf("%02x", b);
    std::cout << "\n";

    auto decrypted = aes_ctr_decrypt(
        key, std::string_view(reinterpret_cast<char*>(encrypted.data()), encrypted.size()));
    std::cout << "Decrypted: \"" << std::string(decrypted.begin(), decrypted.end()) << "\"\n";

    return 0;
}
