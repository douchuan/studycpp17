#ifndef STUDYCPP_STD_CHRONO_DEMO_H
#define STUDYCPP_STD_CHRONO_DEMO_H

#include <chrono>
#include <string>
#include <thread>

// --- 获取当前时间戳（毫秒） ---
inline long long now_ms() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

// --- 测量耗时 ---
template <typename Fn>
inline auto measure(Fn fn) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = fn();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return std::make_pair(result, elapsed);
}

// --- 时间字面量 ---
inline long long seconds_to_ms(int seconds) {
    using namespace std::chrono_literals;
    auto duration = std::chrono::seconds(seconds);
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

// --- 休眠 ---
inline void sleep_ms(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

#endif  // STUDYCPP_STD_CHRONO_DEMO_H
