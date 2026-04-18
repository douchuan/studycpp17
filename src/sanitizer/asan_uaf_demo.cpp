// === AddressSanitizer (ASan) — Use-After-Free (野指针/悬垂指针) ===
// Bug：free 后继续使用指针
// 场景：对象已释放但持有其引用、回调中访问已销毁对象
// 运行：cmake -DSANITIZE_ADDRESS=ON .. && make && ./asan_uaf_demo
#include <cstdio>
#include <cstdlib>
#include <cstring>

struct User {
    char name[32];
    int age;
};

int main() {
    User* u = (User*)malloc(sizeof(User));
    strncpy(u->name, "Alice", sizeof(u->name));
    u->age = 30;
    free(u);

    // BUG: u is freed, but still accessed
    printf("User: %s, age=%d\n", u->name, u->age);
    return 0;
}
