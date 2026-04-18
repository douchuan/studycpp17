#include <gtest/gtest.h>

#include "tree_demo.h"

TEST(TreeDemoTest, InorderBST) {
    auto* root = build_bst({3, 1, 2});
    std::vector<int> in;
    inorder(root, in);
    EXPECT_EQ(in, (std::vector<int>{1, 2, 3}));
    free_tree(root);
}
TEST(TreeDemoTest, LevelOrder) {
    auto* root = build_bst({2, 1, 3});
    auto levels = level_order(root);
    ASSERT_EQ(levels.size(), 2u);
    EXPECT_EQ(levels[0], (std::vector<int>{2}));
    EXPECT_EQ(levels[1], (std::vector<int>{1, 3}));
    free_tree(root);
}
TEST(TreeDemoTest, MaxDepth) {
    auto* root = build_bst({1, 2, 3, 4});
    EXPECT_EQ(max_depth(root), 4);
    free_tree(root);
}
TEST(TreeDemoTest, IsValidBST) {
    auto* root = build_bst({5, 3, 7});
    EXPECT_TRUE(is_valid_bst(root));
    free_tree(root);
}
