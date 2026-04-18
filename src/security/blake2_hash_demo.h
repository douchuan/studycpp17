#ifndef STUDYCPP_BLAKE2_HASH_H
#define STUDYCPP_BLAKE2_HASH_H

// === BLAKE2 高性能哈希 ===
// BLAKE2s（32 位优化，256 位输出）/ BLAKE2b（64 位优化，512 位输出）
// 使用场景：需要高性能哈希的场景（文件校验、数据指纹），速度优于 SHA-2/SHA-3
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> blake2s(std::string_view data) {
    std::vector<uint8_t> digest(EVP_MAX_MD_SIZE);
    unsigned int len = 0;
    EVP_Digest(data.data(), data.size(), digest.data(), &len, EVP_blake2s256(), nullptr);
    digest.resize(len);
    return digest;
}

inline std::vector<uint8_t> blake2b(std::string_view data) {
    std::vector<uint8_t> digest(EVP_MAX_MD_SIZE);
    unsigned int len = 0;
    EVP_Digest(data.data(), data.size(), digest.data(), &len, EVP_blake2b512(), nullptr);
    digest.resize(len);
    return digest;
}

// 带密钥的 BLAKE2b（可用作 MAC）
inline std::vector<uint8_t> blake2b_keyed(std::string_view data, std::string_view key) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_PKEY* pkey =
        EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, nullptr, reinterpret_cast<const uint8_t*>(key.data()),
                             static_cast<int>(key.size()));
    EVP_DigestSignInit(ctx, nullptr, EVP_blake2b512(), nullptr, pkey);
    EVP_DigestSignUpdate(ctx, data.data(), data.size());
    size_t len = 0;
    EVP_DigestSignFinal(ctx, nullptr, &len);
    std::vector<uint8_t> digest(len);
    EVP_DigestSignFinal(ctx, digest.data(), &len);
    EVP_PKEY_free(pkey);
    EVP_MD_CTX_free(ctx);
    return digest;
}

#endif  // STUDYCPP_BLAKE2_HASH_H
