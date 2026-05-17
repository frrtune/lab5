#include <pdcurses.h>
#include <string>
#include "../dynamic_array/dynamic_array.hpp"
#include "../tasks/dictionary.hpp"

DynamicArray<std::string> split_words(const std::string& str) {
    DynamicArray<std::string> words;
    std::string word;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\t') {
            if (word.empty() == 0) {
                words.Resize(words.GetLength() + 1);
                words.Set(words.GetLength() - 1, word);
                word.clear();
            }
        } else {
            word += str[i];
        }
    }
    if (word.empty() == 0) {
        words.Resize(words.GetLength() + 1);
        words.Set(words.GetLength() - 1, word);
    }
    return words;
}