#ifndef STUDYCPP_HKDF_KDF_H
#define STUDYCPP_HKDF_KDF_H

// === HKDF（Extract-then-Expand 密钥派生） ===
// RFC 5869 标准：从任意熵输入派生密码学密钥
// 使用场景：TLS 1.3 密钥派生、DH 后处理、密钥分层派生
#include <openssl/evp.h>
#include <openssl/kdf.h>

#include <cstdint>
#include <string_view>
#include <vector>

// HKDF 完整流程：Extract + Expand
inline std::vector<uint8_t> hkdf(std::string_view ikm, std::string_view salt, std::string_view info,
                                 size_t out_len) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_HKDF, nullptr);
    EVP_PKEY_derive_init(ctx);
    EVP_PKEY_CTX_set_hkdf_md(ctx, EVP_sha256());
    EVP_PKEY_CTX_set1_hkdf_salt(ctx, reinterpret_cast<const uint8_t*>(salt.data()),
                                static_cast<int>(salt.size()));
    EVP_PKEY_CTX_set1_hkdf_key(ctx, reinterpret_cast<const uint8_t*>(ikm.data()),
                               static_cast<int>(ikm.size()));
    EVP_PKEY_CTX_add1_hkdf_info(ctx, reinterpret_cast<const uint8_t*>(info.data()),
                                static_cast<int>(info.size()));

    size_t len = 0;
    EVP_PKEY_derive(ctx, nullptr, &len);
    std::vector<uint8_t> out(out_len);
    len = out_len;
    EVP_PKEY_derive(ctx, out.data(), &len);
    EVP_PKEY_CTX_free(ctx);
    return out;
}

#endif  // STUDYCPP_HKDF_KDF_H
