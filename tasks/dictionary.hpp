#include "../deque/deque.hpp"
#include "../array_sequence/array_sequence.hpp"
#include <string>

class NameIndex {
    private:
        std::string word_;
        Deque<ArraySequence, size_t> positions_;
        friend class DequeString;
    public:
        NameIndex() : word_(""), positions_() {}
        NameIndex(const std::string& word) : word_(word), positions_() {}
        NameIndex(const std::string& word, Deque<ArraySequence, size_t>& positions) : word_(word), positions_(positions) {}
        NameIndex& operator=(const NameIndex& other) {
            if (this != &other) {
                word_ = other.word_;
                positions_ = other.positions_;
            }
            return *this;
        }
        std::string get_word() const {
            return word_;
        }
        Deque<ArraySequence, size_t> get_positions() const {
            return positions_;
        }
        void add_position(size_t position) {
            positions_.push_back(position);
        }
};

class DequeString {
    private:
        Deque<ArraySequence, NameIndex> name_indexes;
    public:
        DequeString() : name_indexes() {}
        void push_word(const std::string& word, size_t position) {
            Deque<ArraySequence, NameIndex> temporary;
            bool is_found = 0;
            while (!name_indexes.empty()) {
                NameIndex current = name_indexes.pop_front();
                if (current.word_ == word) {
                    current.add_position(position);
                    is_found = 1;
                }
                temporary.push_back(current);
            }
            if (is_found == 0) {
                NameIndex new_name_index(word);
                new_name_index.add_position(position);
                temporary.push_back(new_name_index);
            }
            name_indexes = temporary;
        } 
        NameIndex pop_word() {
            NameIndex word = name_indexes.pop_front();
            return word;
        }
};

class Dictionary {
    private:
        Deque<ArraySequence, std::string> banned_words_;
    public:
        Dictionary() : banned_words_() {}
        Dictionary(Deque<ArraySequence, std::string>& words) : banned_words_(words) {}
        void push_word(const std::string& word) {
            Deque<ArraySequence, std::string> temporary;
            bool is_found = 0;
            while (!banned_words_.empty()) {
                std::string current = banned_words_.pop_front();
                if (current == word) {
                    is_found = 1;
                }   
                temporary.push_back(current);
            }
            if (is_found == 0) {
                temporary.push_back(word);
            }
            banned_words_ = temporary;
        } 
        std::string pop_word() {
            std::string word = banned_words_.pop_front();
            return word;
        }
        bool is_banned(const std::string& word) {
            Deque<ArraySequence, std::string> temporary = banned_words_;
            while(!temporary.empty()) {
                if (temporary.pop_front() == word) return 1;
            }
            return 0;
        }
};