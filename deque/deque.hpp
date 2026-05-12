#include "../sequence/sequence.hpp"
#include "../exceptions/exceptions.hpp"

template <template <typename> class Container, typename T>
class Deque {
private:
    Container<T> c;
};


