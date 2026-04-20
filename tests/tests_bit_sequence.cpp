#include <gtest/gtest.h>
#include "../bit_sequence/bit_sequence.hpp"

TEST(BitSequenceTest, GetBitExceptionTest) {
    bool items[] = {1, 0, 1};
    BitSequence seq(items, 3);
    EXPECT_THROW(seq.GetBit(3), RangeError);
}

TEST(BitSequenceTest, GetFirstExceptionTest) {
    bool items[] = {};
    BitSequence seq(items, 0);
    EXPECT_THROW(seq.GetFirst(), RangeError);
}

TEST(BitSequenceTest, GetLastExceptionTest) {
    bool items[] = {};
    BitSequence seq(items, 0);
    EXPECT_THROW(seq.GetBit(0), RangeError);
}

TEST(BitSequenceTest, GetExceptionTest) {
    bool items[] = {1, 0, 1};
    BitSequence seq(items, 3);
    EXPECT_THROW(seq.GetBit(3), RangeError);
}

TEST(BitSequenceTest, GetSubsequenceExceptionTest) {
    bool items[] = {1, 0, 1, 0, 1};
    BitSequence seq(items, 5);
    EXPECT_THROW(seq.GetSubsequence(4, 1), InvalidArgumentError);
}

TEST(BitSequenceTest, InsertAtExceptionTest) {
    bool items[] = {1, 0, 1};
    BitSequence seq(items, 3);
    EXPECT_THROW(seq.InsertAt(0, 50), RangeError);
}

TEST(BitSequenceTest, ConcatExceptionTest) {
    bool items[] = {1, 0, 1};
    BitSequence seq(items, 3);
    EXPECT_THROW(seq.Concat(nullptr), InvalidArgumentError);
}

TEST(BitSequenceTest, ConstructorTest) {
    BitSequence seq;
    EXPECT_EQ(seq.GetLength(), 0);
}
TEST(BitSequenceTest, ArrayConstructorTest) {
    bool items[] = {1, 0, 1};
    BitSequence seq(items, 3);
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.GetBit(0), 1);
    EXPECT_EQ(seq.GetBit(1), 0);
    EXPECT_EQ(seq.GetBit(2), 1);
}
TEST(BitSequenceTest, GetFirstTest) {
    bool items[] = {1, 0, 1};
    BitSequence seq(items, 3);
    EXPECT_EQ(seq.GetFirst().GetValue(), 1);
}
TEST(BitSequenceTest, GetLastTest) {
    bool items[] = {1, 0, 1};
    BitSequence seq(items, 3);
    EXPECT_EQ(seq.GetLast().GetValue(), 1);
}
TEST(BitSequenceTest, AndTest) {
    bool items1[] = {1, 0, 1};
    bool items2[] = {1, 1, 1, 0, 0};
    BitSequence seq1(items1, 3);
    BitSequence seq2(items2, 5);
    BitSequence* result = seq1.And(seq2);
    EXPECT_EQ(result->GetLength(), 5);
    EXPECT_EQ(result->GetBit(0), 0);
    EXPECT_EQ(result->GetBit(1), 0);
    EXPECT_EQ(result->GetBit(2), 1);
    EXPECT_EQ(result->GetBit(3), 0);
    EXPECT_EQ(result->GetBit(4), 0);
    delete result;
}
TEST(BitSequenceTest, OrTest) {
    bool items1[] = {1, 0, 1};
    bool items2[] = {1, 1, 0, 0, 1};
    BitSequence seq1(items1, 3);
    BitSequence seq2(items2, 5);
    BitSequence* result = seq1.Or(seq2);
    EXPECT_EQ(result->GetLength(), 5);
    EXPECT_EQ(result->GetBit(0), 1);
    EXPECT_EQ(result->GetBit(1), 1);
    EXPECT_EQ(result->GetBit(2), 0);
    EXPECT_EQ(result->GetBit(3), 0);
    EXPECT_EQ(result->GetBit(4), 1);
    delete result;
}
TEST(BitSequenceTest, XorTest) {
    bool items1[] = {1, 0, 1};
    bool items2[] = {1, 1, 0, 0, 1};
    BitSequence seq1(items1, 3);
    BitSequence seq2(items2, 5);
    BitSequence* result = seq1.Xor(seq2);
    EXPECT_EQ(result->GetLength(), 5);
    EXPECT_EQ(result->GetBit(0), 1);
    EXPECT_EQ(result->GetBit(1), 1);
    EXPECT_EQ(result->GetBit(2), 0);
    EXPECT_EQ(result->GetBit(3), 0);
    EXPECT_EQ(result->GetBit(4), 0);
    delete result;
}