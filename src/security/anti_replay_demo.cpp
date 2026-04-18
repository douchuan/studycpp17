#include "anti_replay_demo.h"

#include <chrono>
#include <iostream>
#include <thread>

int main() {
    std::cout << "=== 防重放攻击 ===\n\n";

    // 1. Nonce 去重
    std::cout << "1. Nonce 去重:\n";
    NonceTracker tracker;
    std::string nonce = secure_random_hex(8);
    std::cout << "   nonce=" << nonce << " → replay=" << (tracker.is_replay(nonce) ? "YES" : "NO")
              << "\n";
    std::cout << "   nonce=" << nonce << " → replay=" << (tracker.is_replay(nonce) ? "YES" : "NO")
              << "\n";

    // 2. 时间戳窗口
    std::cout << "\n2. 时间戳窗口验证:\n";
    auto now = std::chrono::system_clock::now();
    int64_t now_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::cout << "   now - 1s: " << (timestamp_within_window(now_ms - 1000) ? "VALID" : "EXPIRED")
              << "\n";
    std::cout << "   now - 10min: "
              << (timestamp_within_window(now_ms - 600000) ? "VALID" : "EXPIRED") << "\n";

    // 3. 序列号单调递增
    std::cout << "\n3. 序列号单调递增:\n";
    SequenceValidator seq;
    std::cout << "   seq=5: " << (seq.is_valid(5) ? "VALID" : "REJECTED") << "\n";
    std::cout << "   seq=3: " << (seq.is_valid(3) ? "VALID" : "REJECTED") << "\n";
    std::cout << "   seq=10: " << (seq.is_valid(10) ? "VALID" : "REJECTED") << "\n";

    // 4. HMAC-Nonce 认证
    std::cout << "\n4. HMAC-Nonce 认证:\n";
    std::string secret_key = "api-secret-key";
    int64_t ts = now_ms;
    std::string auth = make_auth_nonce(secret_key, ts);
    std::cout << "   auth=" << auth.substr(0, 16) << "...\n";
    std::cout << "   verify (valid): "
              << (verify_auth_nonce(secret_key, ts, auth) ? "PASS" : "FAIL") << "\n";
    std::cout << "   verify (wrong key): "
              << (verify_auth_nonce("wrong-key", ts, auth) ? "PASS" : "FAIL") << "\n";

    return 0;
}
