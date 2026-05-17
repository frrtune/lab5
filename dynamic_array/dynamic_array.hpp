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
        DynamicArray(size_t size) : data(nullptr), size(size) {
            if (size == 0) return;
            data = new T[size];
        };
        DynamicArray(const T* items, size_t count) : data(nullptr), size(count) {
            if (count == 0) return;
            data = new T[count];
            for (size_t i = 0; i < count; i++) {
                data[i] = items[i];
            }
        };
        /**
         * @brief Копирующий конструктор динамического массива 
         * 
         * @param dynamicArray изначальный массив
         */
        DynamicArray(const DynamicArray<T>& dynamicArray) : data(nullptr), size(dynamicArray.size) {
            if (size == 0) {
                data = nullptr;
                return;
            }
            data = new T[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = dynamicArray.data[i];
            }
        };
        /**
         * @brief Деструктор массива
         * 
         */
        ~DynamicArray() {
            delete[] data;
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
            if (new_size == 0) {
                delete[] data;
                data = nullptr;
                size = 0;
                return;
            }
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