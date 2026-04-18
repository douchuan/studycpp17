#ifndef STUDYCPP_CHACHA20_POLY1305_H
#define STUDYCPP_CHACHA20_POLY1305_H

// === ChaCha20-Poly1305（AEAD 流密码） ===
// Google 首选 AEAD 方案（无 AES 硬件加速时性能优于 AES-GCM）
// 使用场景：TLS 1.3 标准套件、移动端加密、非 AES-NI 环境
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> chacha20_poly1305_encrypt(std::string_view key,
                                                      std::string_view plaintext) {
    std::vector<uint8_t> nonce(12);
    if (RAND_bytes(nonce.data(), static_cast<int>(nonce.size())) != 1)
        throw std::runtime_error("RAND_bytes failed");

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_chacha20_poly1305(), nullptr, nullptr, nullptr);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, static_cast<int>(nonce.size()), nullptr);
    EVP_EncryptInit_ex(ctx, nullptr, nullptr, reinterpret_cast<const uint8_t*>(key.data()),
                       nonce.data());

    std::vector<uint8_t> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, total = 0;
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len,
                      reinterpret_cast<const uint8_t*>(plaintext.data()),
                      static_cast<int>(plaintext.size()));
    total = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + total, &len);
    total += len;
    ciphertext.resize(total);

    std::vector<uint8_t> tag(16);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_GET_TAG, static_cast<int>(tag.size()), tag.data());
    EVP_CIPHER_CTX_free(ctx);

    std::vector<uint8_t> out = nonce;
    out.insert(out.end(), ciphertext.begin(), ciphertext.end());
    out.insert(out.end(), tag.begin(), tag.end());
    return out;
}

inline std::vector<uint8_t> chacha20_poly1305_decrypt(std::string_view key,
                                                      std::string_view packed) {
    if (packed.size() < 12 + 16) throw std::runtime_error("packed too short");

    // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage)
    std::string_view nonce(packed.data(), 12);
    std::string_view ciphertext(packed.data() + 12, packed.size() - 12 - 16);
    std::string_view tag(packed.data() + packed.size() - 16, 16);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_chacha20_poly1305(), nullptr, nullptr, nullptr);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, static_cast<int>(nonce.size()), nullptr);
    EVP_DecryptInit_ex(ctx, nullptr, nullptr, reinterpret_cast<const uint8_t*>(key.data()),
                       reinterpret_cast<const uint8_t*>(nonce.data()));

    std::vector<uint8_t> plaintext(ciphertext.size() + 16);
    int len = 0, total = 0;
    EVP_DecryptUpdate(ctx, plaintext.data(), &len,
                      reinterpret_cast<const uint8_t*>(ciphertext.data()),
                      static_cast<int>(ciphertext.size()));
    total = len;
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, static_cast<int>(tag.size()),
                        const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(tag.data())));
    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + total, &len) <= 0) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("ChaCha20-Poly1305 authentication failed");
    }
    total += len;
    plaintext.resize(total);
    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}

#endif  // STUDYCPP_CHACHA20_POLY1305_H
