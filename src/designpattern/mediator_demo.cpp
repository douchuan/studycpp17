#include "mediator_demo.h"

#include <iostream>

int main() {
    ChatRoom room;
    User alice("Alice", &room);
    User bob("Bob", &room);
    room.add_user(&alice);
    room.add_user(&bob);
    alice.send("Hi Bob!");
    bob.send("Hey Alice!");
    for (const auto& m : alice.messages()) std::cout << "Alice received: " << m << "\n";
    for (const auto& m : bob.messages()) std::cout << "Bob received: " << m << "\n";
    return 0;
}
