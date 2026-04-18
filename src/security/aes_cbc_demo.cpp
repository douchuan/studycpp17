#include "aes_cbc_demo.h"

#include <iostream>

int main() {
    std::string key(32, '\0');
    for (int i = 0; i < 32; ++i) key[i] = static_cast<char>(i + 1);

    std::string plaintext = "Hello, AES-CBC world!";

    std::cout << "=== AES-256-CBC 加密 ===\n";
    std::cout << "Plaintext: \"" << plaintext << "\"\n\n";

    auto packed = aes_cbc_encrypt(key, plaintext);
    std::cout << "Packed (IV+CT, " << packed.size() << " bytes): ";
    for (auto b : packed) printf("%02x", b);
    std::cout << "\n";

    auto decrypted = aes_cbc_decrypt(
        key, std::string_view(reinterpret_cast<char*>(packed.data()), packed.size()));
    std::cout << "Decrypted: \"" << std::string(decrypted.begin(), decrypted.end()) << "\"\n";

    return 0;
}
