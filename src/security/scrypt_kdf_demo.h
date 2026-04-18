#ifndef STUDYCPP_SCRYPT_KDF_H
#define STUDYCPP_SCRYPT_KDF_H

// === scrypt 密钥派生 ===
// 内存硬函数：通过大量内存访问抵抗 GPU/ASIC 暴力破解
// 使用场景：现代密码存储、Tarsnap、加密货币钱包
// 参数：N=CPU/内存成本 (2^14=16384)、r=块大小(8)、p=并行度(1)
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

inline std::vector<uint8_t> scrypt_derive(std::string_view password, std::string_view salt,
                                          uint64_t n, int r, int p, int key_len) {
    std::vector<uint8_t> key(key_len);
    if (EVP_PBE_scrypt(password.data(), password.size(),
                       reinterpret_cast<const uint8_t*>(salt.data()), salt.size(), n, r, p, 0,
                       key.data(), key_len) != 1)
        throw std::runtime_error("scrypt derivation failed");
    return key;
}

#endif  // STUDYCPP_SCRYPT_KDF_H
