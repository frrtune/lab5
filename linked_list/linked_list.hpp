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
        size_t GetLength() const {
            auto current = head;
            size_t size = 0;
            while (current != nullptr) {
                size++;
                current = current -> next;
            }
            return size;
        };
        /**
         * @brief Конструктор пустого списка
         * 
         */
        LinkedList() : head(nullptr) {};
        /**
         * @brief Конструктор связного списка с заданным размером
         * 
         * @param data данные
         * @param list_size размер
         */
        LinkedList(const T* data, size_t list_size) : head(nullptr) {
            if (list_size == 0) {
                throw InvalidArgumentError("list size must be positive");
            }
            Node<T> *head = new Node<T>(data[0]);
            Node<T>* current = head;
            for (size_t i = 1; i < list_size; i++) {
                current->next = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
                new(current->next) Node<T>(data[i]);
                current = current->next;
            }
        }
        LinkedList(const LinkedList<T>& list) : head(nullptr) {
            if (list.head == nullptr) {
                throw InvalidArgumentError("list is nullptr");
            }
            head = static_cast<Node<T>*>(::operator new(sizeof(Node<T>)));
            new(head) Node<T>(list.head->node_data);
            Node<T>* this_current = head;
            Node<T>* other_current = list.head->next;
            while (other_current != nullptr) {
                Node<T> *this_current->next = new Node<T>(other_current->node_data);
                this_current = this_current->next;
                other_current = other_current->next;
            }
        }
        ~LinkedList() {
            delete_nodes(head);
        }
        T GetFirst() const {
            if (head == nullptr) {
                throw RangeError("list is empty");
            }
            return head->node_data;
        };
        T GetLast() const {
            if (head == nullptr) {
                throw RangeError("list is empty");
            }
           Node<T>* current = head;
           while (current->next != nullptr) {
                current = current->next;
           }
           return current->node_data;
        };
        T Get(size_t index) const {
            if (head == nullptr) {
                throw RangeError("list is empty");
            }
           if (index >= GetLength()) {
                throw RangeError("index is out of range");
            }
           Node<T>* current = head;
           for (size_t i = 0; i < index; i++) {
                current = current->next;
           }
           return current->node_data;
        }
        void Append(const T& item) {
            Node<T> *new_node = new Node<T>(item);
            if (head == nullptr) {
                head = new_node;
            } else {
                Node<T>* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = new_node;
            }
        };
        LinkedList<T>* GetSubList(size_t start_index, size_t end_index) {
            size_t length = GetLength();
            if (start_index >= length || end_index >= length) {
                throw RangeError("index is out of range");
            }
            if (start_index > end_index) {
                throw InvalidArgumentError("start index must be less than end index");
            }
            LinkedList<T>* sublist = new LinkedList<T>();
            Node<T>* current = head;
            for (size_t i = 0; i < start_index; i++) {
                current = current->next;
            }
            for (size_t i = start_index; i <= end_index; i++) {
                sublist->Append(current->node_data);
                current = current->next;    
            }
            return sublist;
        };
        void Prepend(const T& item) {
            Node<T> *new_node = new Node<T>(item);
            new_node->next = head;
            head = new_node;
        };
        void InsertAt(T item, size_t index) {
            size_t length = GetLength();
            if (index > length) {
                throw RangeError("index is out of range");
            }
            if (index == 0) {
                Prepend(item);
                return;
            }
            if (index == length) {
                Append(item);
                return;
            }
            Node<T>* current = head;
            for (size_t i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node<T> *new_node = new Node<T>(item);
            new_node->next = current->next;
            current->next = new_node;
        };
        LinkedList<T>* Concat(LinkedList<T> *list) {
            if (list == nullptr) {
                throw InvalidArgumentError("list is nullptr");
            }
            LinkedList<T>* new_list = new LinkedList<T>();
            Node<T>* current = head;
            while (current != nullptr) {
                new_list->Append(current->node_data);
                current = current->next;
            }
            current = list->head;
            while (current != nullptr) {
                new_list->Append(current->node_data);
                current = current->next;
            }
            return new_list;
        }; 
};