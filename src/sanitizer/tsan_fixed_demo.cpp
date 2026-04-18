// === ThreadSanitizer (TSan) — 正确版本：用 std::mutex 保护共享数据 ===
// 与 tsan_race_demo.cpp 对比：加锁后 TSan 无告警
// 运行：cmake -DSANITIZE_THREAD=ON .. && make && ./tsan_fixed_demo
#include <cstdio>
#include <mutex>
#include <thread>

static int g_counter = 0;
static std::mutex g_mu;

void increment(int n) {
    for (int i = 0; i < n; i++) {
        std::lock_guard<std::mutex> lock(g_mu);  // FIX: 加锁保护
        g_counter++;
    }
}

int main() {
    const int N = 100000;
    std::thread t1(increment, N);
    std::thread t2(increment, N);
    t1.join();
    t2.join();
    printf("counter=%d (expected %d)\n", g_counter, N * 2);
    return 0;
}
