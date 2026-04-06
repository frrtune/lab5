#pragma once

#include <stdexcept>
#include <new>

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
            for (size_t i = 0; i < size; i++) {
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
                for (size_t i = 0; i < size; i++) {
                    data[i].~T();
                }
                ::operator delete(data);
            }
        }
};