#ifndef STUDYCPP_PASSWORD_HASH_H
#define STUDYCPP_PASSWORD_HASH_H

// === 密码哈希（存储用） ===
// PBKDF2 / scrypt / Argon2id（Argon2 需独立库，此处用 PBKDF2 + scrypt）
// 使用场景：用户密码存储，防止彩虹表和暴力破解
// 推荐优先级：Argon2id > scrypt > bcrypt > PBKDF2
#include <openssl/evp.h>

#include <cstdint>
#include <string_view>
#include <vector>

// PBKDF2-HMAC-SHA256
inline std::vector<uint8_t> pbkdf2_hash(std::string_view password, std::string_view salt,
                                        int iterations = 100000, int key_len = 32) {
    std::vector<uint8_t> out(key_len);
    if (PKCS5_PBKDF2_HMAC(password.data(), static_cast<int>(password.size()),
                          reinterpret_cast<const uint8_t*>(salt.data()),
                          static_cast<int>(salt.size()), iterations, EVP_sha256(), key_len,
                          out.data()) != 1)
        throw std::runtime_error("PKCS5_PBKDF2_HMAC failed");
    return out;
}

// PBKDF2 验证
inline bool pbkdf2_verify(std::string_view password, std::string_view salt,
                          std::string_view expected_hash, int iterations = 100000) {
    auto computed = pbkdf2_hash(password, salt, iterations, static_cast<int>(expected_hash.size()));
    return computed == std::vector<uint8_t>(expected_hash.begin(), expected_hash.end());
}

// scrypt（内存硬函数，抗 GPU/ASIC 破解）
inline std::vector<uint8_t> scrypt_hash(std::string_view password, std::string_view salt,
                                        uint64_t n = 16384, int r = 8, int p = 1,
                                        int key_len = 32) {
    std::vector<uint8_t> out(key_len);
    if (EVP_PBE_scrypt(password.data(), password.size(),
                       reinterpret_cast<const uint8_t*>(salt.data()), salt.size(), n, r, p, 0,
                       out.data(), key_len) != 1)
        throw std::runtime_error("EVP_PBE_scrypt failed");
    return out;
}

// scrypt 验证
inline bool scrypt_verify(std::string_view password, std::string_view salt,
                          std::string_view expected_hash, uint64_t n = 16384, int r = 8,
                          int p = 1) {
    auto computed = scrypt_hash(password, salt, n, r, p, static_cast<int>(expected_hash.size()));
    return computed == std::vector<uint8_t>(expected_hash.begin(), expected_hash.end());
}

// Argon2id 需要 libargon2，不在 OpenSSL 中
// 安装 libargon2 后使用：argon2id_hash_raw(&params, password, salt, hash, hash_len)

#endif  // STUDYCPP_PASSWORD_HASH_H
