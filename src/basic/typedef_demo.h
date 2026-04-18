#ifndef STUDYCPP_BASIC_TYPEDEF_DEMO_H
#define STUDYCPP_BASIC_TYPEDEF_DEMO_H

// typedef 完整示例
// 使用场景：简化复杂类型名称、提高代码可读性、
// 统一类型别名（方便后续整体替换底层类型）
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// NOLINTBEGIN(modernize-use-using)
// This file intentionally uses typedef to demonstrate the legacy syntax
// ========== 1. 基本类型别名 ==========

// 场景：统一数值类型，后续只需改一处即可全局替换
typedef int64_t user_id_t;
typedef double currency_t;

// 场景：明确语义（避免裸 int 在不同位置含义不清）
typedef int score_t;
typedef int age_t;

// ========== 2. 指针类型别名 ==========

struct User {
    user_id_t id;
    std::string name;
};

// 场景：简化指针类型（现代代码优先用 using 或别名模板，但 typedef 仍广泛存在）
typedef User* user_ptr;
typedef const User* const_user_ptr;

// ========== 3. 函数指针别名 ==========

// 场景：回调函数签名简化
typedef bool (*compare_func)(score_t a, score_t b);
typedef void (*callback_func)(const User& user, score_t score);

// ========== 4. 容器类型别名 ==========

// 场景：长模板类型简化
typedef std::vector<User> user_list;
typedef std::map<user_id_t, User> user_registry;
typedef std::pair<user_id_t, score_t> user_score_pair;

// 场景：嵌套容器
typedef std::vector<std::vector<int>> int_matrix;
typedef std::map<std::string, std::vector<user_score_pair>> group_score_map;

// ========== 5. 智能指针别名 ==========

typedef std::shared_ptr<User> user_shared_ptr;
typedef std::unique_ptr<User> user_unique_ptr;

// ========== 6. 结构体/联合体中的 typedef ==========

// 场景：C 风格结构体免写 struct 关键字（C++ 中非必需，但兼容 C 代码时常见）
typedef struct {
    currency_t amount;
    const char* currency_code;
} Money;

// ========== 7. 数组类型别名 ==========

// 场景：固定大小数组的便捷定义（如网络缓冲区、棋盘、哈希桶等）
typedef int array_t[100];         // 固定大小一维数组
typedef char buffer_t[256];       // 字符缓冲区
typedef int chess_board_t[8][8];  // 二维数组（棋盘）

// 数组类型作为函数参数时，退化为指针，但语法上更清晰
inline void fill_array(array_t arr, int count) {
    for (int i = 0; i < count; ++i) arr[i] = i * 10;
}

inline int sum_array(array_t arr, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) total += arr[i];
    return total;
}

// 二维数组操作
inline void init_board(chess_board_t board) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) board[i][j] = (i + j) % 2;
}
// NOLINTEND(modernize-use-using)

inline bool ascending(score_t a, score_t b) { return a < b; }
inline bool descending(score_t a, score_t b) { return a > b; }

// ========== 使用函数 ==========

inline user_list create_users() { return {User{1, "Alice"}, User{2, "Bob"}, User{3, "Charlie"}}; }

inline user_registry build_registry(const user_list& users) {
    user_registry reg;
    for (const auto& u : users) reg[u.id] = u;
    return reg;
}

inline int_matrix create_matrix(int rows, int cols) {
    return int_matrix(rows,
                      std::vector<int>(cols, 0));  // NOLINT(modernize-return-braced-init-list)
}

inline user_shared_ptr make_user_shared(user_id_t id, const std::string& name) {
    return std::make_shared<User>(User{id, name});
}

inline user_unique_ptr make_user_unique(user_id_t id, const std::string& name) {
    return std::make_unique<User>(User{id, name});
}

// 函数指针作为参数
inline score_t apply_compare(score_t a, score_t b, compare_func cmp) { return cmp(a, b) ? a : b; }

#endif  // STUDYCPP_BASIC_TYPEDEF_DEMO_H
