#ifndef STUDYCPP_ALGORITHM_SORT_DEMO_H
#define STUDYCPP_ALGORITHM_SORT_DEMO_H

#include <algorithm>
#include <functional>
#include <vector>

// --- 升序排序（返回新 vector） ---
inline std::vector<int> sort_asc(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    return v;
}

// --- 降序排序 ---
inline std::vector<int> sort_desc(std::vector<int> v) {
    std::sort(v.begin(), v.end(), std::greater<>{});
    return v;
}

// --- 部分排序：取前 k 个最小元素 ---
inline std::vector<int> top_k(std::vector<int> v, int k) {
    if (k <= 0) return {};
    if (k >= static_cast<int>(v.size())) {
        std::sort(v.begin(), v.end());
        return v;
    }
    std::partial_sort(v.begin(), v.begin() + k, v.end());
    v.resize(k);
    return v;
}

// --- 判断是否有序 ---
inline bool is_sorted(const std::vector<int>& v) { return std::is_sorted(v.begin(), v.end()); }

#endif  // STUDYCPP_ALGORITHM_SORT_DEMO_H
