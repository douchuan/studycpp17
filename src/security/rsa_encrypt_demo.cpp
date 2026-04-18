#include "rsa_encrypt_demo.h"

#include <iostream>

int main() {
    std::cout << "=== RSA-OAEP 非对称加密 ===\n\n";

    auto keys = rsa_generate_key(2048);
    std::cout << "RSA-2048 key pair generated\n";
    std::cout << "Public key (PEM, " << keys.pub_pem.size() << " bytes)\n";
    std::cout << "Private key (PEM, " << keys.priv_pem.size() << " bytes)\n\n";

    std::string message = "Hello, RSA!";
    std::cout << "Plaintext: \"" << message << "\"\n";

    auto ct = rsa_oaep_encrypt(keys.pub_pem, message);
    std::cout << "Ciphertext (" << ct.size() << " bytes): ";
    for (auto b : ct) printf("%02x", b);
    std::cout << "\n";

    auto pt = rsa_oaep_decrypt(keys.priv_pem,
                               std::string_view(reinterpret_cast<char*>(ct.data()), ct.size()));
    std::cout << "Decrypted: \"" << std::string(pt.begin(), pt.end()) << "\"\n";

    return 0;
}
