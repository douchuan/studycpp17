#ifndef STUDYCPP_ED25519_SIGN_H
#define STUDYCPP_ED25519_SIGN_H

// === Ed25519 数字签名（EdDSA） ===
// 现代首选签名方案：64 字节签名、32 字节密钥、恒定时间、无随机数依赖
// 使用场景：SSH 密钥、TLS 1.3、Signal 协议、Git 签名
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

struct Ed25519Keys {
    std::vector<uint8_t> pub;   // 32 bytes
    std::vector<uint8_t> priv;  // 32 bytes (seed)
};

inline Ed25519Keys ed25519_generate() {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, nullptr);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY* pkey = nullptr;
    EVP_PKEY_keygen(ctx, &pkey);
    EVP_PKEY_CTX_free(ctx);

    Ed25519Keys keys;
    keys.pub.resize(32);
    keys.priv.resize(32);
    size_t len = 32;
    EVP_PKEY_get_raw_public_key(pkey, keys.pub.data(), &len);
    len = 32;
    EVP_PKEY_get_raw_private_key(pkey, keys.priv.data(), &len);
    EVP_PKEY_free(pkey);
    return keys;
}

// Ed25519 签名（64 字节）
inline std::vector<uint8_t> ed25519_sign(const std::vector<uint8_t>& priv, std::string_view data) {
    EVP_PKEY* pkey =
        EVP_PKEY_new_raw_private_key(EVP_PKEY_ED25519, nullptr, priv.data(), priv.size());
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestSignInit(ctx, nullptr, nullptr, nullptr, pkey);
    // Ed25519 requires one-shot sign
    size_t len = 0;
    EVP_DigestSign(ctx, nullptr, &len, reinterpret_cast<const uint8_t*>(data.data()), data.size());
    std::vector<uint8_t> sig(len);
    EVP_DigestSign(ctx, sig.data(), &len, reinterpret_cast<const uint8_t*>(data.data()),
                   data.size());
    EVP_MD_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return sig;
}

// Ed25519 验证
inline bool ed25519_verify(const std::vector<uint8_t>& pub, std::string_view data,
                           std::string_view signature) {
    EVP_PKEY* pkey = EVP_PKEY_new_raw_public_key(EVP_PKEY_ED25519, nullptr, pub.data(), pub.size());
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestVerifyInit(ctx, nullptr, nullptr, nullptr, pkey);
    bool ok =
        EVP_DigestVerify(ctx, reinterpret_cast<const uint8_t*>(signature.data()), signature.size(),
                         reinterpret_cast<const uint8_t*>(data.data()), data.size()) == 1;
    EVP_MD_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return ok;
}

#endif  // STUDYCPP_ED25519_SIGN_H
