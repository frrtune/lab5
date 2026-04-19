#pragma once

#include "../sequence/sequence.hpp"
#include "../dynamic_array/dynamic_array.hpp"

template <typename T> class MutableArraySequence : public Sequence <T> {
    private:
        DynamicArray<T> buff;
        MutableArraySequence(const DynamicArray<T>& arr);
    public:
        MutableArraySequence();
        MutableArraySequence(const T* items, size_t count);
        MutableArraySequence (const MutableArraySequence<T>& arr);
        T GetFirst() const override;
        T GetLast() const override;
        T Get(size_t index) const override;
        MutableArraySequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override;
        size_t GetLength() const override;
        void Append(const T& item) override;
        void Prepend(const T& item) override;
        void InsertAt(const T& item, size_t index) override;
        void Concat(Sequence<T>* list) override;
};

template <typename T>
MutableArraySequence<T>::MutableArraySequence() : buff() {}

template <typename T>
MutableArraySequence<T>::MutableArraySequence(const T* items, size_t count) : buff(count) {
    for (size_t i = 0; i < count; i++) {
        buff.Set(i, items[i]);
    }
}

template <typename T>
MutableArraySequence<T>::MutableArraySequence (const MutableArraySequence<T>& arr) : buff(arr.buff) {}

template <typename T>
T MutableArraySequence<T>::GetFirst() const {
    if (buff.GetLength() == 0) {
        throw RangeError("buffer is empty");   
    }
    return buff.Get(0);
};

template <typename T>
T MutableArraySequence<T>::GetLast() const {
    if (buff.GetLength() == 0) {
        throw RangeError("buffer is empty");   
    }
    return buff.Get(buff.GetLength() - 1);
};

template <typename T>
T MutableArraySequence<T>::Get(size_t index) const {
    if (index >= buff.GetLength()) {
        throw RangeError("index is out of range");   
    }
    return buff.Get(index);
};

template <typename T>
MutableArraySequence<T>* MutableArraySequence<T>::GetSubsequence(size_t start_index, size_t end_index) const {
    if (start_index >= buff.GetLength() || end_index >= buff.GetLength()) {
        throw RangeError("index is out of range");   
    }
    if (start_index > end_index) {
        throw InvalidArgumentError("start index must be less than end index");
    }
    size_t new_size = end_index - start_index + 1;
    DynamicArray<T> new_buff(new_size);
    for (size_t i = start_index; i <= end_index; i++) {
        new_buff.Set(i - start_index, buff.Get(i));
    }
    return new MutableArraySequence<T>(new_buff);
};

template <typename T>
size_t MutableArraySequence<T>::GetLength() const {
    return buff.GetLength();
};

template <typename T>
void MutableArraySequence<T>::Append(const T& item) {
    buff.Resize(buff.GetLength() + 1);
    buff.Set(buff.GetLength() - 1, item);
};

template <typename T>
void MutableArraySequence<T>::Prepend(const T& item) {
    buff.Resize(buff.GetLength() + 1);
    for (int i = buff.GetLength() - 1; i > 0; i--) {
        buff.Set(i, buff.Get(i - 1));
    }
    buff.Set(0, item);
};

template <typename T>
void MutableArraySequence<T>::InsertAt(const T& item, size_t index) {
            if (index > buff.GetLength()) {
                throw RangeError("index is out of range");
            }
            buff.Resize(buff.GetLength() + 1);
            for (int i = buff.GetLength() - 1; i > index; i++) {
                buff.Set(i, buff.Get(i - 1));
            }
            buff.Set(index, item);
        };

template <typename T>
void MutableArraySequence<T>::Concat(Sequence<T>* list) {
    if (list == nullptr) {
        throw InvalidArgumentError("argument is nullptr");
    }
    size_t this_size = this->GetLength();
    buff.Resize(buff.GetLength() + list->GetLength());
    for (size_t i = 0; i < list->GetLength(); i++) {
        buff.Set(i + this_size, list->Get(i));
    }
};