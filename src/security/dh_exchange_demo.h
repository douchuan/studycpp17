#ifndef STUDYCPP_DH_EXCHANGE_H
#define STUDYCPP_DH_EXCHANGE_H

// === Diffie-Hellman 密钥交换 ===
// 经典 DH（大整数群）/ ECDH（椭圆曲线）
// 使用场景：TLS 握手、安全信道建立、端到端加密初始化
#include <openssl/dh.h>
#include <openssl/evp.h>

#include <cstdint>
#include <vector>

// 经典 DH 参数生成 + 密钥交换
inline void dh_classic_demo() {
    // 生成 DH 参数（实际生产应使用标准 RFC 3526 组）
    EVP_PKEY_CTX* param_ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_DH, nullptr);
    EVP_PKEY_paramgen_init(param_ctx);
    EVP_PKEY_CTX_set_dh_paramgen_prime_len(param_ctx, 2048);
    EVP_PKEY* params = nullptr;
    EVP_PKEY_paramgen(param_ctx, &params);
    EVP_PKEY_CTX_free(param_ctx);

    // Alice 生成密钥对
    EVP_PKEY_CTX* alice_ctx = EVP_PKEY_CTX_new(params, nullptr);
    EVP_PKEY_keygen_init(alice_ctx);
    EVP_PKEY* alice_key = nullptr;
    EVP_PKEY_keygen(alice_ctx, &alice_key);
    EVP_PKEY_CTX_free(alice_ctx);

    // Bob 生成密钥对
    EVP_PKEY_CTX* bob_ctx = EVP_PKEY_CTX_new(params, nullptr);
    EVP_PKEY_keygen_init(bob_ctx);
    EVP_PKEY* bob_key = nullptr;
    EVP_PKEY_keygen(bob_ctx, &bob_key);
    EVP_PKEY_CTX_free(bob_ctx);

    // Alice 计算共享密钥
    EVP_PKEY_CTX* a_ctx = EVP_PKEY_CTX_new(alice_key, nullptr);
    EVP_PKEY_derive_init(a_ctx);
    EVP_PKEY_derive_set_peer(a_ctx, bob_key);
    size_t a_len = 0;
    EVP_PKEY_derive(a_ctx, nullptr, &a_len);
    std::vector<uint8_t> alice_shared(a_len);
    EVP_PKEY_derive(a_ctx, alice_shared.data(), &a_len);
    EVP_PKEY_CTX_free(a_ctx);

    // Bob 计算共享密钥
    EVP_PKEY_CTX* b_ctx = EVP_PKEY_CTX_new(bob_key, nullptr);
    EVP_PKEY_derive_init(b_ctx);
    EVP_PKEY_derive_set_peer(b_ctx, alice_key);
    size_t b_len = 0;
    EVP_PKEY_derive(b_ctx, nullptr, &b_len);
    std::vector<uint8_t> bob_shared(b_len);
    EVP_PKEY_derive(b_ctx, bob_shared.data(), &b_len);
    EVP_PKEY_CTX_free(b_ctx);

    // 双方共享密钥应相同
    bool match = (alice_shared == bob_shared);
    (void)match;

    EVP_PKEY_free(params);
    EVP_PKEY_free(alice_key);
    EVP_PKEY_free(bob_key);
}

#endif  // STUDYCPP_DH_EXCHANGE_H
