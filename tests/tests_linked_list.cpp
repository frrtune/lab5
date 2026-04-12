#include <gtest/gtest.h>
#include "../linked_list/linked_list.hpp"

TEST(LinkedListTest, ConstructorTest) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    EXPECT_EQ(list.Get(1), 2);
}
TEST(LinkedListTest, GetFirstTest) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    EXPECT_EQ(list.GetFirst(), 1);
}
TEST(LinkedListTest, GetLastTest) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    EXPECT_EQ(list.GetLast(), 3);
}
TEST(LinkedListTest, GetTest) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    EXPECT_EQ(list.Get(2), 3);
}
TEST(LinkedListTest, AppendTest) {
    LinkedList<int> list;
    list.Append(12);
    EXPECT_EQ(list.GetFirst(), 12);
    EXPECT_EQ(list.GetLength(), 1);
}
TEST(LinkedListTest, PrependTest) {
    int items[] = {1, 2};
    LinkedList<int> list(items, 2);
    list.Prepend(12);
    EXPECT_EQ(list.GetFirst(), 12);
    EXPECT_EQ(list.GetLength(), 3);
}