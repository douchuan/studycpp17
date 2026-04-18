#ifndef STUDYCPP_SHA2_HASH_H
#define STUDYCPP_SHA2_HASH_H

// === SHA-2 系列哈希 ===
// SHA256 / SHA384 / SHA512 / SHA512/256
// 使用场景：数据完整性校验、数字签名前置哈希、Merkle 树
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> sha256(std::string_view data) {
    std::vector<uint8_t> digest(EVP_MAX_MD_SIZE);
    unsigned int len = 0;
    EVP_Digest(data.data(), data.size(), digest.data(), &len, EVP_sha256(), nullptr);
    digest.resize(len);
    return digest;
}

inline std::vector<uint8_t> sha384(std::string_view data) {
    std::vector<uint8_t> digest(EVP_MAX_MD_SIZE);
    unsigned int len = 0;
    EVP_Digest(data.data(), data.size(), digest.data(), &len, EVP_sha384(), nullptr);
    digest.resize(len);
    return digest;
}

inline std::vector<uint8_t> sha512(std::string_view data) {
    std::vector<uint8_t> digest(EVP_MAX_MD_SIZE);
    unsigned int len = 0;
    EVP_Digest(data.data(), data.size(), digest.data(), &len, EVP_sha512(), nullptr);
    digest.resize(len);
    return digest;
}

// SHA512/256：截断版 SHA512，抗长度扩展攻击
inline std::vector<uint8_t> sha512_256(std::string_view data) {
    std::vector<uint8_t> digest(EVP_MAX_MD_SIZE);
    unsigned int len = 0;
    EVP_Digest(data.data(), data.size(), digest.data(), &len, EVP_sha512_256(), nullptr);
    digest.resize(len);
    return digest;
}

#endif  // STUDYCPP_SHA2_HASH_H
