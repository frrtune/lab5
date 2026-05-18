#include <gtest/gtest.h>
#include "../deque/deque.hpp"
#include "../array_sequence/array_sequence.hpp"

TEST(DequeTest, PushBackTest) {
    Deque<ArraySequence, int> deque;
    deque.push_back(12);
    deque.push_back(102);
    EXPECT_EQ(deque.back(), 102);
}

TEST(DequeTest, PopBackTest) {
    Deque<ArraySequence, int> deque;
    deque.push_back(102);
    deque.push_back(12);
    EXPECT_EQ(deque.pop_back(), 12);
    EXPECT_EQ(deque.back(), 102);
}