#include <gtest/gtest.h>

#include "event_queue.hxx"


TEST(EventQueueTest, SingleEventInQueue)
{
    std::vector<edgas::Event> events = {
        edgas::Event{.time = 5.0}
    };
    edgas::EventQueue queue(events);

    EXPECT_EQ(0, queue.top());
}


TEST(EventQueueTest, UpdateTopWhenQueueHasTwoEvents)
{
    std::vector<edgas::Event> events = {
        edgas::Event{.time = 7.2},
        edgas::Event{.time = 4.5}
    };
    edgas::EventQueue queue(events);

    EXPECT_EQ(1, queue.top());

    events[1].time = 8.7;
    queue.update(1, events[1].time);
    EXPECT_EQ(0, queue.top());
}


TEST(EventQueueTest, UpdateTopWhenQueueHasSeveralEvents)
{
    std::vector<edgas::Event> events = {
        edgas::Event{.time = 9.1},
        edgas::Event{.time = 7.2},
        edgas::Event{.time = 4.9},
        edgas::Event{.time = 5.4},
        edgas::Event{.time = 2.3},
    };
    edgas::EventQueue queue(events);

    EXPECT_EQ(4, queue.top());

    events[4].time = 8.7;
    queue.update(4, events[4].time);
    EXPECT_EQ(2, queue.top());

    events[2].time = 11.3;
    queue.update(2, events[2].time);
    EXPECT_EQ(3, queue.top());
}


TEST(EventQueueTest, UpdateNonTopToTopWhenQueueHasTwoEvents)
{
    std::vector<edgas::Event> events = {
        edgas::Event{.time = 7.2},
        edgas::Event{.time = 4.5}
    };
    edgas::EventQueue queue(events);

    EXPECT_EQ(1, queue.top());

    events[0].time = 3.7;
    queue.update(0, events[0].time);
    EXPECT_EQ(0, queue.top());
}


TEST(EventQueueTest, UpdateNonTopWhenQueueHasSeveralEvents)
{
    std::vector<edgas::Event> events = {
        edgas::Event{.time = 7.2},
        edgas::Event{.time = 4.9},
        edgas::Event{.time = 5.4},
        edgas::Event{.time = 6.3},
    };
    edgas::EventQueue queue(events);

    ASSERT_EQ(1, queue.top());

    events[3].time = 3.7;
    queue.update(3, events[3].time);
    ASSERT_EQ(3, queue.top());

    events[0].time = 2.3;
    queue.update(0, events[0].time);
    EXPECT_EQ(0, queue.top());
}

// EOF