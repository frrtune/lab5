#pragma once

#include <new>
#include "../exceptions/exceptions.hpp"

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
        template <typename U> friend class LinkedList;
};

template <typename T> class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;
        /**
         * @brief Удаление узлов связного списка циклом
         * 
         * @param head начальный узел
         */
        void delete_nodes(Node<T>* head) {
            while (head != nullptr) {
                Node<T>* next = head->next;
                delete head;
                head = next;
            } 
            tail = nullptr;
            size = 0;
        }
        void swap(LinkedList<T>& other) {
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(size, other.size);
        }
    public:
        /**
         * @brief Конструктор пустого списка
         * 
         */
        LinkedList() : head(nullptr), tail(nullptr), size(0) {};
        /**
         * @brief Конструктор связного списка с заданным размером
         * 
         * @param data данные
         * @param list_size размер
         */
        LinkedList(const T* data, size_t list_size) : LinkedList() {
            if (list_size == 0) {
                throw InvalidArgumentError("list size must be positive");
            }
            Node<T> *head = new Node<T>(data[0]);
            Node<T>* current = head;
            for (size_t i = 0; i < list_size; i++) {
                Append(data[i]);
            }
        }
        LinkedList(const LinkedList<T>& list) : LinkedList() {
            for (Node<T>* current = list.head; current != nullptr, current = current->next) {
                Append(current->node_data);
            }
        }
        ~LinkedList() {
            delete_nodes(head);
        }
        LinkedList<T>& operator=(const LinkedList<T>& list) {
            if (this != &list) {
                LinkedList<T> copy(list);
                swap(copy);
            }
            return *this;
        }
        T GetFirst() const {
            if (head == nullptr) {
                throw EmptyBufferError("list is empty");
            }
            return head->node_data;
        };
        T GetLast() const {
            if (tail == nullptr) {
                throw EmptyBufferError("list is empty");
            }
           return tail->node_data;
        };
        T Get(size_t index) const {
            if (head == nullptr) {
                throw EmptyBufferError("list is empty");
            }
           if (index >= GetLength()) {
                throw RangeError(index, GetLength());
            }
           Node<T>* current = head;
           for (size_t i = 0; i < index; i++) {
                current = current->next;
           }
           return current->node_data;
        }
        void Append(const T& item) {
            Node<T>* new_node = new Node<T>(item);
            if (tail == nullptr) {
                head = new_node;
            } else {
                tail->next = new_node;
            }
            tail = new_node;
            size++;
        };
        LinkedList<T>* GetSubList(size_t start_index, size_t end_index) const {
            if (start_index >= size) {
                throw RangeError(start_index, size);
            }
            if (end_index >= size) {
                throw RangeError(end_index, size);
            }
            if (start_index > end_index) {
                throw InvalidArgumentError("start index must be less than end index");
            }
            LinkedList<T>* sublist = new LinkedList<T>();
            try {
                Node<T>* current = head;
                for (size_t i = 0; i < start_index; i++) {
                    current = current->next;
                }
                for (size_t i = start_index; i <= end_index; i++) {
                    sublist->Append(current->node_data);
                    current = current->next;
                }
            } catch (...) {
                delete sublist;
                throw;
            }
            return sublist;
        };
        void Prepend(const T& item) {
            Node<T>* new_node = new Node<T>(item, head);
            head = new_node;
            if (tail == nullptr) {
                tail = new_node;
            }
            size++;
        };
        void InsertAt(const T& item, size_t index) {
            if (index > size) {
                throw RangeError(index, size);
            }
            if (index == 0) {
                Prepend(item);
                return;
            }
            if (index == size) {
                Append(item);
                return;
            }
            Node<T>* current = head;
            for (size_t i = 0; i < index - 1; i++) {
                current = current->next;
            }
            current->next = new Node<T>(item, current->next);
            size++;
        };
        LinkedList<T>* Concat(const LinkedList<T>* list) const {
            if (list == nullptr) {
                throw InvalidArgumentError("list is nullptr");
            }
            LinkedList<T>* new_list = new LinkedList<T>(*this);
            try {
                for (Node<T>* current = list->head; current != nullptr; current = current->next) {
                    new_list->Append(current->node_data);
                }
            } catch (...) {
                delete new_list;
                throw;
            }
            return new_list;
        };
};
