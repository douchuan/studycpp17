#include "filesystem_demo.h"

#include <iostream>

namespace fs = std::filesystem;

int main() {
    fs::path p = "/tmp/example.cpp";

    std::cout << "extension of 'example.cpp': " << get_extension(p) << "\n";
    std::cout << "stem of 'example.cpp': " << stem(p) << "\n";

    // List files in current directory
    std::cout << "files in current dir:\n";
    for (const auto& f : list_files(".")) {
        std::cout << "  " << f << "\n";
    }

    return 0;
}
