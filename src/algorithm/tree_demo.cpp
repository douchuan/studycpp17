#include "tree_demo.h"

#include <iostream>

int main() {
    // 构建 BST: {5, 3, 7, 2, 4, 6, 8}
    auto* root = build_bst({5, 3, 7, 2, 4, 6, 8});

    std::cout << "preorder: ";
    std::vector<int> pre;
    preorder(root, pre);
    for (int x : pre) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "inorder:  ";
    std::vector<int> in;
    inorder(root, in);
    for (int x : in) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "level_order:\n";
    auto levels = level_order(root);
    for (size_t i = 0; i < levels.size(); ++i) {
        std::cout << "  level " << i << ": ";
        for (int x : levels[i]) std::cout << x << " ";
        std::cout << "\n";
    }

    std::cout << "max_depth: " << max_depth(root) << "\n";
    std::cout << "is_valid_bst: " << std::boolalpha << is_valid_bst(root) << "\n";

    free_tree(root);
    return 0;
}
