#ifndef STUDYCPP_AES_CTR_H
#define STUDYCPP_AES_CTR_H

// === AES-CTR（计数器模式流密码） ===
// 将块密码转为流密码，无需填充，支持并行加解密
// 使用场景：大文件加密、磁盘加密、需要随机访问的场景
// 注意：CTR 本身不提供完整性保护，需配合 HMAC 或 Poly1305
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> aes_ctr_encrypt(std::string_view key, std::string_view data) {
    std::vector<uint8_t> nonce(16);
    if (RAND_bytes(nonce.data(), static_cast<int>(nonce.size())) != 1)
        throw std::runtime_error("RAND_bytes failed");

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), nullptr,
                       reinterpret_cast<const uint8_t*>(key.data()), nonce.data());

    std::vector<uint8_t> output(data.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, total = 0;
    EVP_EncryptUpdate(ctx, output.data(), &len, reinterpret_cast<const uint8_t*>(data.data()),
                      static_cast<int>(data.size()));
    total = len;
    EVP_EncryptFinal_ex(ctx, output.data() + total, &len);
    total += len;
    output.resize(total);
    EVP_CIPHER_CTX_free(ctx);

    std::vector<uint8_t> out = nonce;
    out.insert(out.end(), output.begin(), output.end());
    return out;
}

// CTR 模式加解密操作相同
inline std::vector<uint8_t> aes_ctr_decrypt(std::string_view key, std::string_view packed) {
    // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage)
    std::string_view nonce(packed.data(), 16);
    std::string_view ciphertext(packed.data() + 16);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), nullptr,
                       reinterpret_cast<const uint8_t*>(key.data()),
                       reinterpret_cast<const uint8_t*>(nonce.data()));

    std::vector<uint8_t> output(ciphertext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, total = 0;
    EVP_DecryptUpdate(ctx, output.data(), &len, reinterpret_cast<const uint8_t*>(ciphertext.data()),
                      static_cast<int>(ciphertext.size()));
    total = len;
    EVP_DecryptFinal_ex(ctx, output.data() + total, &len);
    total += len;
    output.resize(total);
    EVP_CIPHER_CTX_free(ctx);
    return output;
}

#endif  // STUDYCPP_AES_CTR_H
