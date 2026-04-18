#include "chacha20_poly1305_demo.h"

#include <iostream>

int main() {
    std::string key(32, '\0');
    for (int i = 0; i < 32; ++i) key[i] = static_cast<char>(i + 1);

    std::string plaintext = "Hello, ChaCha20-Poly1305! Modern AEAD cipher.";

    std::cout << "=== ChaCha20-Poly1305（AEAD 流密码） ===\n";
    std::cout << "Plaintext: \"" << plaintext << "\"\n\n";

    auto packed = chacha20_poly1305_encrypt(key, plaintext);
    std::cout << "Packed (nonce+CT+TAG, " << packed.size() << " bytes): ";
    for (auto b : packed) printf("%02x", b);
    std::cout << "\n";

    auto decrypted = chacha20_poly1305_decrypt(
        key, std::string_view(reinterpret_cast<char*>(packed.data()), packed.size()));
    std::cout << "Decrypted: \"" << std::string(decrypted.begin(), decrypted.end()) << "\"\n";

    return 0;
}
