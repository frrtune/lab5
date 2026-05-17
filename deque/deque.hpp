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
    Deque& operator=(const Deque& other) {
        if (this != &other) {
            c = other.c;
        }
        return *this;
    }
    void push_back(const T& item) {
        c = *c.Append(item);
    }
    void push_front(const T& item) {
        c = *c.Prepend(item);
    }
    T pop_back() {
        if (c.GetLength() == 0) throw EmptyBufferError("deque is empty");
        T item = c.GetLast();
        if (c.GetLength() == 1)  {
            c = Container<T>();
        } else {
            c = *c.GetSubsequence(0, c.GetLength() - 2);
        }
        return item;
    }
    T pop_front() {
        if (c.GetLength() == 0) throw EmptyBufferError("deque is empty");
        T item = c.GetFirst();
        c = *c.GetSubsequence(1, c.GetLength() - 1);
        return item;
    }   
    T front() {
        return c.GetFirst();
    }
    T back() {
        return c.GetLast();
    }
    bool empty() {
        return c.GetLength() == 0;
    }
    size_t size() {
        return c.GetLength();
    }
};