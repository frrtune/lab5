#pragma once

#include <new>
#include "../exceptions/exceptions.hpp"


/**
 * @brief Шаблонный класс динамического массива
 * 
 * @tparam T тип элементов
 */
template <typename T> class DynamicArray {
    private:
        T* data;
        size_t size;
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
            for (size_t i = 0; i < size; i++) {
                new(data + i) T();
            }
            this->size = size;  
        };
        DynamicArray(const T* items, size_t count) : size(count) {
            if (count == 0) {
                data = nullptr;
                return;
            }
            data = static_cast<T*>(::operator new(count * sizeof(T)));
            for (size_t i = 0; i < count; i++) {
                new(data + i) T(items[i]);
            }
        };
        /**
         * @brief Копирующий конструктор динамического массива 
         * 
         * @param dynamicArray изначальный массив
         */
        DynamicArray(const DynamicArray<T>& dynamicArray) : size(dynamicArray.size) {
            if (size == 0) {
                data = nullptr;
                return;
            }
            data = static_cast<T*>(::operator new(sizeof(T) * size));
            if (data == nullptr) {
                throw FailedAllocationError("memory allocation for dynamic array failed");
            }
            for (size_t i = 0; i < size; i++) {
                new(data + i) T(dynamicArray.data[i]);
            }
        };
        /**
         * @brief Деструктор массива
         * 
         */
        ~DynamicArray() {
            if (data != nullptr) {
                for (size_t i = 0; i < size; i++) {
                    data[i].~T();
                }
                ::operator delete(data);
            }
        }
        T Get(size_t index) const {
            if (index >= size) {
                throw RangeError(index, size);
            }
            return data[index];
        }; 
        size_t GetLength() const {
            return size;
        };
        void Set(size_t index, const T& value) {
            if (index >= size) {
                throw RangeError(index, size);
            }
            data[index] = value;
        };
        void Resize(size_t new_size) {
            if (new_size == size) return;
            T* new_data = new T[new_size];
            size_t min_size = 0;
            if (new_size < size) {
                min_size = new_size;
            } else {
                min_size = size;
            }
            for (size_t i = 0; i < min_size; i++) {
                new_data[i] = data[i]; 
            }
            delete[] data;
            data = new_data;
            size = new_size;
            }
};