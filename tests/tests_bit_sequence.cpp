#include <gtest/gtest.h>
#include "../bit_sequence/bit_sequence.hpp"

TEST(BitSequenceTest, ConstructorTest) {
    BitSequence sequence;
    EXPECT_EQ(seq.GetLength(), 0);
}
TEST(BitSequenceTest, ArrayConstructorTest) {
    bool items[] = {1, 0, 1};
    BitSequence sequence(items, 5);
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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}