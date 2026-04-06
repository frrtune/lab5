#pragma once

#include "../sequence/sequence.hpp"
#include "../dynamic_array/dynamic_array.hpp"

template <typename T> class ArraySequence : public Sequence <T> {
    private:
        DynamicArray<T*> buff;
        ArraySequence(DynamicArray<T>* arr) : buff(arr) {};
    public:
        /*ArraySequence() : buff(new DynamicArray<T>()) {}
        ArraySequence(const T* data, int size) : buff(new DynamicArray<T>(size)) {
            for (int i = 0, i < size, i++) {
                
            }
        }*/

};