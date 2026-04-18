// === AddressSanitizer (ASan) — Double Free (重复释放) ===
// Bug：同一块内存 free 两次
// 场景：多个所有者共享裸指针、异常路径下重复 cleanup
// 运行：cmake -DSANITIZE_ADDRESS=ON .. && make && ./asan_double_free_demo
#include <cstdio>
#include <cstdlib>

int main() {
    int* p = (int*)malloc(sizeof(int) * 10);
    p[0] = 42;
    free(p);

    // BUG: p is already freed
    free(p);
    return 0;
}
