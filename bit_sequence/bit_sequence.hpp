#pragma once

#include <utility>
#include "../exceptions.hpp"
#include "../sequence/sequence.hpp"
#include "../array_sequence/array_sequence.hpp"

class Bit {
    private:
        bool value;
    public:
        Bit() : value(false) {};
        Bit(bool v) : value(v) {};
        bool GetValue() const {
            return value;
        }
        void SetValue(bool v) {
            value = v;
        }
};

class BitSequence : public Sequence<Bit> {
    private:
        ArraySequence<Bit> bit_sequence;
        /**
         * @brief Дополнение нулями слева
         * 
         * @param new_length новая длина (до которой нужно дополнить)
         * @return BitSequence* 
         */
        BitSequence* add_zeros(size_t new_length) const {
            if (new_length < GetLength()) {
                throw InvalidArgumentError("current length must be less or equal to new one");
            }
            size_t zeros_count = new_length - GetLength();
            BitSequence* result = new BitSequence();
            for (size_t i = 0; i < zeros_count; i++) {
                result->Append(Bit(false));
            }
            for (size_t i = 0; i < GetLength(); i++) {
                result->Append(Get(i));
            }
            return result;
        }
        /**
         * @brief Выравнивает длины двух последовательностей по большей из них, добавляя нули слева
         * 
         * @param other 
         * @return std::pair<BitSequence*, BitSequence*> 
         */
        std::pair<BitSequence*, BitSequence*> align(const BitSequence& other) const {
            size_t max_length = 0;  
            if (GetLength() > other.GetLength()) {
                max_length = GetLength();
            } else {
                max_length =other.GetLength();
            }
            BitSequence* aligned_this = this->add_zeros(max_length);
            BitSequence* aligned_other = other.add_zeros(max_length);
            return {aligned_this, aligned_other};
        };
    public:
        BitSequence() : bit_sequence() {}
        BitSequence(const Bit* items, size_t count) {
            for (size_t i = 0; i < count; i++) {
                bit_sequence.Append(items[i]);
            }
        }
        BitSequence(const bool* items, size_t count) {
            for (size_t i = 0; i < count; i++) {
                bit_sequence.Append(Bit(items[i]));
            }
        }
        BitSequence(const BitSequence& other) : bit_sequence(other.bit_sequence) {}
        Bit GetFirst() const override {
            return bit_sequence.GetFirst();
        }
        Bit GetLast() const override {
            return bit_sequence.GetLast();
        }
        Bit Get(size_t index) const override {
            return bit_sequence.Get(index);
        }
        Sequence<Bit>* GetSubsequence(size_t startIndex, size_t endIndex) const override {
            return bit_sequence.GetSubsequence(startIndex, endIndex);
        }
        size_t GetLength() const override {
            return bit_sequence.GetLength();
            }
        Sequence<Bit>* Append(const Bit& item) const override {
            return bit_sequence.Append(item);
        }
        Sequence<Bit>* Prepend(const Bit& item) const override {
            return bit_sequence.Prepend(item);
        }
        Sequence<Bit>* InsertAt(const Bit& item, size_t index) const override {
            return bit_sequence.InsertAt(item, index);
        }
        Sequence<Bit>* Concat(Sequence<Bit>* list) const override {
            return bit_sequence.Concat(list);
        }
        BitSequence* And(const BitSequence& other) const {
            auto [aligned_this, aligned_other] = align(other);
            BitSequence* result = new BitSequence();
            for (size_t i = 0; i < aligned_this->GetLength(); i++) {
                bool value = aligned_this->Get(i).GetValue() && aligned_other->Get(i).GetValue();
                result->Append(Bit(value));
            }
            delete aligned_this;
            delete aligned_other;
            return result;
        }
        BitSequence* Or(const BitSequence& other) const {
            auto [aligned_this, aligned_other] = align(other);
            BitSequence* result = new BitSequence();
            for (size_t i = 0; i < aligned_this->GetLength(); i++) {
                bool value = aligned_this->Get(i).GetValue() || aligned_other->Get(i).GetValue();
                result->Append(Bit(value));
            }
            delete aligned_this;
            delete aligned_other;
            return result;
        }
        BitSequence* Xor(const BitSequence& other) const {
            auto [aligned_this, aligned_other] = align(other);
            BitSequence* result = new BitSequence();
            for (size_t i = 0; i < aligned_this->GetLength(); i++) {
                bool value = aligned_this->Get(i).GetValue() != aligned_other->Get(i).GetValue();
                result->Append(Bit(value));
            }
            delete aligned_this;
            delete aligned_other;
            return result;
        }
        BitSequence* Not() const {
            BitSequence* result = new BitSequence();
            for (size_t i = 0; i < GetLength(); i++) {
                result->Append(Bit(!Get(i).GetValue()));
            }
            return result;
        }
};