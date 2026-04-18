#include "pkcs7_padding_demo.h"

#include <iostream>

int main() {
    std::cout << "=== PKCS#7 / ISO 7816-4 填充 ===\n\n";

    std::string data1 = "Hello";             // 5 bytes → +11 padding
    std::string data2 = "1234567890ABCDEF";  // 16 bytes → +16 padding (full block)
    std::string data3 = "Exactly16bytes!!";  // 16 bytes

    for (auto& data : {data1, data2, data3}) {
        auto padded = pkcs7_pad(data);
        std::cout << "PKCS#7 pad(\"" << data << "\") → " << padded.size() << " bytes: ";
        for (auto b : padded) printf("%02x ", b);
        std::cout << "\n";

        auto unpadded = pkcs7_unpad(padded);
        std::cout << "  Unpadded: \"" << std::string(unpadded.begin(), unpadded.end()) << "\"\n";
    }

    std::cout << "\n";

    std::string data4 = "ISO test";
    auto iso_padded = iso7816_pad(data4);
    std::cout << "ISO 7816 pad(\"" << data4 << "\") → " << iso_padded.size() << " bytes: ";
    for (auto b : iso_padded) printf("%02x ", b);
    std::cout << "\n";

    auto iso_unpadded = iso7816_unpad(iso_padded);
    std::cout << "  Unpadded: \"" << std::string(iso_unpadded.begin(), iso_unpadded.end())
              << "\"\n";

    return 0;
}
