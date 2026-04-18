#include "strategy_demo.h"

#include <iostream>

int main() {
    SortContext ctx(std::make_unique<BubbleSort>());
    std::vector<int> data = {5, 2, 8, 1, 9};
    ctx.sort(data);
    std::cout << ctx.strategy_name() << ": ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
