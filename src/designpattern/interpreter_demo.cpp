#include "interpreter_demo.h"

#include <iostream>

int main() {
    auto e1 = std::make_unique<TerminalExpression>("hello");
    auto e2 = std::make_unique<TerminalExpression>("world");
    auto or_expr = std::make_unique<OrExpression>(std::move(e1), std::move(e2));
    std::cout << "'say hello world' contains hello or world: " << std::boolalpha
              << or_expr->interpret("say hello world") << "\n";
    return 0;
}
