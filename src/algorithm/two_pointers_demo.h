#ifndef STUDYCPP_ALGORITHM_TWO_POINTERS_DEMO_H
#define STUDYCPP_ALGORITHM_TWO_POINTERS_DEMO_H

#include <algorithm>
#include <string>
#include <vector>

// --- 两数之和 II（已排序数组） ---
inline std::pair<int, int> two_sum_sorted(const std::vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) return {left, right};
        if (sum < target)
            left++;
        else
            right--;
    }
    return {-1, -1};
}

// --- 三数之和 ---
inline std::vector<std::vector<int>> three_sum(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> result;
    int n = static_cast<int>(nums.size());
    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // 去重
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum < 0)
                left++;
            else if (sum > 0)
                right--;
            else {
                result.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            }
        }
    }
    return result;
}

// --- 盛最多水的容器 ---
inline int max_area(std::vector<int> height) {
    int max_area = 0, left = 0, right = static_cast<int>(height.size()) - 1;
    while (left < right) {
        int h = std::min(height[left], height[right]);
        max_area = std::max(max_area, h * (right - left));
        if (height[left] < height[right])
            left++;
        else
            right--;
    }
    return max_area;
}

// --- 接雨水（双指针） ---
inline int trap(const std::vector<int>& height) {
    int left = 0, right = static_cast<int>(height.size()) - 1;
    int left_max = 0, right_max = 0, water = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= left_max)
                left_max = height[left];
            else
                water += left_max - height[left];
            left++;
        } else {
            if (height[right] >= right_max)
                right_max = height[right];
            else
                water += right_max - height[right];
            right--;
        }
    }
    return water;
}

// --- 回文串判断（双指针） ---
inline bool is_palindrome(const std::string& s) {
    int left = 0, right = static_cast<int>(s.size()) - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

#endif  // STUDYCPP_ALGORITHM_TWO_POINTERS_DEMO_H
