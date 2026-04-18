// === clang-tidy 静态分析 — 常见陷阱 ===
// clang-tidy 在编译时检查代码问题（无需运行）
// 运行：cmake ..（自动启用 clang-tidy）&& make static_analysis_demo
//
// 典型问题：
//   bugprone-*：容易出错的写法
//   cppcoreguidelines-*：C++ Core Guidelines 违反
//   performance-*：性能隐患
//   readability-*：可读性问题
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// bugprone-argument-comment：参数顺序易混淆
void set_timeout(int connect_ms, int read_ms) {
    printf("connect=%dms, read=%dms\n", connect_ms, read_ms);
}

void call_with_confused_args() {
    // BUG: 参数顺序可能写反，clang-tidy 的 bugprone-argument-comment 会检查
    set_timeout(5000, 1000);
}

// cppcoreguidelines-owning-memory：原始指针管理内存
void raw_pointer_owner() {
    // BUG: 应该用 unique_ptr 而非裸指针管理堆内存
    int* data = new int[100];
    data[0] = 42;
    delete[] data;
}

// cppcoreguidelines-pro-bounds-array-to-pointer-decay：数组退化
void takes_ptr(const int* p, size_t n) { printf("first=%d, n=%zu\n", p[0], n); }

void array_to_ptr_decay() {
    int arr[5] = {1, 2, 3, 4, 5};
    // BUG: 数组退化为指针，sizeof(arr) 是指针大小而非数组大小
    takes_ptr(arr, sizeof(arr));
}

// performance-unnecessary-copy：不必要的拷贝
void print_strings(const std::vector<std::string>& strings) {
    // BUG: 按值遍历触发拷贝，应使用 const auto&
    for (const auto s : strings) {
        printf("  [%zu bytes]\n", s.size());
    }
}

int main() {
    printf("=== clang-tidy Static Analysis Demos ===\n\n");

    printf("1. Confused args:\n");
    call_with_confused_args();

    printf("\n2. Raw pointer owner:\n");
    raw_pointer_owner();

    printf("\n3. Array-to-ptr decay:\n");
    array_to_ptr_decay();

    printf("\n4. Unnecessary copy:\n");
    std::vector<std::string> items = {"hello", "world"};
    print_strings(items);

    return 0;
}
