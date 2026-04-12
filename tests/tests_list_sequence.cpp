#include <gtest/gtest.h>
#include "../list_sequence/list_sequence.hpp"

TEST(ListSequenceTest, ConstructorTest) {
    ListSequence<int> sequence;
    EXPECT_EQ(sequence.GetLength(), 0);
}
TEST(LinkedListTest, GetFirst) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    EXPECT_EQ(list.GetFirst(), 1);
}
TEST(LinkedListTest, GetLast) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    EXPECT_EQ(list.GetLast(), 3);
}
TEST(LinkedListTest, Get) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    EXPECT_EQ(list.Get(2), 3);
}
TEST(LinkedListTest, Append) {
    LinkedList<int> list;
    list.Append(12);
    EXPECT_EQ(list.GetFirst(), 12);
    EXPECT_EQ(list.GetLength(), 1);
}
TEST(LinkedListTest, Prepend) {
    int items[] = {1, 2};
    LinkedList<int> list(items, 2);
    list.Prepend(12);
    EXPECT_EQ(list.GetFirst(), 12);
    EXPECT_EQ(list.GetLength(), 3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}