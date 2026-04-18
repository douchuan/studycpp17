#include "decorator_demo.h"

#include <iostream>

int main() {
    PlainText plain("hello world");
    std::cout << plain.read() << "\n";

    UpperDecorator upper(std::make_unique<PlainText>("hello world"));
    std::cout << upper.read() << "\n";
    return 0;
}
