#ifndef STUDYCPP_ALGORITHM_SEARCH_DEMO_H
#define STUDYCPP_ALGORITHM_SEARCH_DEMO_H

#include <algorithm>
#include <vector>

// --- 二分查找（要求数据已排序） ---
inline bool binary_search(const std::vector<int>& sorted, int target) {
    return std::binary_search(sorted.begin(), sorted.end(), target);
}

// --- 查找最大值和最小值 ---
inline std::pair<int, int> minmax(const std::vector<int>& v) {
    auto result = std::minmax_element(v.begin(), v.end());
    return {*result.first, *result.second};
}

// --- 统计等于 target 的元素个数 ---
inline int count_value(const std::vector<int>& v, int target) {
    return static_cast<int>(std::count(v.begin(), v.end(), target));
}

#endif  // STUDYCPP_ALGORITHM_SEARCH_DEMO_H
