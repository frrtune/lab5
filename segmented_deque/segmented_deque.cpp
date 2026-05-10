#include "../segmented_deque/segmented_deque.hpp"

template <typename T>
SegmentedDeque<T>::SegmentedDeque() : head(nullptr), tail(nullptr), total_size(0) {};

template <typename T>
T SegmentedDeque<T>::GetFirst() const {
    if (total_size == 0) throw RangeError("SegmentedDeque is empty");
    return head->data[head->first_elem];
}

template <typename T>
T SegmentedDeque<T>::GetLast() const {
    if (total_size == 0) throw RangeError("SegmentedDeque is empty");
    return tail->data[tail->first_elem + tail->elem_count - 1];
}

template <typename T>
T SegmentedDeque<T>::Get(size_t index) const {
    if (total_size == 0) throw RangeError("SegmentedDeque is empty");
    if (index >= total_size) throw InvalidArgumentError("index must be less than total size");
    Batch* current = head;
    while (current != nullptr) {
        if (index < current->elem_count) {
            return current->data[current->first_elem + index];
        }
        index -= current->elem_count;
        current = current->next;
    }
    throw Error("some error occured");
}