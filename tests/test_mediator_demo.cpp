#include <gtest/gtest.h>

#include "mediator_demo.h"

TEST(MediatorDemoTest, SendAndReceive) {
    ChatRoom room;
    User alice("Alice", &room);
    User bob("Bob", &room);
    room.add_user(&alice);
    room.add_user(&bob);
    alice.send("Hi Bob!");
    EXPECT_EQ(bob.messages().size(), 1);
    EXPECT_EQ(bob.messages()[0], "Alice: Hi Bob!");
    EXPECT_EQ(alice.messages().size(), 0);
}
