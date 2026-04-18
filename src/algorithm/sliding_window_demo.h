#ifndef STUDYCPP_ALGORITHM_SLIDING_WINDOW_DEMO_H
#define STUDYCPP_ALGORITHM_SLIDING_WINDOW_DEMO_H

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

// --- 最大子数组和（长度不超过 k） ---
// 简化为：窗口内最大和，窗口大小固定为 k

// --- 最大连续 1 的个数 III（最多翻转 k 个 0） ---
inline int longest_ones(const std::vector<int>& nums, int k) {
    int left = 0, max_len = 0;
    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        if (nums[right] == 0) k--;
        while (k < 0) {
            if (nums[left] == 0) k++;
            left++;
        }
        max_len = std::max(max_len, right - left + 1);
    }
    return max_len;
}

// --- 无重复字符的最长子串 ---
inline int longest_substring_no_repeat(const std::string& s) {
    std::unordered_map<char, int> last_pos;
    int max_len = 0, left = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        if (last_pos.count(s[right])) left = std::max(left, last_pos[s[right]] + 1);
        last_pos[s[right]] = right;
        max_len = std::max(max_len, right - left + 1);
    }
    return max_len;
}

// --- 滑动窗口最大值 ---
inline std::vector<int> sliding_window_max(const std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::vector<int> deque;  // 单调递减队列，存储索引
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        while (!deque.empty() && deque.front() <= i - k) deque.erase(deque.begin());
        while (!deque.empty() && nums[deque.back()] <= nums[i]) deque.pop_back();
        deque.push_back(i);
        if (i >= k - 1) result.push_back(nums[deque.front()]);
    }
    return result;
}

#endif  // STUDYCPP_ALGORITHM_SLIDING_WINDOW_DEMO_H
