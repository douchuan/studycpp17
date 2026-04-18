#include "typedef_demo.h"

#include <iostream>

int main() {
    std::cout << "=== typedef 完整示例 ===\n\n";

    // 1. 基本类型别名
    user_id_t uid = 1001;
    currency_t price = 99.50;
    score_t s = 85;
    std::cout << "=== 基本类型别名 ===\n";
    std::cout << "user_id_t: " << uid << "\n";
    std::cout << "currency_t: " << price << "\n";
    std::cout << "score_t: " << s << "\n\n";

    // 2. 指针类型别名
    User u{1, "Alice"};
    user_ptr ptr = &u;
    const_user_ptr cptr = &u;
    std::cout << "=== 指针类型别名 ===\n";
    std::cout << "user_ptr->name: " << ptr->name << "\n";
    std::cout << "const_user_ptr->name: " << cptr->name << "\n\n";

    // 3. 函数指针别名
    std::cout << "=== 函数指针别名 ===\n";
    std::cout << "ascending(10, 20): " << ascending(10, 20) << "\n";
    std::cout << "descending(10, 20): " << descending(10, 20) << "\n";
    std::cout << "apply_compare(10, 20, ascending): " << apply_compare(10, 20, ascending) << "\n";
    std::cout << "apply_compare(10, 20, descending): " << apply_compare(10, 20, descending)
              << "\n\n";

    // 4. 容器类型别名
    std::cout << "=== 容器类型别名 ===\n";
    user_list users = create_users();
    for (const auto& u : users) std::cout << "User: id=" << u.id << ", name=" << u.name << "\n";

    user_registry reg = build_registry(users);
    std::cout << "Registry size: " << reg.size() << "\n";
    std::cout << "Find user 2: " << reg[2].name << "\n";

    int_matrix mat = create_matrix(2, 3);
    std::cout << "Matrix[0][1]: " << mat[0][1] << "\n\n";

    // 5. 智能指针别名
    std::cout << "=== 智能指针别名 ===\n";
    auto sp = make_user_shared(10, "Dave");
    std::cout << "shared_ptr: id=" << sp->id << ", name=" << sp->name << "\n";
    std::cout << "use_count: " << sp.use_count() << "\n";

    auto up = make_user_unique(20, "Eve");
    std::cout << "unique_ptr: id=" << up->id << ", name=" << up->name << "\n\n";

    // 6. 结构体中的 typedef
    std::cout << "=== 结构体 typedef ===\n";
    Money m{100.00, "USD"};
    std::cout << "Money: " << m.amount << " " << m.currency_code << "\n\n";

    // 7. 数组类型别名
    std::cout << "=== 数组类型别名 ===\n";
    array_t arr;
    fill_array(arr, 10);
    std::cout << "fill_array(arr, 10): ";
    for (int i = 0; i < 10; ++i) std::cout << arr[i] << " ";
    std::cout << "\nsum_array(arr, 10): " << sum_array(arr, 10) << "\n";

    buffer_t buf = "Hello, typedef array!";
    std::cout << "buffer_t: " << buf << "\n";

    chess_board_t board;
    init_board(board);
    std::cout << "Chess board top-left 3x3:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) std::cout << board[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";

    return 0;
}
