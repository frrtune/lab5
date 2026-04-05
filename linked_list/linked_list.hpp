#pragma once

#include <stdexcept>
#include <new>

/**
 * @brief Узел (ячейка) связного списка
 * 
 * @tparam T тип элемента узла
 */
template <typename T> class Node {
    private:
        T node_data;
        Node<T>* next;
    public:
        Node(const T& node_data, Node<T>* next = nullptr) : node_data(node_data), next(next) {};
};

template <typename T> class LinkedList {
    private:
        Node<T>* head;
        size_t size;
        /**
         * @brief Конструктор связного списка
         * 
         * @param head начальный узел
         * @param size размер связного списка
         */
        LinkedList (Node<T>* head, size_t size) : head(head), size(size) {};
        /**
         * @brief Удаление узлов связного списка циклом
         * 
         * @param head начальный узел
         */
        void delete_nodes(Node<T>* head) {
            while (head != nullptr) {
                Node<T>* next = head->next;
                head->~Node();
                ::operator delete(head);
                head = next;
            }   
        }
    public:
        /**
         * @brief Конструктор пустого списка
         * 
         */
        LinkedList() : head(nullptr), size(0) {};
        /**
         * @brief Конструктор связного списка с заданным размером
         * 
         * @param data данные
         * @param list_size размер
         */
        LinkedList (const T* data, size_t list_size) : head(nullptr), size(0) {
            if (list_size == 0) return;
            head = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
            new(head) Node<T>(data[0]);
            size = 1;
            Node<T>* current = head;
            for (size_t i = 1; i < list_size; i++) {
                current->next = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
                new(current->next) Node<T>(data[i]);
                current = current->next;
                size++;
            }
        }
        ~LinkedList() {
            delete_nodes(head);
        }
};