#include "aes_gcm_demo.h"

#include <iostream>

int main() {
    std::string key(32, '\0');
    for (int i = 0; i < 32; ++i) key[i] = static_cast<char>(i + 1);

    std::string plaintext = "Hello, AES-GCM world! Sensitive data here.";

    std::cout << "=== AES-256-GAE 认证加密 ===\n";
    std::cout << "Plaintext: \"" << plaintext << "\"\n\n";

    auto [packed, tag] = aes_gcm_encrypt(key, plaintext);
    std::cout << "Packed (IV+CT+TAG, " << packed.size() << " bytes): ";
    for (auto b : packed) printf("%02x", b);
    std::cout << "\n";

    auto decrypted = aes_gcm_decrypt(
        key, std::string_view(reinterpret_cast<char*>(packed.data()), packed.size()));
    std::cout << "Decrypted: \"" << std::string(decrypted.begin(), decrypted.end()) << "\"\n";

    // Tamper test
    std::vector<uint8_t> tampered = packed;
    tampered[20] ^= 0xFF;
    try {
        aes_gcm_decrypt(
            key, std::string_view(reinterpret_cast<char*>(tampered.data()), tampered.size()));
        std::cout << "ERROR: should have failed!\n";
    } catch (const std::exception& e) {
        std::cout << "Tamper detected: " << e.what() << "\n";
    }

    return 0;
}
