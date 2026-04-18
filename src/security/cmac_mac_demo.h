#ifndef STUDYCPP_CMAC_MAC_H
#define STUDYCPP_CMAC_MAC_H

// === CMAC（基于块密码的消息认证码） ===
// AES-CMAC：使用 AES 块密码构造 MAC，适合硬件 AES 加速环境
// 使用场景：NIST SP 800-38B 标准，物联网设备认证
#include <openssl/cmac.h>
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> aes_cmac(std::string_view key, std::string_view data) {
    // NOLINTBEGIN(clang-diagnostic-deprecated-declarations)
    // CMAC APIs are deprecated in OpenSSL 3.x but still supported for teaching purposes
    CMAC_CTX* ctx = CMAC_CTX_new();
    std::vector<uint8_t> out(EVP_MAX_BLOCK_LENGTH);
    size_t len = 0;
    CMAC_Init(ctx, key.data(), key.size(), EVP_aes_256_cbc(), nullptr);
    CMAC_Update(ctx, data.data(), data.size());
    CMAC_Final(ctx, out.data(), &len);
    out.resize(len);
    CMAC_CTX_free(ctx);
    // NOLINTEND(clang-diagnostic-deprecated-declarations)
    return out;
}

#endif  // STUDYCPP_CMAC_MAC_H
