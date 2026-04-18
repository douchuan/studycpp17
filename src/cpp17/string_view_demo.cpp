#include "string_view_demo.h"

#include <iostream>

int main() {
    std::cout << "words in 'hello world cpp': " << count_words("hello world cpp") << "\n";

    std::string s = "abcdef";
    std::cout << "head('abcdef', 3): " << head(s, 3) << "\n";

    std::cout << "count 'l' in 'hello': " << count_char("hello", 'l') << "\n";

    // C 字符串直接传，零拷贝
    std::cout << "words from literal: " << count_words("one two three") << "\n";

    return 0;
}
