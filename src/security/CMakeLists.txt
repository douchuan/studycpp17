# security 模块：基于 OpenSSL 3.x 的密码学工具箱教学示例

find_package(OpenSSL REQUIRED)

add_executable(secure_random_demo secure_random_demo.cpp)
add_executable(sha2_hash_demo sha2_hash_demo.cpp)
add_executable(sha3_hash_demo sha3_hash_demo.cpp)
add_executable(blake2_hash_demo blake2_hash_demo.cpp)
add_executable(password_hash_demo password_hash_demo.cpp)
add_executable(hmac_mac_demo hmac_mac_demo.cpp)
add_executable(cmac_mac_demo cmac_mac_demo.cpp)
add_executable(poly1305_mac_demo poly1305_mac_demo.cpp)
add_executable(aes_gcm_demo aes_gcm_demo.cpp)
add_executable(aes_cbc_demo aes_cbc_demo.cpp)
add_executable(aes_ctr_demo aes_ctr_demo.cpp)
add_executable(chacha20_poly1305_demo chacha20_poly1305_demo.cpp)
add_executable(rsa_encrypt_demo rsa_encrypt_demo.cpp)
add_executable(ecies_encrypt_demo ecies_encrypt_demo.cpp)
add_executable(dh_exchange_demo dh_exchange_demo.cpp)
add_executable(x25519_exchange_demo x25519_exchange_demo.cpp)
add_executable(rsa_sign_demo rsa_sign_demo.cpp)
add_executable(ecdsa_sign_demo ecdsa_sign_demo.cpp)
add_executable(ed25519_sign_demo ed25519_sign_demo.cpp)
add_executable(hkdf_kdf_demo hkdf_kdf_demo.cpp)
add_executable(pbkdf2_kdf_demo pbkdf2_kdf_demo.cpp)
add_executable(scrypt_kdf_demo scrypt_kdf_demo.cpp)
add_executable(encoding_demo encoding_demo.cpp)
add_executable(x509_cert_demo x509_cert_demo.cpp)
add_executable(pkcs7_padding_demo pkcs7_padding_demo.cpp)
add_executable(secure_compare_demo secure_compare_demo.cpp)
add_executable(anti_replay_demo anti_replay_demo.cpp)

foreach(tgt
    secure_random_demo sha2_hash_demo sha3_hash_demo blake2_hash_demo
    password_hash_demo hmac_mac_demo cmac_mac_demo poly1305_mac_demo
    aes_gcm_demo aes_cbc_demo aes_ctr_demo chacha20_poly1305_demo
    rsa_encrypt_demo ecies_encrypt_demo dh_exchange_demo x25519_exchange_demo
    rsa_sign_demo ecdsa_sign_demo ed25519_sign_demo
    hkdf_kdf_demo pbkdf2_kdf_demo scrypt_kdf_demo
    encoding_demo x509_cert_demo pkcs7_padding_demo
    secure_compare_demo anti_replay_demo)
    target_link_libraries(${tgt} PRIVATE OpenSSL::Crypto)
endforeach()
