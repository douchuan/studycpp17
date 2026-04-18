#include "ecdsa_sign_demo.h"

#include <iostream>

int main() {
    std::cout << "=== ECDSA 数字签名（P-256） ===\n\n";

    auto keys = ecdsa_generate(NID_X9_62_prime256v1);
    std::cout << "ECDSA P-256 key pair generated\n";

    std::string data = "ECDSA signed message";
    std::cout << "Data: \"" << data << "\"\n\n";

    auto sig = ecdsa_sign(keys.priv_pem, data);
    std::cout << "Signature (" << sig.size() << " bytes): ";
    for (auto b : sig) printf("%02x", b);
    std::cout << "\n\n";

    bool ok = ecdsa_verify(keys.pub_pem, data,
                           std::string_view(reinterpret_cast<char*>(sig.data()), sig.size()));
    std::cout << "Verify: " << (ok ? "PASS" : "FAIL") << "\n";

    return 0;
}
