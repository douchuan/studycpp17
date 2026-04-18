#ifndef STUDYCPP_ANTI_REPLAY_H
#define STUDYCPP_ANTI_REPLAY_H

// === 防重放攻击 ===
// Nonce 唯一性检查 / 时间戳窗口验证 / 序列号单调递增
// 使用场景：API 请求防重放、WebSocket 消息排序、认证令牌
#include <chrono>
#include <cstdint>
#include <mutex>
#include <stdexcept>
#include <string_view>
#include <unordered_set>
#include <vector>

#include "hmac_mac_demo.h"
#include "sec_utils.h"
#include "secure_compare_demo.h"
#include "secure_random_demo.h"

// 方案 1：Nonce 去重（适合短时间窗口）
class NonceTracker {
   public:
    bool is_replay(const std::string& nonce) {
        std::scoped_lock lock(mu_);
        return !seen_.insert(nonce).second;
    }
    void cleanup(size_t max_size) {
        std::scoped_lock lock(mu_);
        while (seen_.size() > max_size) {
            auto it = seen_.begin();
            seen_.erase(it);
        }
    }

   private:
    std::unordered_set<std::string> seen_;
    std::mutex mu_;
};

// 方案 2：时间戳窗口验证
inline bool timestamp_within_window(int64_t ts_ms, int64_t window_ms = 300000) {
    auto now = std::chrono::system_clock::now();
    int64_t now_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return (now_ms - ts_ms) >= 0 && (now_ms - ts_ms) <= window_ms;
}

// 方案 3：序列号单调递增
class SequenceValidator {
   public:
    bool is_valid(uint64_t seq) {
        std::scoped_lock lock(mu_);
        if (seq <= last_seq_) return false;
        last_seq_ = seq;
        return true;
    }

   private:
    uint64_t last_seq_ = 0;
    std::mutex mu_;
};

// 方案 4：HMAC-Nonce 组合（服务端验证请求新鲜度）
inline std::string make_auth_nonce(std::string_view key, int64_t ts_ms) {
    std::string data = std::to_string(ts_ms);
    auto mac = hmac_sha256(key, data);
    return hex_encode(mac);
}

inline bool verify_auth_nonce(std::string_view key, int64_t ts_ms, std::string_view expected,
                              int64_t window_ms = 300000) {
    if (!timestamp_within_window(ts_ms, window_ms)) return false;
    std::string computed = make_auth_nonce(key, ts_ms);
    return constant_time_compare(computed, expected);
}

#endif  // STUDYCPP_ANTI_REPLAY_H
