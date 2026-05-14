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
    T pop_back() {
        if (c.GetLength() == 0) throw EmptyBufferError("deque is empty");
        T item = c.GetLast();
        if (c.GetLength() == 1)  {
            c = Container<T>();
        } else {
            Container<T>* temporary = c.GetSubsequence(0, c.GetLength() - 2);
            c = *temporary;
            delete temporary;
        }
        return item;
    }
    T pop_front() {
        if (c.GetLength() == 0) throw EmptyBufferError("deque is empty");
        T item = c.GetFirst();
        Container<T>* temporary = c.GetSubsequence(1, c.GetLength() - 1);
        c = *temporary;
        delete temporary;
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