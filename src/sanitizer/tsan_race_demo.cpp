// === ThreadSanitizer (TSan) — 数据竞态条件 ===
// Bug：多线程同时读写共享变量，无同步
// 场景：全局计数器、lazy init 无锁、多线程更新配置
// 运行（仅 Clang）：cmake -DSANITIZE_THREAD=ON .. && make && ./tsan_race_demo
#include <cstdio>
#include <thread>

// 全局共享变量，无保护
static int g_counter = 0;

void increment(int n) {
    for (int i = 0; i < n; i++) {
        g_counter++;  // BUG: data race — concurrent read-modify-write
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
