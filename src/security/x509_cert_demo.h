#ifndef STUDYCPP_X509_CERT_H
#define STUDYCPP_X509_CERT_H

// === X.509 证书操作 ===
// 自签名证书生成 / 证书链验证 / PEM 序列化
// 使用场景：TLS 服务端证书、mTLS 客户端证书、CA 证书管理
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#include <cstdint>
#include <string_view>
#include <vector>

// 生成自签名证书
inline std::vector<uint8_t> generate_selfsigned_cert(std::string_view cn, int days = 365) {
    // 生成 EC 密钥
    EVP_PKEY_CTX* kctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, nullptr);
    EVP_PKEY_keygen_init(kctx);
    EVP_PKEY_CTX_set_ec_paramgen_curve_nid(kctx, NID_X9_62_prime256v1);
    EVP_PKEY* pkey = nullptr;
    EVP_PKEY_keygen(kctx, &pkey);
    EVP_PKEY_CTX_free(kctx);

    // 创建证书
    X509* cert = X509_new();
    X509_set_version(cert, 2);
    ASN1_INTEGER_set(X509_get_serialNumber(cert), 1);
    X509_gmtime_adj(X509_get_notBefore(cert), 0);
    X509_gmtime_adj(X509_get_notAfter(cert), static_cast<long>(days) * 86400);

    // 设置 Subject / Issuer
    X509_NAME* name = X509_get_subject_name(cert);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_UTF8,
                               reinterpret_cast<const uint8_t*>(cn.data()),
                               static_cast<int>(cn.size()), -1, 0);
    X509_set_issuer_name(cert, name);
    X509_set_pubkey(cert, pkey);

    // 自签名
    X509_sign(cert, pkey, EVP_sha256());

    // 序列化 PEM
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_X509(bio, cert);
    BUF_MEM* bptr;
    BIO_get_mem_ptr(bio, &bptr);
    std::vector<uint8_t> pem(bptr->data, bptr->data + bptr->length);

    X509_free(cert);
    BIO_free(bio);
    EVP_PKEY_free(pkey);
    return pem;
}

// 解析证书 Subject CN
inline std::string cert_subject_cn(std::string_view pem) {
    BIO* bio = BIO_new_mem_buf(pem.data(), static_cast<int>(pem.size()));
    X509* cert = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    X509_NAME* name = X509_get_subject_name(cert);
    char buf[256];
    X509_NAME_get_text_by_NID(name, NID_commonName, buf, sizeof(buf));
    std::string cn(buf);

    X509_free(cert);
    return cn;
}

// 验证证书是否由指定 CA 签发
inline bool cert_verify_by_ca(std::string_view cert_pem, std::string_view ca_pem) {
    BIO* c_bio = BIO_new_mem_buf(cert_pem.data(), static_cast<int>(cert_pem.size()));
    BIO* a_bio = BIO_new_mem_buf(ca_pem.data(), static_cast<int>(ca_pem.size()));
    X509* cert = PEM_read_bio_X509(c_bio, nullptr, nullptr, nullptr);
    X509* ca = PEM_read_bio_X509(a_bio, nullptr, nullptr, nullptr);
    BIO_free(c_bio);
    BIO_free(a_bio);

    EVP_PKEY* ca_key = X509_get_pubkey(ca);
    int ok = X509_verify(cert, ca_key);
    EVP_PKEY_free(ca_key);
    X509_free(cert);
    X509_free(ca);
    return ok == 1;
}

#endif  // STUDYCPP_X509_CERT_H
