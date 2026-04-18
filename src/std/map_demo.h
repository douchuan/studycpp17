#ifndef STUDYCPP_STD_MAP_DEMO_H
#define STUDYCPP_STD_MAP_DEMO_H

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// --- ordered map：按键有序 ---
inline std::map<std::string, int> build_map() {
    std::map<std::string, int> m = {{"banana", 2}, {"apple", 1}, {"cherry", 3}};
    return m;  // 遍历时按 key 字母序
}

// --- unordered_map：O(1) 查找 ---
inline std::unordered_map<std::string, int> build_unordered_map() {
    return {{"banana", 2}, {"apple", 1}, {"cherry", 3}};
}

// --- 统计词频 ---
inline std::unordered_map<std::string, int> word_count(const std::vector<std::string>& words) {
    std::unordered_map<std::string, int> counts;
    for (const auto& w : words) {
        ++counts[w];
    }
    return counts;
}

// --- 安全取值：返回默认值 ---
inline int get_or_default(const std::unordered_map<std::string, int>& m, const std::string& key,
                          int default_val = 0) {
    auto it = m.find(key);
    return it != m.end() ? it->second : default_val;
}

#endif  // STUDYCPP_STD_MAP_DEMO_H
