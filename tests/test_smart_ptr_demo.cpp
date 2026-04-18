#include <gtest/gtest.h>

#include "smart_ptr_demo.h"

TEST(SmartPtrDemoTest, UniquePtr) {
    auto s = make_unique_str("test");
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(*s, "test");
}

TEST(SmartPtrDemoTest, SharedPtr) {
    auto v = make_shared_vec();
    EXPECT_EQ(v->size(), 4u);
    EXPECT_EQ((*v)[0], 1);
    EXPECT_EQ(v.use_count(), 1);
}

TEST(SmartPtrDemoTest, CustomDeleter) {
    auto p = make_ptr_with_deleter(99);
    EXPECT_EQ(*p, 99);
}

TEST(SmartPtrDemoTest, WeakPtrAlive) {
    auto sp = std::make_shared<int>(42);
    auto wp = observe(sp);
    EXPECT_TRUE(is_alive(wp));
    sp.reset();
    EXPECT_FALSE(is_alive(wp));
}
