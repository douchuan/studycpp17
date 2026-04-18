#ifndef STUDYCPP_AES_CBC_H
#define STUDYCPP_AES_CBC_H

// === AES-CBC（密码块链接模式） ===
// 传统块密码模式，需要 PKCS#7 填充 + 独立 HMAC 实现认证
// 使用场景：兼容旧系统（TLS 1.2 及以下、磁盘加密）
// 注意：不推荐新项目使用，优先选 AES-GCM
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> aes_cbc_encrypt(std::string_view key, std::string_view plaintext) {
    std::vector<uint8_t> iv(16);
    if (RAND_bytes(iv.data(), static_cast<int>(iv.size())) != 1)
        throw std::runtime_error("RAND_bytes failed");

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                       reinterpret_cast<const uint8_t*>(key.data()), iv.data());

    std::vector<uint8_t> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, total = 0;
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len,
                      reinterpret_cast<const uint8_t*>(plaintext.data()),
                      static_cast<int>(plaintext.size()));
    total = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + total, &len);
    total += len;
    ciphertext.resize(total);
    EVP_CIPHER_CTX_free(ctx);

    // 输出：IV + ciphertext
    std::vector<uint8_t> out = iv;
    out.insert(out.end(), ciphertext.begin(), ciphertext.end());
    return out;
}

inline std::vector<uint8_t> aes_cbc_decrypt(std::string_view key, std::string_view packed) {
    if (packed.size() < 16) throw std::runtime_error("packed too short");

    // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage)
    std::string_view iv(packed.data(), 16);
    std::string_view ciphertext(packed.data() + 16);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                       reinterpret_cast<const uint8_t*>(key.data()),
                       reinterpret_cast<const uint8_t*>(iv.data()));

    std::vector<uint8_t> plaintext(ciphertext.size() + 16);
    int len = 0, total = 0;
    EVP_DecryptUpdate(ctx, plaintext.data(), &len,
                      reinterpret_cast<const uint8_t*>(ciphertext.data()),
                      static_cast<int>(ciphertext.size()));
    total = len;
    EVP_DecryptFinal_ex(ctx, plaintext.data() + total, &len);
    total += len;
    plaintext.resize(total);
    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}

#endif  // STUDYCPP_AES_CBC_H
