#include "chain_of_responsibility_demo.h"

#include <iostream>

int main() {
    auto auth = std::make_unique<AuthHandler>();
    auto log = std::make_unique<LogHandler>();
    auth->set_next(std::move(log));
    std::cout << auth->handle("auth") << "\n";
    std::cout << auth->handle("log") << "\n";
    std::cout << auth->handle("unknown") << "\n";
    return 0;
}
