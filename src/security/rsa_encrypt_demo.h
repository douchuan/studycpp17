#ifndef STUDYCPP_RSA_ENCRYPT_H
#define STUDYCPP_RSA_ENCRYPT_H

// === RSA 非对称加密 ===
// RSA-OAEP（安全）/ RSA-PKCS1-v1.5（兼容）
// 使用场景：密钥交换、信封加密、数字信封
// 注意：RSA 不直接加密大数据，通常只加密对称密钥
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <vector>

struct RsaKeyPair {
    std::vector<uint8_t> pub_pem;   // PEM 格式公钥
    std::vector<uint8_t> priv_pem;  // PEM 格式私钥
};

// 生成 RSA 密钥对
inline RsaKeyPair rsa_generate_key(int bits = 2048) {
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
    BIO_get_mem_ptr(pub_bio, &bptr);
    RsaKeyPair keys;
    keys.pub_pem.assign(bptr->data, bptr->data + bptr->length);
    BIO_get_mem_ptr(priv_bio, &bptr);
    keys.priv_pem.assign(bptr->data, bptr->data + bptr->length);

    BIO_free(pub_bio);
    BIO_free(priv_bio);
    EVP_PKEY_free(pkey);
    return keys;
}

// RSA-OAEP 加密（推荐）
inline std::vector<uint8_t> rsa_oaep_encrypt(const std::vector<uint8_t>& pub_pem,
                                             std::string_view plaintext) {
    BIO* bio = BIO_new_mem_buf(pub_pem.data(), static_cast<int>(pub_pem.size()));
    EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    EVP_PKEY_encrypt_init(ctx);
    EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);
    EVP_PKEY_CTX_set_rsa_oaep_md(ctx, EVP_sha256());

    size_t out_len = 0;
    EVP_PKEY_encrypt(ctx, nullptr, &out_len, reinterpret_cast<const uint8_t*>(plaintext.data()),
                     plaintext.size());
    std::vector<uint8_t> ciphertext(out_len);
    EVP_PKEY_encrypt(ctx, ciphertext.data(), &out_len,
                     reinterpret_cast<const uint8_t*>(plaintext.data()), plaintext.size());
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return ciphertext;
}

// RSA-OAEP 解密
inline std::vector<uint8_t> rsa_oaep_decrypt(const std::vector<uint8_t>& priv_pem,
                                             std::string_view ciphertext) {
    BIO* bio = BIO_new_mem_buf(priv_pem.data(), static_cast<int>(priv_pem.size()));
    EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    EVP_PKEY_decrypt_init(ctx);
    EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);
    EVP_PKEY_CTX_set_rsa_oaep_md(ctx, EVP_sha256());

    size_t out_len = 0;
    EVP_PKEY_decrypt(ctx, nullptr, &out_len, reinterpret_cast<const uint8_t*>(ciphertext.data()),
                     ciphertext.size());
    std::vector<uint8_t> plaintext(out_len);
    EVP_PKEY_decrypt(ctx, plaintext.data(), &out_len,
                     reinterpret_cast<const uint8_t*>(ciphertext.data()), ciphertext.size());
    plaintext.resize(out_len);
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return plaintext;
}

#endif  // STUDYCPP_RSA_ENCRYPT_H
