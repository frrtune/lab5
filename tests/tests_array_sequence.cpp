#include <gtest/gtest.h>
#include "../array_sequence/array_sequence.hpp"

TEST(ArraySequenceTest, ConstructorTest) {
    ArraySequence<int> sequence;
    EXPECT_EQ(sequence.GetLength(), 0);
}
TEST(ArraySequenceTest, GetFirstTest) {
    int items[] = {1, 2, 3};
    ArraySequence<int> sequence(items, 3);
    EXPECT_EQ(sequence.GetFirst(), 1);
}
TEST(ListSequenceTest, GetLastTest) {
    int items[] = {1, 2, 3};
    ListSequence<int> sequence(items, 3);
    EXPECT_EQ(sequence.GetLast(), 3);
}
TEST(ListSequenceTest, GetTest) {
    int items[] = {1, 2, 3};
    ListSequence<int> sequence(items, 3);
    EXPECT_EQ(sequence.Get(2), 3);
}
TEST(ListSequenceTest, AppendTest) {
    ListSequence<int> sequence;
    Sequence<int>* seq2 = sequence.Append(42);
    EXPECT_EQ(seq2->GetFirst(), 42);
    EXPECT_EQ(seq2->GetLength(), 1);
    delete seq2;
}
TEST(ListSequenceTest, PrependTest) {
    int items[] = {1, 2, 3};
    ListSequence<int> sequence(items, 3);
    Sequence<int>* seq2 = sequence.Prepend(123);
    EXPECT_EQ(seq2->GetFirst(), 123);
    EXPECT_EQ(seq2->GetLength(), 4);
    delete seq2;
}
TEST(ListSequenceTest, InsertAtTest) {
    int items[] = {1, 2, 3};
    ListSequence<int> sequence(items, 3);
    Sequence<int>* seq2 = sequence.InsertAt(12, 1);
    EXPECT_EQ(seq2->Get(1), 12);
    EXPECT_EQ(seq2->GetLength(), 4);
    delete seq2;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}