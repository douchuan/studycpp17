#ifndef STUDYCPP_ECIES_ENCRYPT_H
#define STUDYCPP_ECIES_ENCRYPT_H

// === ECIES（椭圆曲线集成加密方案） ===
// 混合加密：ECDH 协商密钥 + AES-GCM 加密数据
// 使用场景：端到端加密、消息加密（比 RSA 更高效、密钥更短）
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <vector>

struct EcKeyPair {
    std::vector<uint8_t> pub_pem;
    std::vector<uint8_t> priv_pem;
};

// 生成 EC 密钥对（P-256）
inline EcKeyPair ec_generate_key() {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, nullptr);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_X9_62_prime256v1);
    EVP_PKEY* pkey = nullptr;
    EVP_PKEY_keygen(ctx, &pkey);
    EVP_PKEY_CTX_free(ctx);

    BIO* pub_bio = BIO_new(BIO_s_mem());
    BIO* priv_bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(pub_bio, pkey);
    PEM_write_bio_PrivateKey(priv_bio, pkey, nullptr, nullptr, 0, nullptr, nullptr);

    BUF_MEM* bptr;
    EcKeyPair keys;
    BIO_get_mem_ptr(pub_bio, &bptr);
    keys.pub_pem.assign(bptr->data, bptr->data + bptr->length);
    BIO_get_mem_ptr(priv_bio, &bptr);
    keys.priv_pem.assign(bptr->data, bptr->data + bptr->length);

    BIO_free(pub_bio);
    BIO_free(priv_bio);
    EVP_PKEY_free(pkey);
    return keys;
}

// 简化版 ECIES：ECDH 派生密钥 + AES-256-CTR（教学演示）
inline std::vector<uint8_t> ecies_encrypt(const std::vector<uint8_t>& pub_pem,
                                          std::string_view plaintext) {
    BIO* bio = BIO_new_mem_buf(pub_pem.data(), static_cast<int>(pub_pem.size()));
    EVP_PKEY* peer_pub = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    // 生成临时 EC 密钥对
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, nullptr);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_X9_62_prime256v1);
    EVP_PKEY* eph_key = nullptr;
    EVP_PKEY_keygen(ctx, &eph_key);
    EVP_PKEY_CTX_free(ctx);

    // ECDH 派生共享密钥
    EVP_PKEY_CTX* dh_ctx = EVP_PKEY_CTX_new(eph_key, nullptr);
    EVP_PKEY_derive_init(dh_ctx);
    EVP_PKEY_derive_set_peer(dh_ctx, peer_pub);
    size_t shared_len = 0;
    EVP_PKEY_derive(dh_ctx, nullptr, &shared_len);
    std::vector<uint8_t> shared(shared_len);
    EVP_PKEY_derive(dh_ctx, shared.data(), &shared_len);
    EVP_PKEY_CTX_free(dh_ctx);

    // 用共享密钥做 AES-CTR 加密（简化，实际应用应使用 HKDF 派生 + AES-GCM）
    std::vector<uint8_t> nonce(16);
    RAND_bytes(nonce.data(), static_cast<int>(nonce.size()));

    EVP_CIPHER_CTX* ectx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ectx, EVP_aes_256_ctr(), nullptr, shared.data(), nonce.data());
    std::vector<uint8_t> ct(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, total = 0;
    EVP_EncryptUpdate(ectx, ct.data(), &len, reinterpret_cast<const uint8_t*>(plaintext.data()),
                      static_cast<int>(plaintext.size()));
    total = len;
    EVP_EncryptFinal_ex(ectx, ct.data() + total, &len);
    total += len;
    ct.resize(total);
    EVP_CIPHER_CTX_free(ectx);

    // 序列化：ephemeral pub + nonce + ciphertext
    BIO* eph_bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(eph_bio, eph_key);
    BUF_MEM* bptr;
    BIO_get_mem_ptr(eph_bio, &bptr);
    std::vector<uint8_t> eph_pub(bptr->data, bptr->data + bptr->length);
    BIO_free(eph_bio);

    std::vector<uint8_t> result;
    uint32_t eph_len32 = eph_pub.size();
    result.insert(result.end(), reinterpret_cast<uint8_t*>(&eph_len32),
                  reinterpret_cast<uint8_t*>(&eph_len32) + 4);
    result.insert(result.end(), eph_pub.begin(), eph_pub.end());
    result.insert(result.end(), nonce.begin(), nonce.end());
    result.insert(result.end(), ct.begin(), ct.end());

    EVP_PKEY_free(peer_pub);
    EVP_PKEY_free(eph_key);
    return result;
}

inline std::vector<uint8_t> ecies_decrypt(const std::vector<uint8_t>& priv_pem,
                                          std::string_view packed) {
    BIO* bio = BIO_new_mem_buf(priv_pem.data(), static_cast<int>(priv_pem.size()));
    EVP_PKEY* priv = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    uint32_t eph_len;
    memcpy(&eph_len, packed.data(), 4);
    std::string_view eph_pem(packed.data() + 4, eph_len);
    std::string_view nonce(packed.data() + 4 + eph_len, 16);
    std::string_view ciphertext(packed.data() + 4 + eph_len + 16);

    BIO* eph_bio = BIO_new_mem_buf(eph_pem.data(), static_cast<int>(eph_pem.size()));
    EVP_PKEY* eph_pub = PEM_read_bio_PUBKEY(eph_bio, nullptr, nullptr, nullptr);
    BIO_free(eph_bio);

    // ECDH 派生共享密钥
    EVP_PKEY_CTX* dh_ctx = EVP_PKEY_CTX_new(priv, nullptr);
    EVP_PKEY_derive_init(dh_ctx);
    EVP_PKEY_derive_set_peer(dh_ctx, eph_pub);
    size_t shared_len = 0;
    EVP_PKEY_derive(dh_ctx, nullptr, &shared_len);
    std::vector<uint8_t> shared(shared_len);
    EVP_PKEY_derive(dh_ctx, shared.data(), &shared_len);
    EVP_PKEY_CTX_free(dh_ctx);

    EVP_CIPHER_CTX* dctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(dctx, EVP_aes_256_ctr(), nullptr, shared.data(),
                       reinterpret_cast<const uint8_t*>(nonce.data()));
    std::vector<uint8_t> pt(ciphertext.size() + 16);
    int len = 0, total = 0;
    EVP_DecryptUpdate(dctx, pt.data(), &len, reinterpret_cast<const uint8_t*>(ciphertext.data()),
                      static_cast<int>(ciphertext.size()));
    total = len;
    EVP_DecryptFinal_ex(dctx, pt.data() + total, &len);
    total += len;
    pt.resize(total);
    EVP_CIPHER_CTX_free(dctx);

    EVP_PKEY_free(priv);
    EVP_PKEY_free(eph_pub);
    return pt;
}

#endif  // STUDYCPP_ECIES_ENCRYPT_H
