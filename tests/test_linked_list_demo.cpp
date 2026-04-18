#include <gtest/gtest.h>

#include "linked_list_demo.h"

TEST(LinkedListDemoTest, Reverse) {
    auto* l = build_list({1, 2, 3});
    auto* rev = reverse_list(l);
    EXPECT_EQ(to_vec(rev), (std::vector<int>{3, 2, 1}));
    free_list(rev);
}
TEST(LinkedListDemoTest, MergeTwoLists) {
    auto* a = build_list({1, 3});
    auto* b = build_list({2, 4});
    auto* m = merge_two_lists(a, b);
    EXPECT_EQ(to_vec(m), (std::vector<int>{1, 2, 3, 4}));
    free_list(m);
}
TEST(LinkedListDemoTest, FindMiddle) {
    auto* l = build_list({1, 2, 3, 4, 5});
    EXPECT_EQ(find_middle(l)->val, 3);
    free_list(l);
}
TEST(LinkedListDemoTest, RemoveNthFromEnd) {
    auto* l = build_list({1, 2, 3, 4, 5});
    auto* r = remove_nth_from_end(l, 2);
    EXPECT_EQ(to_vec(r), (std::vector<int>{1, 2, 3, 5}));
    free_list(r);
}
