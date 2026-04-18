#ifndef STUDYCPP_ALGORITHM_BACKTRACKING_DEMO_H
#define STUDYCPP_ALGORITHM_BACKTRACKING_DEMO_H

#include <string>
#include <vector>

// --- 全排列 ---
inline std::vector<std::vector<int>> permute(std::vector<int> nums) {
    std::vector<std::vector<int>> result;
    auto backtrack = [&](auto& self, int start) -> void {
        if (start == static_cast<int>(nums.size())) {
            result.push_back(nums);
            return;
        }
        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            std::swap(nums[start], nums[i]);
            self(self, start + 1);
            std::swap(nums[start], nums[i]);
        }
    };
    backtrack(backtrack, 0);
    return result;
}

// --- 子集（幂集） ---
inline std::vector<std::vector<int>> subsets(std::vector<int> nums) {
    std::vector<std::vector<int>> result;
    auto backtrack = [&](auto& self, int start, std::vector<int>& path) -> void {
        result.push_back(path);
        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            path.push_back(nums[i]);
            self(self, i + 1, path);
            path.pop_back();
        }
    };
    std::vector<int> path;
    backtrack(backtrack, 0, path);
    return result;
}

// --- N 皇后（返回解的数量） ---
inline int n_queens(int n) {
    int count = 0;
    std::vector<bool> cols(n, false);
    std::vector<bool> diag1(static_cast<size_t>(2 * n), false);  // row - col + n
    std::vector<bool> diag2(static_cast<size_t>(2 * n), false);  // row + col
    auto backtrack = [&](auto& self, int row) -> void {
        if (row == n) {
            count++;
            return;
        }
        for (int col = 0; col < n; ++col) {
            int d1 = row - col + n, d2 = row + col;
            if (cols[col] || diag1[d1] || diag2[d2]) continue;
            cols[col] = diag1[d1] = diag2[d2] = true;
            self(self, row + 1);
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    };
    backtrack(backtrack, 0);
    return count;
}

#endif  // STUDYCPP_ALGORITHM_BACKTRACKING_DEMO_H
