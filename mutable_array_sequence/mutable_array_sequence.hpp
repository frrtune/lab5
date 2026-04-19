#pragma once

#include "../sequence/sequence.hpp"
#include "../dynamic_array/dynamic_array.hpp"

template <typename T> class MutableArraySequence : public Sequence <T> {
    private:
        DynamicArray<T> buff;
        MutableArraySequence(const DynamicArray<T>& arr) : buff(arr) {}
    public:
        MutableArraySequence() : buff() {}
        MutableArraySequence(const T* items, size_t count) : buff(count) {
            for (size_t i = 0; i < count; i++) {
               buff.Set(i, items[i]);
            }
        }
        MutableArraySequence (const MutableArraySequence<T>& arr) : buff(arr.buff) {};
        T GetFirst() const override {
            if (buff.GetLength() == 0) {
                throw RangeError("buffer is empty");   
            }
            return buff.Get(0);
        };
        T GetLast() const override {
            if (buff.GetLength() == 0) {
                throw RangeError("buffer is empty");   
            }
            return buff.Get(buff.GetLength() - 1);
        };
        T Get(size_t index) const override {
            if (index >= buff.GetLength()) {
                throw RangeError("index is out of range");   
            }
            return buff.Get(index);
        };
        MutableArraySequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override {
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
        size_t GetLength() const override {
            return buff.GetLength();
        };
        void Append(const T& item)  override {
            buff.Resize(buff.GetLength() + 1);
            buff.Set(buff.GetLength() - 1, item);
        };
        void Prepend(const T& item) override {
            buff.Resize(buff.GetLength() + 1);
            for (int i = buff.GetLength() - 1; i > 0; i--) {
                buff.Set(i, buff.Get(i - 1));
            }
            buff.Set(0, item);
        };
        void InsertAt(const T& item, size_t index) override {
            if (index > buff.GetLength()) {
                throw RangeError("index is out of range");
            }
            buff.Resize(buff.GetLength() + 1);
            for (int i = buff.GetLength() - 1; i > index; i++) {
                buff.Set(i, buff.Get(i - 1));
            }
            buff.Set(index, item);
        };
        void Concat(Sequence<T>* list) override {
            if (list == nullptr) {
                throw InvalidArgumentError("argument is nullptr");
            }
            size_t this_size = this->GetLength();
            buff.Resize(buff.GetLength() + list->GetLength());
            for (size_t i = 0; i < list->GetLength(); i++) {
                buff.Set(i + this_size, list->Get(i));
            }
        };
};