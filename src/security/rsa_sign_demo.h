#ifndef STUDYCPP_RSA_SIGN_H
#define STUDYCPP_RSA_SIGN_H

// === RSA 数字签名 ===
// RSA-PSS（安全推荐）/ RSA-PKCS1-v1.5（兼容旧系统）
// 使用场景：代码签名、证书签发、API 请求认证
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

#include <cstdint>
#include <string_view>
#include <vector>

struct RsaSignKeys {
    std::vector<uint8_t> pub_pem;
    std::vector<uint8_t> priv_pem;
};

inline RsaSignKeys rsa_sign_generate(int bits = 2048) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits);
    EVP_PKEY* pkey = nullptr;
    EVP_PKEY_keygen(ctx, &pkey);
    EVP_PKEY_CTX_free(ctx);

    BIO* pub_bio = BIO_new(BIO_s_mem());
    BIO* priv_bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(pub_bio, pkey);
    PEM_write_bio_PrivateKey(priv_bio, pkey, nullptr, nullptr, 0, nullptr, nullptr);

    BUF_MEM* bptr;
    RsaSignKeys keys;
    BIO_get_mem_ptr(pub_bio, &bptr);
    keys.pub_pem.assign(bptr->data, bptr->data + bptr->length);
    BIO_get_mem_ptr(priv_bio, &bptr);
    keys.priv_pem.assign(bptr->data, bptr->data + bptr->length);

    BIO_free(pub_bio);
    BIO_free(priv_bio);
    EVP_PKEY_free(pkey);
    return keys;
}

// RSA-PSS 签名
inline std::vector<uint8_t> rsa_pss_sign(const std::vector<uint8_t>& priv_pem,
                                         std::string_view data) {
    BIO* bio = BIO_new_mem_buf(priv_pem.data(), static_cast<int>(priv_pem.size()));
    EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_PKEY_CTX* pctx = nullptr;
    EVP_DigestSignInit(ctx, &pctx, EVP_sha256(), nullptr, pkey);
    EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PSS_PADDING);
    EVP_PKEY_CTX_set_rsa_pss_saltlen(pctx, RSA_PSS_SALTLEN_DIGEST);

    EVP_DigestSignUpdate(ctx, data.data(), static_cast<int>(data.size()));
    size_t len = 0;
    EVP_DigestSignFinal(ctx, nullptr, &len);
    std::vector<uint8_t> sig(len);
    EVP_DigestSignFinal(ctx, sig.data(), &len);
    EVP_MD_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return sig;
}

// RSA-PSS 验证
inline bool rsa_pss_verify(const std::vector<uint8_t>& pub_pem, std::string_view data,
                           std::string_view signature) {
    BIO* bio = BIO_new_mem_buf(pub_pem.data(), static_cast<int>(pub_pem.size()));
    EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_PKEY_CTX* pctx = nullptr;
    EVP_DigestVerifyInit(ctx, &pctx, EVP_sha256(), nullptr, pkey);
    EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PSS_PADDING);
    EVP_PKEY_CTX_set_rsa_pss_saltlen(pctx, RSA_PSS_SALTLEN_DIGEST);

    EVP_DigestVerifyUpdate(ctx, data.data(), static_cast<int>(data.size()));
    bool ok = EVP_DigestVerifyFinal(ctx, reinterpret_cast<const uint8_t*>(signature.data()),
                                    signature.size()) == 1;
    EVP_MD_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return ok;
}

#endif  // STUDYCPP_RSA_SIGN_H
