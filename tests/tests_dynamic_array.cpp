#include <gtest/gtest.h>
#include "../dynamic_array/dynamic_array.hpp"

TEST(DynamicArrayTest, ConstructorTest) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.GetLength(), 0);
}
TEST(DynamicArrayTest, ConstructorFromArrayTest) {
    int items[] = {0, 1, 2, 12, 3};
    DynamicArray<int> arr(items, 5);
    EXPECT_EQ(arr.GetLength(), 5);
    EXPECT_EQ(arr.Get(0), 0);
    EXPECT_EQ(arr.Get(3), 12);
}
TEST(DynamicArrayTest, SetTest) {
    DynamicArray<int> arr(3);
    arr.Set(0, 0);
    arr.Set(1, 1);
    arr.Set(2, 3);
    EXPECT_EQ(arr.Get(0), 0);
    EXPECT_EQ(arr.Get(1), 1);
    EXPECT_EQ(arr.Get(2), 3);
}
TEST(DynamicArrayTest, GetTest) {
    int items[] = {3, 1, 2};
    DynamicArray<int> arr(items, 3);
    EXPECT_EQ(arr.Get(2), 2);
}
TEST(DynamicArrayTest, GetLengthTest) {
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    EXPECT_EQ(arr.GetLength(), 3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}