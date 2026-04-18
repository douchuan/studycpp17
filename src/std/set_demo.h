#ifndef STUDYCPP_STD_SET_DEMO_H
#define STUDYCPP_STD_SET_DEMO_H

#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// --- 去重集合 ---
inline std::set<int> unique_set(std::vector<int> v) { return {v.begin(), v.end()}; }

// --- 交集 ---
inline std::set<int> set_intersection(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result;
    for (const auto& x : a) {
        if (b.count(x)) result.insert(x);
    }
    return result;
}

// --- 差集 (a - b) ---
inline std::set<int> set_difference(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result;
    for (const auto& x : a) {
        if (!b.count(x)) result.insert(x);
    }
    return result;
}

// --- 快速查找（unordered_set） ---
inline bool contains(const std::unordered_set<std::string>& s, const std::string& key) {
    return s.find(key) != s.end();
}

#endif  // STUDYCPP_STD_SET_DEMO_H
