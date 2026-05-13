#include "../sequence/sequence.hpp"
#include "../exceptions/exceptions.hpp"

template <template <typename> class Container, typename T>
class Deque {
private:
    Container<T> c;
public:
    Deque() = default;
    ~Deque() = default;
    Deque(const Deque& other_deque) : c(other_deque.c) {}
    Deque(const Container<T>& other_container) : c(other_container) {}
    void push_back(const T& item) {
        Container<T>* temporary = c.Append(item);
        c = *temporary;
        delete temporary;
    }
    void push_front(const T& item) {
        Container<T>* temporary = c.Prepend(item);
        c = *temporary;
        delete temporary;
    }
};