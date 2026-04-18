// === LeakSanitizer (LSan) — 内存泄漏检测 ===
// Bug：malloc/new 分配的内存未 free/delete
// 场景：早期返回遗漏释放、容器扩容未释放旧缓冲区、遗忘 shared_ptr 循环引用
// 运行：cmake -DSANITIZE_LEAK=ON .. && make && ./leak_demo
//       （LSan 通常随 ASan 内置：SANITIZE_ADDRESS=ON 时自动开启）
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

// 场景 1：早期返回路径忘记释放
void early_return_leak(bool condition) {
    char* buf = (char*)malloc(1024);
    memset(buf, 0, 1024);
    if (condition) {
        printf("condition true, returning early\n");
        // BUG: buf not freed on early return
        return;
    }
    free(buf);
}

// 场景 2：strdup 返回的内存未释放
const char* get_config() {
    return strdup("api-key=secret123");  // 调用者负责 free，但没人调
}

// 场景 3：容器 grow 时忘记释放旧缓冲区
void vector_grow_leak() {
    int* old_buf = (int*)malloc(10 * sizeof(int));
    int* new_buf = (int*)malloc(20 * sizeof(int));
    memcpy(new_buf, old_buf, 10 * sizeof(int));
    // BUG: old_buf not freed after grow
    free(new_buf);
}

int main() {
    printf("=== LeakSanitizer Demos ===\n\n");

    printf("1. Early return leak:\n");
    early_return_leak(true);

    printf("2. strdup leak:\n");
    get_config();  // 返回值未使用，内存泄漏

    printf("3. Vector grow leak:\n");
    vector_grow_leak();

    printf("\n--- LSan report appears at exit ---\n");
    return 0;
}
