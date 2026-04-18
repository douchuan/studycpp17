#include "fstream_demo.h"

#include <iostream>

int main() {
    const std::string path = "/tmp/studycpp_test.txt";

    // write
    if (write_file(path, "hello\nworld\ncpp\n")) {
        std::cout << "wrote file: " << path << "\n";
    }

    // read all
    std::cout << "read all:\n" << read_file(path);

    // read lines
    auto lines = read_lines(path);
    std::cout << "read " << lines.size() << " lines:\n";
    for (size_t i = 0; i < lines.size(); ++i) {
        std::cout << "  [" << i << "] " << lines[i] << "\n";
    }

    // append
    append_file(path, "extra line\n");
    std::cout << "after append, lines = " << read_lines(path).size() << "\n";

    return 0;
}
