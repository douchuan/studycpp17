#ifndef STUDYCPP_HMAC_MAC_H
#define STUDYCPP_HMAC_MAC_H

// === HMAC（基于哈希的消息认证码） ===
// HMAC-SHA256 / HMAC-SHA512
// 使用场景：API 请求签名、Webhook 验证、JWT 签名
#include <openssl/hmac.h>

#include <cstdint>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> hmac_sha256(std::string_view key, std::string_view data) {
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    HMAC(EVP_sha256(), key.data(), static_cast<int>(key.size()),
         reinterpret_cast<const unsigned char*>(data.data()), data.size(), result, &len);
    return {result, result + len};
}

inline std::vector<uint8_t> hmac_sha512(std::string_view key, std::string_view data) {
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    HMAC(EVP_sha512(), key.data(), static_cast<int>(key.size()),
         reinterpret_cast<const unsigned char*>(data.data()), data.size(), result, &len);
    return {result, result + len};
}

#endif  // STUDYCPP_HMAC_MAC_H
