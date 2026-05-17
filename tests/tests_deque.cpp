#include <gtest/gtest.h>
#include "../deque/deque.hpp"
#include "../array_sequence/array_sequence.hpp"

TEST(DequeTest, PushFrontTest) {
    Deque<ArraySequence, int> deque;
    deque.push_back(12);
    EXPECT_EQ(deque.back(), 12);
}