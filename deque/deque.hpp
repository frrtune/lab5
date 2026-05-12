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
};