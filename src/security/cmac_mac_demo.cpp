#include "cmac_mac_demo.h"

#include <iostream>

int main() {
    std::string key(32, '\xAB');  // 256-bit AES key
    std::string data = "AES-CMAC test message";

    std::cout << "=== CMAC（基于块密码的 MAC） ===\n";
    std::cout << "Key:  32-byte AES-256 key (0xAB...)\n";
    std::cout << "Data: \"" << data << "\"\n\n";

    auto mac = aes_cmac(key, data);
    std::cout << "AES-CMAC: ";
    for (auto b : mac) printf("%02x", b);
    std::cout << "\n";

    return 0;
}
