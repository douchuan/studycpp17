#ifndef STUDYCPP_ALGORITHM_TRANSFORM_DEMO_H
#define STUDYCPP_ALGORITHM_TRANSFORM_DEMO_H

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

// --- map：对每个元素应用函数 ---
template <typename Fn>
inline std::vector<int> transform(const std::vector<int>& v, Fn fn) {
    std::vector<int> result;
    result.reserve(v.size());
    std::transform(v.begin(), v.end(), std::back_inserter(result), fn);
    return result;
}

// --- filter：保留满足条件的元素 ---
template <typename Pred>
inline std::vector<int> filter(const std::vector<int>& v, Pred pred) {
    std::vector<int> result;
    std::copy_if(v.begin(), v.end(), std::back_inserter(result), pred);
    return result;
}

// --- reduce：折叠为单个值 ---
template <typename Op>
inline int reduce(const std::vector<int>& v, int init, Op op) {
    return std::accumulate(v.begin(), v.end(), init, op);
}

#endif  // STUDYCPP_ALGORITHM_TRANSFORM_DEMO_H
