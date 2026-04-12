#pragma once

#include "../sequence/sequence.hpp"
#include "../linked_list/linked_list.hpp"

template <typename T> class ListSequence : public Sequence <T> {
    private:
        LinkedList<T> buff;
    public:
        ListSequence() : buff() {}
        ListSequence(const T* items, size_t count) {
            for (size_t i = 0; i < count; i++) {
               buff.Append(items[i]);
            }
        }
        ListSequence (const ListSequence<T>& list) : buff(list.buff) {};
        T GetFirst() const override {
            if (buff.GetLength() == 0) {
                throw RangeError("buffer is empty");   
            }
            return buff.GetFirst();
        };
        T GetLast() const override {
            if (buff.GetLength() == 0) {
                throw RangeError("buffer is empty");   
            }
            return buff.GetLast();
        };
        T Get(size_t index) const override {
            if (index >= buff.GetLength()) {
                throw RangeError("index is out of range");   
            }
            return buff.Get(index);
        };
        ListSequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override {
            if (start_index >= buff.GetLength() || end_index >= buff.GetLength()) {
                throw RangeError("index is out of range");   
            }
            if (start_index > end_index) {
                throw InvalidArgumentError("start index must be less than end index");
            }
            ListSequence<T>* subsequence = new ListSequence<T>();
            for (size_t i = start_index; i <= end_index; i++) {
                subsequence->buff.Append(buff.Get(i));
            }
            return subsequence;
        };
        size_t GetLength() const override {
            return buff.GetLength();
        };
        ListSequence<T>* Append(const T& item) const override {
            ListSequence<T>* new_list = new ListSequence<T>(*this);
            new_list->buff.Append(item);
            return new_list;
        };
        ListSequence<T>* Prepend(const T& item) const override {
            ListSequence<T>* new_list = new ListSequence<T>();
            new_list->buff.Append(item);
            for (size_t i = 0; i < buff.GetLength(); i++) {
                new_list->buff.Append(buff.Get(i));
            }
            return new_list;
        };
        ListSequence<T>* InsertAt(const T& item, size_t index) const override {
            if (index > buff.GetLength()) {
                throw RangeError("index is out of range");
            }
            ListSequence<T>* new_list = new ListSequence<T>();
            for (size_t i = 0; i < index; i++) {
                new_list->buff.Append(buff.Get(i));
            }
            new_list->buff.Append(item);
            for (size_t i = index; i < buff.GetLength(); i++) {
                new_list->buff.Append(buff.Get(i));
            }
            return new_list;
        };
        ListSequence <T>* Concat(Sequence<T>* list) const override {
            if (list == nullptr) {
                throw InvalidArgumentError("argument is nullptr");
            }
            ListSequence<T>* new_list = new ListSequence<T>(*this);
            for (size_t i = 0; i < list->GetLength(); i++) {
                new_list->buff.Append(list->Get(i));
            }
            return new_list;
        };
};