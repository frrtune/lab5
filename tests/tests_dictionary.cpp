#include <gtest/gtest.h>
#include "../tasks/dictionary.hpp"

TEST(DequeStringTest, PushWordTest) {
    DequeString words;
    words.push_word("spirit", 0);
    NameIndex champions = words.pop_word();
    EXPECT_EQ(champions.get_word(), "spirit");
}