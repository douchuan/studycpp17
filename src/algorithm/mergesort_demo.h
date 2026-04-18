#ifndef STUDYCPP_ALGORITHM_MERGESORT_DEMO_H
#define STUDYCPP_ALGORITHM_MERGESORT_DEMO_H

#include <vector>

// --- 归并排序 ---
inline void merge_sort(std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    if (n <= 1) return;
    auto ms = [&](auto& self, int left, int right) -> void {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        self(self, left, mid);
        self(self, mid + 1, right);
        // merge
        std::vector<int> tmp;
        tmp.reserve(right - left + 1);
        int i = left, j = mid + 1;
        while (i <= mid && j <= right) {
            tmp.push_back(nums[i] <= nums[j] ? nums[i++] : nums[j++]);
        }
        while (i <= mid) tmp.push_back(nums[i++]);
        while (j <= right) tmp.push_back(nums[j++]);
        for (int k = 0; k < static_cast<int>(tmp.size()); ++k) nums[left + k] = tmp[k];
    };
    ms(ms, 0, n - 1);
}

// --- 逆序对计数（归并过程统计） ---
inline int count_inversions(std::vector<int> nums) {
    int count = 0;
    int n = static_cast<int>(nums.size());
    auto ms = [&](auto& self, int left, int right) -> void {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        self(self, left, mid);
        self(self, mid + 1, right);
        std::vector<int> tmp;
        tmp.reserve(right - left + 1);
        int i = left, j = mid + 1;
        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                tmp.push_back(nums[i++]);
            } else {
                count += (mid - i + 1);  // nums[i..mid] 都大于 nums[j]
                tmp.push_back(nums[j++]);
            }
        }
        while (i <= mid) tmp.push_back(nums[i++]);
        while (j <= right) tmp.push_back(nums[j++]);
        for (int k = 0; k < static_cast<int>(tmp.size()); ++k) nums[left + k] = tmp[k];
    };
    ms(ms, 0, n - 1);
    return count;
}

#endif  // STUDYCPP_ALGORITHM_MERGESORT_DEMO_H
