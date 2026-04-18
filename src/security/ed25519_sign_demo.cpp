#include "ed25519_sign_demo.h"

#include <iostream>

int main() {
    std::cout << "=== Ed25519 数字签名（EdDSA） ===\n\n";

    auto keys = ed25519_generate();
    std::cout << "Ed25519 key pair generated\n";
    std::cout << "Public key (32 bytes):  ";
    for (auto b : keys.pub) printf("%02x", b);
    std::cout << "\n\n";

    std::string data = "Ed25519 signed message";
    std::cout << "Data: \"" << data << "\"\n";

    auto sig = ed25519_sign(keys.priv, data);
    std::cout << "Signature (" << sig.size() << " bytes): ";
    for (auto b : sig) printf("%02x", b);
    std::cout << "\n\n";

    bool ok = ed25519_verify(keys.pub, data,
                             std::string_view(reinterpret_cast<char*>(sig.data()), sig.size()));
    std::cout << "Verify original: " << (ok ? "PASS" : "FAIL") << "\n";

    std::string tampered = data + "!";
    ok = ed25519_verify(keys.pub, tampered,
                        std::string_view(reinterpret_cast<char*>(sig.data()), sig.size()));
    std::cout << "Verify tampered: " << (ok ? "PASS (WRONG!)" : "FAIL (correct)") << "\n";

    return 0;
}
