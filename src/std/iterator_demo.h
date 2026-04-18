#ifndef STUDYCPP_STD_ITERATOR_DEMO_H
#define STUDYCPP_STD_ITERATOR_DEMO_H

#include <algorithm>
#include <iterator>
#include <list>
#include <vector>

// --- advance / next / prev ---
inline int nth_element(std::vector<int> v, int n) {
    auto it = v.begin();
    std::advance(it, n);
    return *it;
}

inline std::vector<int>::iterator find_n_steps(std::vector<int>::iterator it, int steps) {
    return std::next(it, steps);
}

// --- back_inserter ---
inline std::vector<int> copy_and_double(const std::vector<int>& src) {
    std::vector<int> dest;
    std::transform(src.begin(), src.end(), std::back_inserter(dest), [](int x) { return x * 2; });
    return dest;
}

// --- distance ---
inline int count_until(const std::vector<int>& v, int target) {
    auto it = std::find(v.begin(), v.end(), target);
    return static_cast<int>(std::distance(v.begin(), it));
}

// --- iterator range for_each ---
inline int sum_via_for_each(const std::vector<int>& v) {
    int total = 0;
    std::for_each(v.begin(), v.end(), [&total](int x) { total += x; });
    return total;
}

#endif  // STUDYCPP_STD_ITERATOR_DEMO_H
