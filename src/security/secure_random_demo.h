#ifndef STUDYCPP_SECURE_RANDOM_H
#define STUDYCPP_SECURE_RANDOM_H

// === CSPRNG（密码学安全伪随机数） ===
// OpenSSL RAND_bytes / RAND_priv_bytes，底层调用 OS 安全随机源
// macOS: SecRandomCopyBytes  Linux: getrandom(/dev/urandom)  Windows: BCryptGenRandom
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// 生成 len 字节安全随机
inline std::vector<uint8_t> secure_random_bytes(size_t len) {
    std::vector<uint8_t> buf(len);
    if (RAND_bytes(buf.data(), static_cast<int>(len)) != 1)
        throw std::runtime_error("RAND_bytes failed");
    return buf;
}

// 生成 [0, max) 范围内的安全随机整数
inline uint32_t secure_random_uint32(uint32_t max) {
    uint8_t buf[4];
    if (RAND_bytes(buf, 4) != 1) throw std::runtime_error("RAND_bytes failed");
    uint32_t val = static_cast<uint32_t>(buf[0]) | (static_cast<uint32_t>(buf[1]) << 8) |
                   (static_cast<uint32_t>(buf[2]) << 16) | (static_cast<uint32_t>(buf[3]) << 24);
    return val % max;
}

// 生成安全随机 Hex 字符串
inline std::string secure_random_hex(size_t len) {
    auto bytes = secure_random_bytes(len);
    static const char hex[] = "0123456789abcdef";
    std::string out(len * 2, ' ');
    for (size_t i = 0; i < len; ++i) {
        out[i * 2] = hex[bytes[i] >> 4];
        out[i * 2 + 1] = hex[bytes[i] & 0xf];
    }
    return out;
}

// 生成安全随机 Base64 字符串（URL-safe，无填充）
inline std::string secure_random_base64(size_t len) {
    auto bytes = secure_random_bytes(len);
    static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    std::string out;
    out.reserve((len * 4 + 2) / 3);
    for (size_t i = 0; i < len; i += 3) {
        uint32_t val = bytes[i] << 16;
        if (i + 1 < len) val |= bytes[i + 1] << 8;
        if (i + 2 < len) val |= bytes[i + 2];
        out += b64[(val >> 18) & 0x3f];
        out += b64[(val >> 12) & 0x3f];
        if (i + 1 < len) out += b64[(val >> 6) & 0x3f];
        if (i + 2 < len) out += b64[val & 0x3f];
    }
    return out;
}

// 抗回溯安全随机（每次从 RAND_priv_bytes 获取，适用于密钥生成）
inline std::vector<uint8_t> secure_priv_bytes(size_t len) {
    std::vector<uint8_t> buf(len);
    if (RAND_priv_bytes(buf.data(), static_cast<int>(len)) != 1)
        throw std::runtime_error("RAND_priv_bytes failed");
    return buf;
}

#endif  // STUDYCPP_SECURE_RANDOM_H
