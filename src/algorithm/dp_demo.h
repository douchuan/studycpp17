#ifndef STUDYCPP_ALGORITHM_DP_DEMO_H
#define STUDYCPP_ALGORITHM_DP_DEMO_H

#include <algorithm>
#include <string>
#include <vector>

// --- 斐波那契（迭代，O(n) 时间 O(1) 空间） ---
inline int fib(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int t = a + b;
        a = b;
        b = t;
    }
    return b;
}

// --- 爬楼梯（每次 1 或 2 步） ---
inline int climb_stairs(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; ++i) {
        int t = a + b;
        a = b;
        b = t;
    }
    return b;
}

// --- 0-1 背包 ---
inline int knapsack(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    int n = static_cast<int>(weights.size());
    std::vector<int> dp(capacity + 1, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = capacity; j >= weights[i]; --j) {
            dp[j] = std::max(dp[j], dp[j - weights[i]] + values[i]);
        }
    }
    return dp[capacity];
}

// --- 最长公共子序列（LCS） ---
inline int longest_common_subsequence(const std::string& s1, const std::string& s2) {
    int m = static_cast<int>(s1.size()), n = static_cast<int>(s2.size());
    std::vector<int> dp(n + 1, 0);
    for (int i = 1; i <= m; ++i) {
        int prev = 0;
        for (int j = 1; j <= n; ++j) {
            int temp = dp[j];
            if (s1[i - 1] == s2[j - 1])
                dp[j] = prev + 1;
            else
                dp[j] = std::max(dp[j], dp[j - 1]);
            prev = temp;
        }
    }
    return dp[n];
}

// --- 最长递增子序列（LIS，O(n log n)） ---
inline int longest_increasing_subsequence(const std::vector<int>& nums) {
    std::vector<int> tails;
    for (int x : nums) {
        auto it = std::lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end())
            tails.push_back(x);
        else
            *it = x;
    }
    return static_cast<int>(tails.size());
}

// --- 最大子数组和（Kadane 算法） ---
inline int max_subarray(const std::vector<int>& nums) {
    int best = nums[0], cur = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        cur = std::max(nums[i], cur + nums[i]);
        best = std::max(best, cur);
    }
    return best;
}

#endif  // STUDYCPP_ALGORITHM_DP_DEMO_H
