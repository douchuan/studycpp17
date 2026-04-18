#ifndef STUDYCPP_STD_FSTREAM_DEMO_H
#define STUDYCPP_STD_FSTREAM_DEMO_H

#include <fstream>
#include <string>
#include <vector>

// --- 写入文件 ---
inline bool write_file(const std::string& path, const std::string& content) {
    std::ofstream ofs(path);
    if (!ofs) return false;
    ofs << content;
    return ofs.good();
}

// --- 追加 ---
inline bool append_file(const std::string& path, const std::string& content) {
    std::ofstream ofs(path, std::ios::app);
    if (!ofs) return false;
    ofs << content;
    return ofs.good();
}

// --- 读取全文 ---
inline std::string read_file(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) return "";
    return {(std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>()};
}

// --- 逐行读取 ---
inline std::vector<std::string> read_lines(const std::string& path) {
    std::vector<std::string> lines;
    std::ifstream ifs(path);
    std::string line;
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }
    return lines;
}

#endif  // STUDYCPP_STD_FSTREAM_DEMO_H
