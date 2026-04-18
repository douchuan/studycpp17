#ifndef STUDYCPP_PKCS7_PADDING_H
#define STUDYCPP_PKCS7_PADDING_H

// === PKCS#7 填充 / ISO 7816-4 填充 ===
// 块密码填充：将任意长度数据填充到块大小整数倍
// PKCS#7：填充 N 个值为 N 的字节（AES 默认）
// ISO 7816-4：填充 0x80 + 零字节
#include <cstdint>
#include <stdexcept>
#include <vector>

// PKCS#7 填充（block_size 通常为 16）
inline std::vector<uint8_t> pkcs7_pad(std::string_view data, int block_size = 16) {
    int pad_len = block_size - static_cast<int>(data.size() % block_size);
    std::vector<uint8_t> out(data.begin(), data.end());
    out.insert(out.end(), pad_len, static_cast<uint8_t>(pad_len));
    return out;
}

// PKCS#7 去填充
inline std::vector<uint8_t> pkcs7_unpad(const std::vector<uint8_t>& data, int block_size = 16) {
    if (data.empty() || data.size() % block_size != 0)
        throw std::runtime_error("invalid pkcs7 data");
    int pad_len = data.back();
    if (pad_len < 1 || pad_len > block_size) throw std::runtime_error("invalid pkcs7 padding");
    for (int i = 0; i < pad_len; ++i)
        if (data[data.size() - 1 - i] != pad_len)
            throw std::runtime_error("pkcs7 padding mismatch");
    return {data.begin(), data.end() - pad_len};
}

// ISO/IEC 7816-4 填充：0x80 + 零字节
inline std::vector<uint8_t> iso7816_pad(std::string_view data, int block_size = 16) {
    std::vector<uint8_t> out(data.begin(), data.end());
    out.push_back(0x80);
    while (out.size() % block_size != 0) out.push_back(0x00);
    return out;
}

inline std::vector<uint8_t> iso7816_unpad(const std::vector<uint8_t>& data) {
    size_t end = data.size();
    while (end > 0 && data[end - 1] == 0x00) --end;
    if (end > 0 && data[end - 1] == 0x80)
        return {data.begin(), data.begin() + static_cast<std::ptrdiff_t>(end) - 1};
    throw std::runtime_error("invalid iso7816 padding");
}

#endif  // STUDYCPP_PKCS7_PADDING_H
