#ifndef STUDYCPP_PBKDF2_KDF_H
#define STUDYCPP_PBKDF2_KDF_H

// === PBKDF2 密钥派生函数 ===
// PKCS#5 v2.0 / RFC 2898，基于 HMAC + 迭代次数增加破解成本
// 使用场景：WPA2、文件系统加密、旧系统兼容
// 推荐迭代次数：SHA256 至少 100,000
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> pbkdf2_derive(std::string_view password, std::string_view salt,
                                          int iterations, int key_len) {
    std::vector<uint8_t> key(key_len);
    PKCS5_PBKDF2_HMAC(password.data(), static_cast<int>(password.size()),
                      reinterpret_cast<const uint8_t*>(salt.data()), static_cast<int>(salt.size()),
                      iterations, EVP_sha256(), key_len, key.data());
    return key;
}

#endif  // STUDYCPP_PBKDF2_KDF_H
