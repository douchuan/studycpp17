// === UndefinedBehaviorSanitizer (UBSan) — 未定义行为 ===
// 检测：空指针解引用、有符号整数溢出、数组越界、对齐错误
// 运行：cmake -DSANITIZE_UNDEFINED=ON .. && make && ./ubsan_demo
#include <cstdint>
#include <cstdio>
#include <cstring>

// 1. 空指针解引用
void null_deref(bool trigger) {
    int* p = nullptr;
    if (trigger) {
        printf("*p = %d\n", *p);  // UBSan: null pointer dereference
    }
}

// 2. 有符号整数溢出
void signed_overflow() {
    volatile int32_t x = 2147483647;  // INT32_MAX
    volatile int32_t y = x + 1;       // UBSan: signed integer overflow
    printf("x+1 = %d\n", y);
}

// 3. 未对齐访问
void unaligned_access(const uint8_t* buf) {
    int val;
    memcpy(&val, buf + 1, sizeof(int));  // OK 用 memcpy 避免严格对齐 UB
    printf("unaligned read = %d\n", val);
}

// 4. 类型双关 (type punning via reinterpret_cast)
void bad_cast() {
    int x = 42;
    // reinterpret cast float* → int* — 严格来说不是 UB 但在某些平台行为异常
    float* fp = reinterpret_cast<float*>(&x);
    printf("bad_cast float = %f\n", *fp);  // UBSan with alignment check
}

int main() {
    printf("=== UBSan Demos ===\n\n");

    printf("1. Signed overflow:\n");
    signed_overflow();

    printf("\n2. Unaligned access (via memcpy, OK):\n");
    uint8_t buf[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    unaligned_access(buf);

    printf("\n3. Bad cast:\n");
    bad_cast();

    // null_deref 放最后，因为会 crash
    printf("\n4. Null deref (will trap with UBSan):\n");
    null_deref(true);

    return 0;
}
