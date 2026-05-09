#include <gtest/gtest.h>
#include "../segmented_deque/segmented_deque.hpp"

TEST(SegmentedDequeTest, ConstructorTest) {
    SegmentedDeque<int> seg_deque;
    EXPECT_EQ(sequence.GetLength(), 0);
}