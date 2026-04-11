#pragma once

#include "../sequence/sequence.hpp"
#include "../dynamic_array/dynamic_array.hpp"

template <typename T> class ArraySequence : public Sequence <T> {
    private:
        DynamicArray<T> buff;
        ArraySequence(const DynamicArray<T>& arr) : buff(arr) {};
    public:
        ArraySequence() : buff() {}
        ArraySequence(const T* data, size_t size) : buff(size) {
            for (size_t i = 0; i < size; i++) {
               buff.Set(i, data[i]);
            }
        }
};