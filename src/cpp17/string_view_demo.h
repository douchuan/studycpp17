#ifndef STUDYCPP_CPP17_STRING_VIEW_DEMO_H
#define STUDYCPP_CPP17_STRING_VIEW_DEMO_H

#include <string>
#include <string_view>
#include <vector>

// --- 用 string_view 避免拷贝，统计单词数 ---
inline int count_words(std::string_view str) {
    int count = 0;
    bool in_word = false;
    for (char c : str) {
        if (c == ' ' || c == '\t') {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            ++count;
        }
    }
    return count;
}

// --- 返回子视图，不产生拷贝 ---
inline std::string_view head(std::string_view str, size_t n) {
    return str.substr(0, std::min(n, str.size()));
}

// --- 统一接受 string、string_view、C 字符串 ---
inline size_t count_char(std::string_view str, char c) {
    size_t n = 0;
    for (char ch : str) {
        if (ch == c) ++n;
    }
    return n;
}

#endif  // STUDYCPP_CPP17_STRING_VIEW_DEMO_H
