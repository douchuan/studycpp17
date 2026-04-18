#ifndef STUDYCPP_AES_GCM_H
#define STUDYCPP_AES_GCM_H

// === AES-GCM（AEAD 认证加密） ===
// 现代安全标准首选：同时提供机密性和完整性
// 使用场景：数据库加密、API 载荷加密、安全通信
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <vector>

// AES-256-GCM 加密
inline std::pair<std::vector<uint8_t>, std::vector<uint8_t>> aes_gcm_encrypt(
    std::string_view key, std::string_view plaintext) {
    // 生成随机 IV（12 字节为 GCM 推荐值）
    std::vector<uint8_t> iv(12);
    if (RAND_bytes(iv.data(), static_cast<int>(iv.size())) != 1)
        throw std::runtime_error("RAND_bytes failed");

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, static_cast<int>(iv.size()), nullptr);
    EVP_EncryptInit_ex(ctx, nullptr, nullptr, reinterpret_cast<const uint8_t*>(key.data()),
                       iv.data());

    int len = 0;
    std::vector<uint8_t> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len,
                      reinterpret_cast<const uint8_t*>(plaintext.data()),
                      static_cast<int>(plaintext.size()));
    int total = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + total, &len);
    total += len;
    ciphertext.resize(total);

    // 获取 16 字节认证 tag
    std::vector<uint8_t> tag(16);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, static_cast<int>(tag.size()), tag.data());
    EVP_CIPHER_CTX_free(ctx);

    // 返回 IV + ciphertext 拼接（tag 附在最后）
    std::vector<uint8_t> result = iv;
    result.insert(result.end(), ciphertext.begin(), ciphertext.end());
    result.insert(result.end(), tag.begin(), tag.end());
    return {result, tag};
}

// AES-256-GCM 解密
inline std::vector<uint8_t> aes_gcm_decrypt(std::string_view key, std::string_view packed) {
    if (packed.size() < 12 + 16) throw std::runtime_error("packed too short");

    // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage)
    std::string_view iv(packed.data(), 12);
    std::string_view ciphertext(packed.data() + 12, packed.size() - 12 - 16);
    std::string_view tag(packed.data() + packed.size() - 16, 16);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, static_cast<int>(iv.size()), nullptr);
    EVP_DecryptInit_ex(ctx, nullptr, nullptr, reinterpret_cast<const uint8_t*>(key.data()),
                       reinterpret_cast<const uint8_t*>(iv.data()));

    int len = 0;
    std::vector<uint8_t> plaintext(ciphertext.size() + 16);
    EVP_DecryptUpdate(ctx, plaintext.data(), &len,
                      reinterpret_cast<const uint8_t*>(ciphertext.data()),
                      static_cast<int>(ciphertext.size()));
    int total = len;
    // 设置期望的 tag，验证失败返回负值
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, static_cast<int>(tag.size()),
                        const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(tag.data())));
    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + total, &len) <= 0) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("GCM authentication failed");
    }
    total += len;
    plaintext.resize(total);
    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}

#endif  // STUDYCPP_AES_GCM_H
