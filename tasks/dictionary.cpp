#include "../deque/deque.hpp"
#include "../array_sequence/array_sequence.hpp"
#include <string>

class NameIndex {
    private:
        std::string word_;
        Deque<ArraySequence, size_t> positions_;
    public:
        NameIndex() : word_(""), positions_() {}
        NameIndex(const std::string& word, Deque<ArraySequence, size_t>& positions) : word_(word), positions_(positions) {}
        std::string get_word() const {
            return word_;
        }
        Deque<ArraySequence, size_t> get_positions() const {
            return positions_;
        }
        void add_positions(size_t position) {
            positions_.push_back(position);
        }
};

class DequeString {
    private:
        Deque<ArraySequence, NameIndex> name_indexes;
    public:
        DequeString() : name_indexes() {}
        void add_word(const std::string& word, size_t position) {
            name_indexes.push_back(word);
        }
        NameIndex get_word() {
            NameIndex word = name_indexes.pop_front();
            return word;
        }
};

class Dictionary {
    private:
        Deque<ArraySequence, size_t> banned_words_;
    public:
        Dictionary() : banned_words_() {}
        Dictionary(Deque<ArraySequence, size_t>& words) : banned_words_(words) {}
};