#include "visitor_demo.h"

#include <iostream>

int main() {
    std::vector<std::unique_ptr<Element>> elements;
    elements.push_back(std::make_unique<ConcreteElementA>("alpha"));
    elements.push_back(std::make_unique<ConcreteElementB>(42));
    elements.push_back(std::make_unique<ConcreteElementA>("beta"));

    PrintVisitor visitor;
    for (auto& e : elements) e->accept(visitor);
    std::cout << visitor.result() << "\n";
    return 0;
}
