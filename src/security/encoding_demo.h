#ifndef STUDYCPP_ENCODING_H
#define STUDYCPP_ENCODING_H

// === 密码学编码 ===
// Base64 / Base64URL / Hex / PEM 序列化
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "sec_utils.h"

// 辅助：分割字符串视图
inline std::vector<std::string_view> split_view(std::string_view s, char delim) {
    std::vector<std::string_view> parts;
    size_t start = 0;
    for (size_t i = 0; i <= s.size(); ++i) {
        if (i == s.size() || s[i] == delim) {
            parts.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }
    return parts;
}

// Base64URL（无填充，URL/filename 安全）
inline std::string base64url_encode(const std::vector<uint8_t>& data) {
    std::string b64 = base64_encode(data);
    std::string url;
    url.reserve(b64.size());
    for (char c : b64) {
        if (c == '+')
            url += '-';
        else if (c == '/')
            url += '_';
        else if (c != '=')
            url += c;
    }
    return url;
}

// 从 PEM 格式解析原始 DER 字节
inline std::vector<uint8_t> pem_to_der(std::string_view pem) {
    std::string stripped;
    stripped.reserve(pem.size());
    for (auto line : split_view(pem, '\n')) {
        if (line.find("-----BEGIN") != std::string_view::npos ||
            line.find("-----END") != std::string_view::npos)
            continue;
        stripped += line;
    }
    return base64_decode(stripped);
}

inline std::string der_to_pem(std::string_view der, std::string_view label) {
    std::string b64 = base64_encode(std::vector<uint8_t>(der.begin(), der.end()));
    std::string pem = "-----BEGIN " + std::string(label) + "-----\n";
    for (size_t i = 0; i < b64.size(); i += 64) pem += b64.substr(i, 64) + "\n";
    pem += "-----END " + std::string(label) + "-----\n";
    return pem;
}

#endif  // STUDYCPP_ENCODING_H
