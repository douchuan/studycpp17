#include <gtest/gtest.h>

#include "state_demo.h"

TEST(StateDemoTest, InsertCoinThenDispense) {
    auto vm = std::make_unique<VendingMachine>(std::make_unique<IdleState>());
    EXPECT_EQ(vm->current_state(), "Idle");
    vm->insert_coin();
    EXPECT_EQ(vm->current_state(), "HasCoin");
    vm->dispense();
    EXPECT_EQ(vm->current_state(), "Idle");
}

TEST(StateDemoTest, DispenseWithoutCoin) {
    auto vm = std::make_unique<VendingMachine>(std::make_unique<IdleState>());
    EXPECT_EQ(vm->dispense(), "insert coin first");
}
