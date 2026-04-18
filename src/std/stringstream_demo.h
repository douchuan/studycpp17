#ifndef STUDYCPP_STD_STRINGSTREAM_DEMO_H
#define STUDYCPP_STD_STRINGSTREAM_DEMO_H

#include <sstream>
#include <string>
#include <vector>

// --- 拼接字符串（比 += 更高效的方式） ---
inline std::string join(const std::vector<std::string>& parts, char sep) {
    std::ostringstream oss;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) oss << sep;
        oss << parts[i];
    }
    return oss.str();
}

// --- 解析整数 ---
inline bool parse_int(const std::string& str, int& result) {
    std::istringstream iss(str);
    return (iss >> result) && iss.eof();
}

// --- 解析 CSV 行 ---
inline std::vector<int> parse_csv_line(const std::string& line) {
    std::vector<int> values;
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ',')) {
        values.push_back(std::stoi(token));
    }
    return values;
}

// --- 格式化输出 ---
inline std::string format_record(int id, const std::string& name, double score) {
    std::ostringstream oss;
    oss << "ID:" << id << " | Name:" << name << " | Score:" << score;
    return oss.str();
}

#endif  // STUDYCPP_STD_STRINGSTREAM_DEMO_H
