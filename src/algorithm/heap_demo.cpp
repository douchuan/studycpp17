#include "heap_demo.h"

#include <iostream>

int main() {
    MinHeap heap;
    heap.push(5);
    heap.push(2);
    heap.push(8);
    heap.push(1);
    std::cout << "min_heap top: " << heap.top() << "\n";
    heap.pop();
    std::cout << "after pop top: " << heap.top() << "\n";

    std::vector<int> nums = {3, 2, 1, 5, 6, 4};
    auto top3 = top_k_heap(nums, 3);
    std::cout << "top 3: ";
    for (int x : top3) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
