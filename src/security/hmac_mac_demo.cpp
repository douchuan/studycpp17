#include "hmac_mac_demo.h"

#include <iostream>

int main() {
    std::string key = "my-secret-key";
    std::string data = "Hello, HMAC world!";

    std::cout << "=== HMAC 消息认证码 ===\n";
    std::cout << "Key:  \"" << key << "\"\n";
    std::cout << "Data: \"" << data << "\"\n\n";

    auto h256 = hmac_sha256(key, data);
    std::cout << "HMAC-SHA256: ";
    for (auto b : h256) printf("%02x", b);
    std::cout << "\n";

    auto h512 = hmac_sha512(key, data);
    std::cout << "HMAC-SHA512: ";
    for (auto b : h512) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
