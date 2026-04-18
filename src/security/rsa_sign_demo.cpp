#include "rsa_sign_demo.h"

#include <iostream>

int main() {
    std::cout << "=== RSA-PSS 数字签名 ===\n\n";

    auto keys = rsa_sign_generate(2048);
    std::cout << "RSA-2048 key pair generated\n";

    std::string data = "Sign this important document";
    std::cout << "Data: \"" << data << "\"\n\n";

    auto sig = rsa_pss_sign(keys.priv_pem, data);
    std::cout << "Signature (" << sig.size() << " bytes): ";
    for (auto b : sig) printf("%02x", b);
    std::cout << "\n\n";

    bool ok = rsa_pss_verify(keys.pub_pem, data,
                             std::string_view(reinterpret_cast<char*>(sig.data()), sig.size()));
    std::cout << "Verify original: " << (ok ? "PASS" : "FAIL") << "\n";

    std::string tampered = data + " modified";
    ok = rsa_pss_verify(keys.pub_pem, tampered,
                        std::string_view(reinterpret_cast<char*>(sig.data()), sig.size()));
    std::cout << "Verify tampered: " << (ok ? "PASS (WRONG!)" : "FAIL (correct, tamper detected)")
              << "\n";

    return 0;
}
