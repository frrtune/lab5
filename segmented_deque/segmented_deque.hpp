#include "../sequence/sequence.hpp"
#include "../exceptions/exceptions.hpp"

template <typename T>
class SegmentedDeque : public Sequence <T> {
    private:
        static const size_t batch_size = 16;
        struct Batch {
            T data[batch_size];
            size_t first_elem = 0;
            size_t elem_count = 0;
            Batch* next = nullptr;
            Batch* prev = nullptr;
        };
        size_t total_size = 0;
        Batch* head = nullptr;
        Batch* tail = nullptr;
        Batch* init_batch() {
            return new Batch();
        };
        void delete_batch(Batch* batch) {
            for(size_t i = 0; i < batch->elem_count; i++) {
                batch->data[i].~T();
            }
            delete batch;
        };
    public:
        SegmentedDeque();
        SegmentedDeque(const SegmentedDeque<T>& other);
        ~SegmentedDeque();
        T GetFirst() const override;
        T GetLast() const override;
        T Get(size_t index) const override;
        SegmentedDeque<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
        size_t GetLength() const override;
        SegmentedDeque<T>* Append(const T& item) const override;
        SegmentedDeque<T>* Prepend(const T& item) const override;
        SegmentedDeque<T>* Concat(Sequence <T> *list) const override;
        SegmentedDeque<T>* InsertAt(const T& item, size_t index) const override;

        template <typename F> 
        SegmentedDeque<F>* Map(F (*func)(const T&)) const;
        T Reduce(T (*func)(const T& x1, const T& x2), const T& c) const;
        SegmentedDeque<T>* Where(bool (*func)(const T&)) const;
};

template <typename T>
SegmentedDeque<T>::SegmentedDeque() : head(nullptr), tail(nullptr), total_size(0) {}

template <typename T>
SegmentedDeque<T>::~SegmentedDeque() {
    Batch* current = head;
    while (current != nullptr) {
        Batch* next = current->next;
        delete_batch(current);
        current = next;
    }
}

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
    if (startIndex >= total_size) throw RangeError(startIndex, total_size);
    if (endIndex >= total_size) throw RangeError(endIndex, total_size);
    SegmentedDeque<T>* result = new SegmentedDeque<T>();
    SegmentedDeque<T>* result = new SegmentedDeque<T>();
    for (size_t i = startIndex; i <= endIndex; i++) {
        SegmentedDeque<T>* temporary = result->Append(Get(i));
        delete result;
        result = new SegmentedDeque<T>(*temporary);
        delete temporary;
    }
    return result;
}

template <typename T>
size_t SegmentedDeque<T>::GetLength() const {
    return total_size;
}

template <typename T>
SegmentedDeque<T>* SegmentedDeque<T>::Prepend(const T& item) const {
    SegmentedDeque<T>* result = new SegmentedDeque<T>(*this);
    if (result->head == nullptr) {
        result->head = result->init_batch();
        result->tail = result->head;
    }
    if (result->head->first_elem > 0) {
        result->head->first_elem--;
        new(result->head->data + result->head->first_elem) T(item);
        result->head->elem_count++;
    } else {
        Batch* new_batch = result->init_batch();
        new_batch->next = result->head;
        result->head->prev = new_batch;
        result->head = new_batch;
        result->head->first_elem = batch_size - 1;
        new(result->head->data + result->head->first_elem) T(item);
        result->head->elem_count = 1;
    }
    result->total_size = total_size + 1;
    return result;
}

template <typename T>
SegmentedDeque<T>* SegmentedDeque<T>::Concat(Sequence <T> *list) const {
    if (list == nullptr) throw InvalidArgumentError("argument is nullptr");
    SegmentedDeque<T>* result = new SegmentedDeque<T>(*this); 
    for (size_t i = 0; i < list->GetLength(); i++) {
        SegmentedDeque<T>* temporary = result->Append(list->Get(i));
        delete result;
        result = new SegmentedDeque<T>(*temporary);
        delete temporary;
    }
    return result;
}

template <typename T>
SegmentedDeque<T>* SegmentedDeque<T>::InsertAt(const T& item, size_t index) const {
    if (index > total_size) throw InvalidArgumentError("index must be less or equal to total size");
    if (index == 0) return Prepend(item);
    if (index == total_size) return Append(item);
    Sequence<T>* left = GetSubsequence(0, index - 1);
    Sequence<T>* right = GetSubsequence(index, total_size - 1);
    Sequence<T>* temporary = left->Append(item);
    SegmentedDeque<T>* result = temporary->Concat(right);
    delete left;
    delete right;
    delete temporary;
    return result;
}

template <typename T>
template <typename F>
SegmentedDeque<F>* SegmentedDeque<T>::Map(F (*func)(const T&)) const {
    if (func == nullptr) throw InvalidArgumentError("argument is nullptr");
    SegmentedDeque<F>* result = new SegmentedDeque<F>();
    for (size_t i = 0; i < total_size; i++) {
        SegmentedDeque<F>* temporary = result->Append(func(Get(i)));
        delete result;
        result = new SegmentedDeque<F>(*temporary);
        delete temporary;
    }
    return result;
}

template <typename T>
T SegmentedDeque<T>::Reduce(T (*func)(const T& x1, const T& x2), const T& c) const {
    if (func == nullptr) throw InvalidArgumentError("argument is nullptr");
    T result = c;
    for (size_t i = 0; i < total_size; i++) {
        result = func(result, Get(i));
    }
    return result;
}

template <typename T>
SegmentedDeque<T>* SegmentedDeque<T>::Where(bool (*func)(const T&)) const {
    if (func == nullptr) throw InvalidArgumentError("argument is nullptr");
    SegmentedDeque<T>* result = new SegmentedDeque<T>();
    for (size_t i = 0; i < total_size; i++) {
        if (func(Get(i))) {
            SegmentedDeque<T>* temporary = result->Append(Get(i));
            delete result;
            result = new SegmentedDeque<T>(*temporary);
            delete temporary; 
        }
    }
    return result;
}
