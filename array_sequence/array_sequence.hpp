#pragma once

#include "../sequence/sequence.hpp"
#include "../dynamic_array/dynamic_array.hpp"

template <typename T> class ArraySequence : public Sequence <T> {
    private:
        DynamicArray<T> buff;
        size_t size;
        ArraySequence(const DynamicArray<T>& arr, size_t param_size) : buff(arr), size(param_size) {}
        size_t calculate_capacity(size_t current_capacity, size_t new_size) {
            if (current_capacity >= new_size) return current_capacity;
            size_t new_capacity = 1;
            if (current_capacity != 0) {
                new_capacity = current_capacity;
            }
            while (new_capacity < new_size) {
                new_capacity *= 2;
            }
            return new_capacity;
        }
        DynamicArray<T> make_buff(const DynamicArray<T>& arr, size_t current_capacity, size_t new_size) {
            if (current_capacity >= new_size) return arr;
            size_t new_capacity = calculate_capacity(current_capacity, new_size);
            DynamicArray<T> new_buff{arr};
            new_buff.Resize(new_capacity);
            return new_buff;
        }

    public:
        ArraySequence() : buff(), size(0) {}
        ArraySequence(const T* items, size_t count) : buff(count), capacity(count){
            for (size_t i = 0; i < count; i++) {
               buff.Set(i, items[i]);
            }
        }
        ArraySequence (const ArraySequence<T>& arr) : buff(arr.buff) {};
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
        ArraySequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override {
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
            return new ArraySequence<T>(new_buff, new_size);
        };
        size_t GetLength() const override {
            return buff.GetLength();
        };
        ArraySequence<T>* Append(const T& item) const override {
            size_t new_size = size + 1;
            DynamicArray<T> new_buff = make_buff(buff, buff.GetLength(), new_size);
            new_buff.Set(size, item);
            return new ArraySequence<T>(new_buff, new_size);
        };
        ArraySequence<T>* Prepend(const T& item) const override {
            size_t new_size = size + 1;
            DynamicArray<T> new_buff = make_buff(buff, buff.GetLength(), new_size);
            for (size_t i = new_size; i > 1; i--) {
                new_buff[i] = new_buff[i - 1];
            }
            new_buff.Set(0, item);
            return new ArraySequence<T>(new_buff, new_size);
        };
        ArraySequence<T>* InsertAt(const T& item, size_t index) const override {
            if (index > buff.GetLength()) {
                throw RangeError("index is out of range");
            }
            size_t new_size = size + 1;
            DynamicArray<T> new_buff = make_buff(buff, buff.GetLength(), new_size);
             for (size_t i = size; i > index; i--) {
                new_buff.Set(i, buff.Get(i - 1));
            }
            new_buff.Set(index, item);
            return new ArraySequence<T>(new_buff, new_size);
        };
        ArraySequence <T>* Concat(Sequence<T>* list) const override {
            if (list == nullptr) {
                throw InvalidArgumentError("argument is nullptr");
            }
            DynamicArray<T> new_buff;
            new_buff.Resize(buff.GetLength() + list->GetLength());
            for (size_t i = 0; i < buff.GetLength(); i++) {
                new_buff.Set(i, buff.Get(i));
            }
            for (size_t i = 0; i < list->GetLength(); i++) {
                new_buff.Set(i + buff.GetLength(), list->Get(i));
            }
            return new ArraySequence<T>(new_buff);
        };
};