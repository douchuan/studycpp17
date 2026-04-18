#include "linked_list_demo.h"

#include <iostream>

int main() {
    // reverse
    auto* l1 = build_list({1, 2, 3, 4, 5});
    auto* rev = reverse_list(l1);
    std::cout << "reversed: ";
    for (int x : to_vec(rev)) std::cout << x << " ";
    std::cout << "\n";
    free_list(rev);

    // merge
    auto* a = build_list({1, 3, 5});
    auto* b = build_list({2, 4, 6});
    auto* merged = merge_two_lists(a, b);
    std::cout << "merged: ";
    for (int x : to_vec(merged)) std::cout << x << " ";
    std::cout << "\n";
    free_list(merged);

    // middle
    auto* l2 = build_list({1, 2, 3, 4, 5});
    auto* mid = find_middle(l2);
    std::cout << "middle: " << mid->val << "\n";
    free_list(l2);

    return 0;
}
