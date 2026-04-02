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
        size_t capacity;
        /**
         * @brief Выделяет память для динамического массива без инициализации
         * 
         * @param cap вместимость массива
         */
        void memory_allocate(size_t cap) {
            if (data != nullptr) {
                throw std::logic_error("memory is already allocated");
            }
            if (cap == 0) {
                size = 0;
                capacity = 0;
                return;
            }
            data = static_cast<T*>(::operator new(cap * sizeof(T)));
            capacity = cap;
            size = 0;
        }
    public: 
        /**
         * @brief Конструктор пустого массива
         * 
         */
        DynamicArray() : data(nullptr), size(0), capacity(0) {}
        /**
         * @brief Конструктор массива с заданной вместимостью
         * 
         * @param cap вместимость массива
         */
        DynamicArray(size_t cap) : data(nullptr), size(0), capacity(0) {
            memory_allocate(cap);
        }
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