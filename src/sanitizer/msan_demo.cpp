// === MemorySanitizer (MSan) — 未初始化内存读取 ===
// Bug：读取未初始化的内存，导致不可预测行为
// 场景：struct 部分初始化、new[] 未 init、栈变量未初始化
// 注意：MSan 仅 Clang 支持，且要求被依赖的库也用 MSan 编译
// 运行（仅 Clang）：cmake -DSANITIZE_MEMORY=ON .. && make && ./msan_demo
#include <cstdio>
#include <cstdlib>

struct Config {
    int timeout;
    int retries;
    char host[64];
};

// 场景 1：struct 部分初始化
void partial_init() {
    Config cfg;
    cfg.timeout = 30;
    // BUG: cfg.retries and cfg.host are uninitialized
    printf("retries = %d\n", cfg.retries);
}

// 场景 2：栈变量未初始化
void uninitialized_local() {
    int sum;  // BUG: not initialized
    printf("sum = %d\n", sum);
}

// 场景 3：malloc 返回的内存未初始化
void uninitialized_heap() {
    int* arr = (int*)malloc(100 * sizeof(int));
    // BUG: arr[50] is uninitialized
    printf("arr[50] = %d\n", arr[50]);
    free(arr);
}

int main() {
    printf("=== MemorySanitizer Demos ===\n\n");

    printf("1. Partial struct init:\n");
    partial_init();

    printf("\n2. Uninitialized local:\n");
    uninitialized_local();

    printf("\n3. Uninitialized heap:\n");
    uninitialized_heap();

    return 0;
}
