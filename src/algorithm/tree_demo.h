#ifndef STUDYCPP_ALGORITHM_TREE_DEMO_H
#define STUDYCPP_ALGORITHM_TREE_DEMO_H

#include <algorithm>
#include <memory>
#include <queue>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v = 0, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(v), left(l), right(r) {}
};

// --- 前序遍历（递归） ---
inline void preorder(TreeNode* node, std::vector<int>& out) {
    if (!node) return;
    out.push_back(node->val);
    preorder(node->left, out);
    preorder(node->right, out);
}

// --- 中序遍历（递归） ---
inline void inorder(TreeNode* node, std::vector<int>& out) {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->val);
    inorder(node->right, out);
}

// --- 层序遍历（BFS） ---
inline std::vector<std::vector<int>> level_order(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if (!root) return result;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = static_cast<int>(q.size());
        result.emplace_back();
        for (int i = 0; i < sz; ++i) {
            TreeNode* cur = q.front();
            q.pop();
            result.back().push_back(cur->val);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }
    return result;
}

// --- 最大深度 ---
inline int max_depth(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(max_depth(root->left), max_depth(root->right));
}

// --- 验证二叉搜索树 ---
inline bool is_valid_bst(TreeNode* node, long min_val = -2147483649LL,
                         long max_val = 2147483648LL) {
    if (!node) return true;
    if (node->val <= min_val || node->val >= max_val) return false;
    return is_valid_bst(node->left, min_val, node->val) &&
           is_valid_bst(node->right, node->val, max_val);
}

// --- 辅助：构建简单 BST ---
inline TreeNode* insert_bst(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val)
        root->left = insert_bst(root->left, val);
    else
        root->right = insert_bst(root->right, val);
    return root;
}

inline TreeNode* build_bst(const std::vector<int>& vals) {
    TreeNode* root = nullptr;
    for (int v : vals) root = insert_bst(root, v);
    return root;
}

// 辅助：释放树
inline void free_tree(TreeNode* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

#endif  // STUDYCPP_ALGORITHM_TREE_DEMO_H
