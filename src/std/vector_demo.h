#ifndef STUDYCPP_STD_VECTOR_DEMO_H
#define STUDYCPP_STD_VECTOR_DEMO_H

#include <algorithm>
#include <numeric>
#include <optional>
#include <vector>

// --- 求和 ---
inline int sum(const std::vector<int>& v) { return std::accumulate(v.begin(), v.end(), 0); }

// --- 去重（返回新 vector，不修改原数据） ---
inline std::vector<int> unique_copy(const std::vector<int>& v) {
    std::vector<int> result = v;
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

// --- 查找第一个满足条件的元素 ---
template <typename Pred>
inline std::optional<int> find_first(const std::vector<int>& v, Pred pred) {
    auto it = std::find_if(v.begin(), v.end(), pred);
    if (it != v.end()) return *it;
    return std::nullopt;
}

#endif  // STUDYCPP_STD_VECTOR_DEMO_H
