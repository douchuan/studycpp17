#ifndef STUDYCPP_STD_STRING_DEMO_H
#define STUDYCPP_STD_STRING_DEMO_H

#include <algorithm>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// --- 字符串分割 ---
inline std::vector<std::string> split(std::string_view str, char delim) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delim);
    while (end != std::string_view::npos) {
        tokens.emplace_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delim, start);
    }
    tokens.emplace_back(str.substr(start));
    return tokens;
}

// --- 字符串修剪（去掉两端空白） ---
inline std::string trim(std::string_view str) {
    auto start = str.find_first_not_of(" \t\n\r");
    if (start == std::string_view::npos) return "";
    auto end = str.find_last_not_of(" \t\n\r");
    return std::string(str.substr(start, end - start + 1));
}

// --- 判断回文 ---
inline bool is_palindrome(std::string_view str) {
    size_t left = 0;
    size_t right = str.size();
    if (right == 0) return true;
    --right;
    while (left < right) {
        if (str[left] != str[right]) return false;
        ++left;
        --right;
    }
    return true;
}

#endif  // STUDYCPP_STD_STRING_DEMO_H
