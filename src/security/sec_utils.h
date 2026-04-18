#ifndef STUDYCPP_SEC_UTILS_H
#define STUDYCPP_SEC_UTILS_H

// 密码学编码工具：Hex、Base64、安全内存清零
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

#include <cerrno>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// 二进制 → 十六进制
inline std::string hex_encode(const std::vector<uint8_t>& data) {
    std::string out;
    out.reserve(data.size() * 2);
    char buf[3];
    for (auto b : data) {
        snprintf(buf, sizeof(buf), "%02x", b);
        out += buf;
    }
    return out;
}

// 十六进制 → 二进制
inline std::vector<uint8_t> hex_decode(std::string_view hex) {
    std::vector<uint8_t> out;
    out.reserve(hex.size() / 2);
    for (size_t i = 0; i < hex.size(); i += 2) {
        unsigned long byte = strtoul(hex.data() + i, nullptr, 16);
        out.push_back(static_cast<uint8_t>(byte));
    }
    return out;
}

// 二进制 → Base64
inline std::string base64_encode(const std::vector<uint8_t>& data) {
    BIO* bio = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new(BIO_s_mem());
    BIO_push(bio, mem);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, data.data(), static_cast<int>(data.size()));
    BIO_flush(bio);
    BUF_MEM* bptr;
    BIO_get_mem_ptr(bio, &bptr);
    std::string out(bptr->data, bptr->length);
    BIO_free_all(bio);
    return out;
}

// Base64 → 二进制
inline std::vector<uint8_t> base64_decode(std::string_view b64) {
    BIO* bio = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new_mem_buf(b64.data(), static_cast<int>(b64.size()));
    BIO_push(bio, mem);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    std::vector<uint8_t> out(b64.size());
    int len = BIO_read(bio, out.data(), static_cast<int>(out.size()));
    out.resize(len);
    BIO_free_all(bio);
    return out;
}

// 安全内存清零（防编译器优化掉）
inline void secure_wipe(void* p, size_t len) {
#if defined(_WIN32)
    SecureZeroMemory(p, len);
#else
    volatile unsigned char* vp = static_cast<volatile unsigned char*>(p);
    while (len--) *vp++ = 0;
#endif
}

#endif  // STUDYCPP_SEC_UTILS_H
