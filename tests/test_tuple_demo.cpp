#include <gtest/gtest.h>

#include "tuple_demo.h"

TEST(TupleDemoTest, MakeRecord) {
    auto record = make_record();
    EXPECT_EQ(std::get<0>(record), 1);
    EXPECT_EQ(std::get<1>(record), "Alice");
    EXPECT_DOUBLE_EQ(std::get<2>(record), 95.5);
}

TEST(TupleDemoTest, UnpackRecord) {
    auto record = make_record();
    int id;
    std::string name;
    double score;
    unpack_record(record, id, name, score);
    EXPECT_EQ(id, 1);
    EXPECT_EQ(name, "Alice");
    EXPECT_DOUBLE_EQ(score, 95.5);
}

TEST(TupleDemoTest, DivideRemainder) {
    auto [q, r] = divide_remainder(17, 5);
    EXPECT_EQ(q, 3);
    EXPECT_EQ(r, 2);
}

TEST(TupleDemoTest, BuildConfig) {
    auto cfg = build_config();
    EXPECT_EQ(cfg.timeout, 30);
    EXPECT_EQ(cfg.host, "localhost");
}
