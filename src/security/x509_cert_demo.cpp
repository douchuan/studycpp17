#include "x509_cert_demo.h"

#include <iostream>

int main() {
    std::cout << "=== X.509 证书操作 ===\n\n";

    // 生成自签名证书
    auto cert = generate_selfsigned_cert("test.example.com", 365);
    std::cout << "Self-signed certificate (PEM):\n";
    std::cout.write(reinterpret_cast<char*>(cert.data()),
                    static_cast<std::streamsize>(cert.size()));
    std::cout << "\n";

    // 解析 Subject CN
    std::string cn =
        cert_subject_cn(std::string_view(reinterpret_cast<char*>(cert.data()), cert.size()));
    std::cout << "Subject CN: " << cn << "\n\n";

    // 生成 CA 证书并验证
    auto ca_cert = generate_selfsigned_cert("My Test CA", 3650);
    std::cout << "CA certificate (PEM):\n";
    std::cout.write(reinterpret_cast<char*>(ca_cert.data()),
                    static_cast<std::streamsize>(ca_cert.size()));
    std::cout << "\n";

    // 自签名证书不能由另一个自签名 CA 验证（预期为 false）
    bool ok = cert_verify_by_ca(
        std::string_view(reinterpret_cast<char*>(cert.data()), cert.size()),
        std::string_view(reinterpret_cast<char*>(ca_cert.data()), ca_cert.size()));
    std::cout << "Cert verified by CA: " << (ok ? "YES" : "NO (expected - different keys)") << "\n";

    return 0;
}
