#include <gtest/gtest.h>

#include "chrono_demo.h"

TEST(ChronoDemoTest, SecondsToMs) {
    EXPECT_EQ(seconds_to_ms(5), 5000);
    EXPECT_EQ(seconds_to_ms(0), 0);
}

TEST(ChronoDemoTest, NowMs) {
    auto t1 = now_ms();
    sleep_ms(50);
    auto t2 = now_ms();
    EXPECT_GT(t2, t1);
    EXPECT_LT(t2 - t1, 500);  // shouldn't be more than 500ms
}

TEST(ChronoDemoTest, Measure) {
    auto [result, elapsed] = measure([]() { return 42; });
    EXPECT_EQ(result, 42);
    // elapsed should be small but non-negative
    EXPECT_GE(elapsed, 0);
}
