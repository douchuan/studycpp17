#include "encoding_demo.h"

#include <iostream>

int main() {
    std::vector<uint8_t> data = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x21};

    std::cout << "=== 密码学编码 ===\n";
    std::cout << "Raw data: Hello!\n\n";

    auto hex = hex_encode(data);
    std::cout << "Hex:       " << hex << "\n";

    auto b64 = base64_encode(data);
    std::cout << "Base64:    " << b64 << "\n";

    auto b64url = base64url_encode(data);
    std::cout << "Base64URL: " << b64url << "\n";

    // Round-trip
    auto decoded_hex = hex_decode(hex);
    auto decoded_b64 = base64_decode(b64);
    std::cout << "\nHex round-trip:  " << std::string(decoded_hex.begin(), decoded_hex.end())
              << "\n";
    std::cout << "Base64 round-trip: " << std::string(decoded_b64.begin(), decoded_b64.end())
              << "\n";

    // DER ↔ PEM
    auto der = base64_decode(b64);
    auto pem =
        der_to_pem(std::string_view(reinterpret_cast<char*>(der.data()), der.size()), "TEST KEY");
    std::cout << "\nPEM:\n" << pem;

    return 0;
}
