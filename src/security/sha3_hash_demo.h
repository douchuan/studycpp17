#ifndef STUDYCPP_SHA3_HASH_H
#define STUDYCPP_SHA3_HASH_H

// === SHA-3 系列哈希（Keccak） ===
// SHA3-256 / SHA3-512 / SHAKE128 / SHAKE256
// 使用场景：与 SHA-2 不同内部结构（海绵构造），可作为算法多样性备份
// SHAKE 为可扩展输出函数（XOF），可输出任意长度摘要
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> sha3_256(std::string_view data) {
    std::vector<uint8_t> digest(EVP_MAX_MD_SIZE);
    unsigned int len = 0;
    EVP_Digest(data.data(), data.size(), digest.data(), &len, EVP_sha3_256(), nullptr);
    digest.resize(len);
    return digest;
}

inline std::vector<uint8_t> sha3_512(std::string_view data) {
    std::vector<uint8_t> digest(EVP_MAX_MD_SIZE);
    unsigned int len = 0;
    EVP_Digest(data.data(), data.size(), digest.data(), &len, EVP_sha3_512(), nullptr);
    digest.resize(len);
    return digest;
}

// SHAKE128：XOF，输出长度可任意指定
inline std::vector<uint8_t> shake128(std::string_view data, size_t out_len) {
    std::vector<uint8_t> digest(out_len);
    EVP_Digest(data.data(), data.size(), digest.data(), nullptr, EVP_shake128(), nullptr);
    return digest;
}

// SHAKE256：XOF，安全性高于 SHAKE128
inline std::vector<uint8_t> shake256(std::string_view data, size_t out_len) {
    std::vector<uint8_t> digest(out_len);
    EVP_Digest(data.data(), data.size(), digest.data(), nullptr, EVP_shake256(), nullptr);
    return digest;
}

#endif  // STUDYCPP_SHA3_HASH_H
