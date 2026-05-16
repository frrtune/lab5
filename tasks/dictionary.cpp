#include "../deque/deque.hpp"
#include "../array_sequence/array_sequence.hpp"
#include <string>

class NameIndex {
    private:
        std::string word_;
        Deque<ArraySequence, size_t> positions_;
    public:
        NameIndex() : word_(""), positions_() {}
        NameIndex(const std::string& word, ArraySequence<size_t> positions) : word_(word), positions_(positions) {}
};  