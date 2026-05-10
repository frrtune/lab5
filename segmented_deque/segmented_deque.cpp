#include "../segmented_deque/segmented_deque.hpp"

template <typename T>
SegmentedDeque<T>::SegmentedDeque() : head(nullptr), tail(nullptr), total_size(0) {};

template <typename T>
SegmentedDeque<T>::~SegmentedDeque() {
    Batch* current = head;
    while (current != nullptr) {
        Batch* next = current->next;
        delete_batch(current);
        current = next;
    }
};

template <typename T>
SegmentedDeque<T>::SegmentedDeque(const SegmentedDeque<T>& other) : head(nullptr), tail(nullptr), total_size(0) {
    Batch* current = other.head;
    while (current != nullptr) {
        Batch* new_batch = new Batch();
        new_batch->first_elem = current->first_elem;
        new_batch->elem_count = current->elem_count;
        for (size_t i = 0; i < current->elem_count; i++) {
            size_t index = current->first_elem + i;
            new(new_batch->data + index) T(current->data[index]);
        }
        if (head == nullptr) {
            head = new_batch;
            tail = new_batch;
        } else {
            tail->next = new_batch;
            new_batch->prev = tail;
            tail = new_batch;
        }
        current = current->next;
    }
    total_size = other.total_size;
};

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

template <typename T>
SegmentedDeque<T>* SegmentedDeque<T>::Append(const T& item) const {
    SegmentedDeque<T>* result = new SegmentedDeque<T>(*this);
    if (result->head == nullptr) {
        result->head = result->init_batch();
        result->tail = result->head;
    }
    if (result->tail->elem_count < batch_size) {
        new(result->tail->data + result->tail->elem_count) T(item);
        result->tail->elem_count++;
    } else {
        Batch* new_batch = result->init_batch();
        new_batch->prev = result->tail;
        result->tail->next = new_batch;
        result->tail = new_batch;
        new(result->tail->data) T(item);
        result->tail->elem_count = 1;
    }
    result->total_size = total_size + 1;
    return result;
}

template <typename T>
SegmentedDeque<T>* SegmentedDeque<T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex) throw InvalidArgumentError("start index must be less thasn end index");
    if (startIndex >= total_size || endIndex >= total_size) throw RangeError("index is out of range");
    SegmentedDeque<T>* result = new SegmentedDeque<T>();
    for (size_t i = startIndex; i <= endIndex; i++) {
        SegmentedDeque<T>* temporary = result->Append(Get(i));
        delete result;
        result = new SegmentedDeque<T>(*temporary);
        delete temporary;
    }
    return result;
}