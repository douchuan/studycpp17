#ifndef STUDYCPP_ALGORITHM_QUICKSORT_DEMO_H
#define STUDYCPP_ALGORITHM_QUICKSORT_DEMO_H

#include <vector>

// --- 快速排序（原地 partition） ---
inline void quick_sort(std::vector<int>& nums) {
    if (nums.empty()) return;
    auto qs = [&](auto& self, int left, int right) -> void {
        if (left >= right) return;
        int pivot = nums[right];
        int i = left;
        for (int j = left; j < right; ++j) {
            if (nums[j] < pivot) std::swap(nums[i++], nums[j]);
        }
        std::swap(nums[i], nums[right]);
        self(self, left, i - 1);
        self(self, i + 1, right);
    };
    qs(qs, 0, static_cast<int>(nums.size()) - 1);
}

// --- 第 K 大元素（快速选择，O(n) 期望） ---
inline int quick_select(std::vector<int> nums, int k) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int pivot = nums[right];
        int i = left;
        for (int j = left; j < right; ++j) {
            if (nums[j] > pivot) std::swap(nums[i++], nums[j]);  // 降序找第K大
        }
        std::swap(nums[i], nums[right]);
        if (i == k - 1) return nums[i];
        if (i > k - 1)
            right = i - 1;
        else
            left = i + 1;
    }
    return -1;
}

#endif  // STUDYCPP_ALGORITHM_QUICKSORT_DEMO_H
