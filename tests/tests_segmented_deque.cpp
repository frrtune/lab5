#include <gtest/gtest.h>
#include "../segmented_deque/segmented_deque.hpp"

TEST(SegmentedDequeTest, ConstructorTest) {
    SegmentedDeque<int> seg_deque;
    EXPECT_EQ(seg_deque.GetLength(), 0);
}

TEST(SegmentedDequeTest, AppendTest) {
    SegmentedDeque<int> seg_deque;
    SegmentedDeque<int>* seg_deque2 = seg_deque.Append(12);
    EXPECT_EQ(seg_deque2->GetLength(), 1);
    delete seg_deque2;
}

TEST(SegmentedDequeTest, PrependTest) {
    SegmentedDeque<int> seg_deque;
    SegmentedDeque<int>* seg_deque2 = seg_deque.Prepend(12);
    EXPECT_EQ(seg_deque2->GetLength(), 1);
    delete seg_deque2;
}

TEST(SegmentedDequeTest, IndexAtTest) {
    SegmentedDeque<int> seg_deque;
    SegmentedDeque<int>* seg_deque2 = seg_deque.InsertAt(12, 0);
    EXPECT_EQ(seg_deque2->GetLength(), 1);
    delete seg_deque2;
}

TEST(SegmentedDequeTest, ConcatTest) {
    SegmentedDeque<int> seg_deque;
    SegmentedDeque<int> seg_deque2;
    SegmentedDeque<int>* seg_deque3 = seg_deque.Prepend(3);
    SegmentedDeque<int>* seg_deque4 = seg_deque3->Prepend(4);
    seg_deque4 = seg_deque.Concat(seg_deque3);
    EXPECT_EQ(seg_deque4->GetLength(), 2);
    delete seg_deque3;
    delete seg_deque4;
}
