// === AddressSanitizer (ASan) — 堆缓冲区溢出 ===
// Bug：越界写操作，覆盖堆上相邻内存
// 场景：循环边界写错、数组索引未校验
// 运行：cmake -DSANITIZE_ADDRESS=ON .. && make && ./asan_overflow_demo
#include <cstdio>
#include <cstdlib>

int main() {
    int* buf = (int*)malloc(5 * sizeof(int));
    for (int i = 0; i <= 5; i++) {  // BUG: off-by-one, i should be < 5
        buf[i] = i * 10;
    }
    printf("buf[4]=%d\n", buf[4]);
    free(buf);
    return 0;
}
