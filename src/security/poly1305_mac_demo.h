#ifndef STUDYCPP_POLY1305_MAC_H
#define STUDYCPP_POLY1305_MAC_H

// === Poly1305 消息认证码 ===
// 使用 EVP_MAC API（OpenSSL 3.x）
#include <openssl/core_names.h>
#include <openssl/evp.h>

#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> poly1305_mac(std::string_view key, std::string_view data) {
    if (key.size() != 32) throw std::runtime_error("Poly1305 requires a 32-byte key");

    EVP_MAC* mac = EVP_MAC_fetch(nullptr, OSSL_MAC_NAME_POLY1305, nullptr);
    if (!mac) throw std::runtime_error("EVP_MAC_fetch POLY1305 failed");

    EVP_MAC_CTX* ctx = EVP_MAC_CTX_new(mac);
    OSSL_PARAM params[2];
    params[0] = OSSL_PARAM_construct_octet_string(
        OSSL_MAC_PARAM_KEY,
        const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(key.data())), key.size());
    params[1] = OSSL_PARAM_construct_end();
    EVP_MAC_init(ctx, nullptr, 0, params);
    EVP_MAC_update(ctx, reinterpret_cast<const unsigned char*>(data.data()), data.size());
    std::vector<uint8_t> out(16);
    size_t len = 0;
    EVP_MAC_final(ctx, out.data(), &len, out.size());
    out.resize(len);
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_free(mac);
    return out;
}

#endif  // STUDYCPP_POLY1305_MAC_H
