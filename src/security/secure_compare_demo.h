#ifndef STUDYCPP_SECURE_COMPARE_H
#define STUDYCPP_SECURE_COMPARE_H

// === 恒定时间比较 / 安全内存操作 ===
// 防侧信道攻击：避免因分支和提前返回泄露比较信息
// 使用场景：MAC 验证、密码比对、令牌校验
#include <openssl/crypto.h>

#include <cstdint>
#include <cstring>
#include <string_view>
#include <vector>

// 恒定时间字节比较（OpenSSL CRYPTO_memcmp）
inline bool constant_time_compare(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) return false;
    return CRYPTO_memcmp(a.data(), b.data(), a.size()) == 0;
}

// 恒定时间向量比较
inline bool constant_time_compare(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b) {
    if (a.size() != b.size()) return false;
    return CRYPTO_memcmp(a.data(), b.data(), a.size()) == 0;
}

// 安全内存清零
inline void secure_zero(std::vector<uint8_t>& buf) {
    OPENSSL_cleanse(buf.data(), buf.size());
    buf.clear();
    buf.shrink_to_fit();
}

#endif  // STUDYCPP_SECURE_COMPARE_H
