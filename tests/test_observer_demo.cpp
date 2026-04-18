#include <gtest/gtest.h>

#include "observer_demo.h"

TEST(ObserverDemoTest, NotifyObserver) {
    Subject subject;
    LogObserver observer;
    subject.attach(&observer);
    subject.notify("event1");
    subject.notify("event2");
    const auto& events = observer.events();
    ASSERT_EQ(events.size(), 2);
    EXPECT_EQ(events[0], "event1");
    EXPECT_EQ(events[1], "event2");
}

TEST(ObserverDemoTest, DetachObserver) {
    Subject subject;
    LogObserver observer;
    subject.attach(&observer);
    subject.detach(&observer);
    subject.notify("event");
    EXPECT_EQ(observer.events().size(), 0);
}
