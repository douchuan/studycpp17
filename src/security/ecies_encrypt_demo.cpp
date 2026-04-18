#include "ecies_encrypt_demo.h"

#include <iostream>

int main() {
    std::cout << "=== ECIES 椭圆曲线集成加密 ===\n\n";

    auto receiver = ec_generate_key();
    std::cout << "Receiver EC P-256 key pair generated\n\n";

    std::string message = "Hello, ECIES!";
    std::cout << "Plaintext: \"" << message << "\"\n";

    auto packed = ecies_encrypt(receiver.pub_pem, message);
    std::cout << "Encrypted (" << packed.size() << " bytes)\n";

    auto decrypted = ecies_decrypt(
        receiver.priv_pem, std::string_view(reinterpret_cast<char*>(packed.data()), packed.size()));
    std::cout << "Decrypted: \"" << std::string(decrypted.begin(), decrypted.end()) << "\"\n";

    return 0;
}
