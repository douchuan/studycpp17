#include "poly1305_mac_demo.h"

#include <iostream>

int main() {
    std::string key(32, '\x00');  // 32-byte Poly1305 key
    for (int i = 0; i < 32; ++i) key[i] = static_cast<char>(i);
    std::string data = "Poly1305 test data";

    std::cout << "=== Poly1305 消息认证码 ===\n";
    std::cout << "Data: \"" << data << "\"\n\n";

    auto mac = poly1305_mac(key, data);
    std::cout << "Poly1305 MAC (" << mac.size() << " bytes): ";
    for (auto b : mac) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
