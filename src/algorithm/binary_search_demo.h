#ifndef STUDYCPP_ALGORITHM_BINARY_SEARCH_DEMO_H
#define STUDYCPP_ALGORITHM_BINARY_SEARCH_DEMO_H

#include <vector>

// --- 二分查找（返回索引，不存在返回 -1） ---
inline int binary_search_manual(const std::vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// --- 查找第一个 >= target 的位置（lower_bound 手写版） ---
inline int lower_bound_manual(const std::vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size());
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

// --- 查找第一个 > target 的位置（upper_bound 手写版） ---
inline int upper_bound_manual(const std::vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size());
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

// --- 旋转数组中查找最小值 ---
inline int find_min_rotated(const std::vector<int>& nums) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right])
            left = mid + 1;
        else
            right = mid;
    }
    return nums[left];
}

// --- 在旋转数组中查找目标值 ---
inline int search_rotated(const std::vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[left] <= nums[mid]) {  // left half sorted
            if (nums[left] <= target && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        } else {  // right half sorted
            if (nums[mid] < target && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}

#endif  // STUDYCPP_ALGORITHM_BINARY_SEARCH_DEMO_H
