#ifndef STUDYCPP_X25519_EXCHANGE_H
#define STUDYCPP_X25519_EXCHANGE_H

// === X25519（Curve25519 密钥交换） ===
// 现代首选 ECDH 方案：32 字节密钥，高速、恒定时间、抗侧信道
// 使用场景：Signal 协议、TLS 1.3、WireGuard、SSH
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

// X25519 密钥对（32 字节公钥 + 32 字节私钥）
struct X25519KeyPair {
    std::vector<uint8_t> pub;   // 32 bytes
    std::vector<uint8_t> priv;  // 32 bytes
};

inline X25519KeyPair x25519_generate() {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_X25519, nullptr);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY* pkey = nullptr;
    EVP_PKEY_keygen(ctx, &pkey);
    EVP_PKEY_CTX_free(ctx);

    X25519KeyPair kp;
    kp.pub.resize(32);
    kp.priv.resize(32);
    size_t len = 32;
    EVP_PKEY_get_raw_public_key(pkey, kp.pub.data(), &len);
    len = 32;
    EVP_PKEY_get_raw_private_key(pkey, kp.priv.data(), &len);
    EVP_PKEY_free(pkey);
    return kp;
}

// 共享密钥派生
inline std::vector<uint8_t> x25519_shared(const std::vector<uint8_t>& my_priv,
                                          const std::vector<uint8_t>& peer_pub) {
    EVP_PKEY* priv =
        EVP_PKEY_new_raw_private_key(EVP_PKEY_X25519, nullptr, my_priv.data(), my_priv.size());
    EVP_PKEY* pub =
        EVP_PKEY_new_raw_public_key(EVP_PKEY_X25519, nullptr, peer_pub.data(), peer_pub.size());
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(priv, nullptr);
    EVP_PKEY_derive_init(ctx);
    EVP_PKEY_derive_set_peer(ctx, pub);
    size_t len = 0;
    EVP_PKEY_derive(ctx, nullptr, &len);
    std::vector<uint8_t> shared(len);
    EVP_PKEY_derive(ctx, shared.data(), &len);
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(priv);
    EVP_PKEY_free(pub);
    return shared;
}

#endif  // STUDYCPP_X25519_EXCHANGE_H
