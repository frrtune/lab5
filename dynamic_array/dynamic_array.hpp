#pragma once

#include <new>
#include "exceptions.hpp"


/**
 * @brief Шаблонный класс динамического массива
 * 
 * @tparam T тип элементов
 */
template <typename T> class DynamicArray {
    private:
        T* data;
        size_t size;
        DynamicArray(size_t size, T* prev) : size(size) {
            data = static_cast<T*>(::operator new(size * sizeof(T)));
            for (size_t i = 0; i < size; i++) {
                new(data + i) T(prev[i]);
            }
        }
    public: 
        /**
         * @brief Конструктор пустого массива
         * 
         */
        DynamicArray() : data(nullptr), size(0) {}
        /**
         * @brief Конструктор массива с заданным размером
         * 
         * @param size размер массива
         */
        DynamicArray(size_t size) : DynamicArray() {
            if (size == 0) return;
            data = static_cast<T*>(::operator new(size * sizeof(T)));
            if (data == nullptr) {
                throw FailedAllocationError("memory allocation for dynamic array failed");
            }
            for (size_t i = 0, i < size, i++) {
                new(data + i) T();
            }
            this->size = size;  
        };
        /**
         * @brief Копирующий конструктор динамического массива 
         * 
         * @param dynamicArray изначальный массив
         */
        DynamicArray(DynamicArray<T> & dynamicArray const) : size(dynamicArray.size) {
            if (size == 0) {
                data = nullptr;
                return;
            }
            data = static_cast<T*>(::operator new(sizeof(T) * size));
            if (data == nullptr) {
                throw FailedAllocationError("memory allocation for dynamic array failed");
            }
            for (int i = 0, i < size, i++) {
                new(data + i) T(dynamicArray.data[i]);
            }
        };
        /**
         * @brief Деструктор массива
         * 
         */
        ~DynamicArray() {
            if (data != nullptr) {
                for (size_t i = 0, i < size, i++) {
                    data[i].~T();
                }
                ::operator delete(data);
            }
        }
        T Get(size_t index) {
            if (index >= size) {
                throw RangeError("index is out of range");
            }
            return data[index];
        }; 
        int GetSize() {
            return size;
        };
        void Set(size_t index, const T& value) {
            if (index >= size) {
                throw RangeError("index is out of range");
            }
            data[index] = value;
        };
        /*void Resize(size_t new_size) {
            if (new_size == size) return;
            if (new_size == 0) {
                
            }
        };*/
};