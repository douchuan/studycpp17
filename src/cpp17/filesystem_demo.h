#ifndef STUDYCPP_CPP17_FILESYSTEM_DEMO_H
#define STUDYCPP_CPP17_FILESYSTEM_DEMO_H

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// --- 获取文件扩展名 ---
inline std::string get_extension(const fs::path& p) { return p.extension().string(); }

// --- 获取不带扩展名的文件名 ---
inline std::string stem(const fs::path& p) { return p.stem().string(); }

// --- 获取文件大小（字节） ---
inline std::uintmax_t file_size(const fs::path& p) {
    if (fs::exists(p) && fs::is_regular_file(p)) {
        return fs::file_size(p);
    }
    return 0;
}

// --- 列出目录下所有文件 ---
inline std::vector<std::string> list_files(const fs::path& dir) {
    std::vector<std::string> files;
    if (fs::exists(dir) && fs::is_directory(dir)) {
        for (const auto& entry : fs::directory_iterator(dir)) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

#endif  // STUDYCPP_CPP17_FILESYSTEM_DEMO_H
