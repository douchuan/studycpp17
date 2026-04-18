#include <gtest/gtest.h>

#include "heap_demo.h"

TEST(HeapDemoTest, MinHeapPushPop) {
    MinHeap h;
    h.push(5);
    h.push(2);
    h.push(8);
    EXPECT_EQ(h.top(), 2);
    h.pop();
    EXPECT_EQ(h.top(), 5);
}
TEST(HeapDemoTest, TopK) {
    auto result = top_k_heap({3, 2, 1, 5, 6, 4}, 3);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 6);
}
