#include <gtest/gtest.h>
#include "../tasks/dictionary.hpp"

TEST(DequeStringTest, PushWordTest) {
    DequeString words;
    words.push_word("team", 0);
    words.push_word("spirit", 1);
    words.push_word("champions", 2);
    words.push_word("pgl", 3);
    words.push_word("astana", 4);
    NameIndex word = words.pop_word();
    EXPECT_EQ(word.get_word(), "team");
    word = words.pop_word();
    EXPECT_EQ(word.get_word(), "spirit");
    word = words.pop_word();
    EXPECT_EQ(word.get_word(), "champions");
    word = words.pop_word();
    EXPECT_EQ(word.get_word(), "pgl");
    word = words.pop_word();
    EXPECT_EQ(word.get_word(), "astana");
}

TEST(DictionaryTest, IsBannedTest) {
    Dictionary dict;
    dict.push_word("falcons");
    dict.push_word("monesy");
    EXPECT_EQ(dict.is_banned("falcons"), 1);
    EXPECT_EQ(dict.is_banned("monesy"), 1);
}