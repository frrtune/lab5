#pragma once

#include <cinttypes>
#include "../dynamic_array/dynamic_array.hpp"
#include "../sequence/sequence.hpp"

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
        DynamicArray<uint8_t> batches;
        size_t size;

        size_t get_current_batch_index(size_t index) const;
        size_t get_current_bit_index(size_t index) const;
        size_t get_batches_count(size_t index) const;
        void set_bit_in_batch(uint8_t& batch, size_t bit_index, bool value) const;
        bool get_bit_from_batch(uint8_t batch, size_t bit_index) const;
        void append_bit(bool value);
        bool get_bit_value(size_t index) const;
    public:
        BitSequence();
        BitSequence(const bool* items, size_t count);
        BitSequence(const BitSequence& other);

        bool GetBit(size_t index) const;
        Bit GetFirst() const override;
        Bit GetLast() const override;
        Bit Get(size_t index) const override;
        Sequence<Bit>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
        size_t GetLength() const override;
        Sequence<Bit>* Append(const Bit& item) const override;
        Sequence<Bit>* Prepend(const Bit& item) const override;
        Sequence<Bit>* InsertAt(const Bit& item, size_t index) const override;
        Sequence<Bit>* Concat(Sequence<Bit>* list) const override;
        BitSequence* And(const BitSequence& other) const;
        BitSequence* Or(const BitSequence& other) const;
        BitSequence* Xor(const BitSequence& other) const;
        BitSequence* Not() const;

        BitSequence operator&(const BitSequence& other) const;
        BitSequence operator|(const BitSequence& other) const;
        BitSequence operator~() const;
        bool operator[](size_t index) const;
};

BitSequence::BitSequence() : batches(), size(0) {}

BitSequence::BitSequence(const bool* items, size_t count) : size(count) {
    size_t batches_count = get_batches_count(count);
    batches = DynamicArray<uint8_t>(batches_count);
    for (size_t i = 0; i < count; i++) {
        size_t current_batch_index = get_current_batch_index(i);
        size_t current_bit_index = get_current_bit_index(i);
        uint8_t batch = batches.Get(current_batch_index);
        set_bit_in_batch(batch, current_bit_index, items[i]);
        batches.Set(current_batch_index, batch);
    }
}

BitSequence::BitSequence(const BitSequence& other) : batches(other.batches), size(other.size) {}

size_t BitSequence::get_current_batch_index(size_t index) const {
    return index / 8;
}

size_t BitSequence::get_current_bit_index(size_t index) const {
    return index % 8;
}

size_t BitSequence::get_batches_count(size_t count) const {
    return count / 8 + (count % 8 != 0);
}

void BitSequence::set_bit_in_batch(uint8_t& batch, size_t bit_index, bool value) const {
    if (value == 1) {
        batch = batch | (1 << bit_index);
    } else {
        batch = batch & (~(1 << bit_index));
    }
}

bool BitSequence::get_bit_from_batch(uint8_t batch, size_t bit_index) const {
    return (batch >> bit_index) & 1;
}

void BitSequence::append_bit(bool value) {
    size_t current_batch_index = get_current_batch_index(size);
    size_t current_bit_index = get_current_bit_index(size);
    if (current_bit_index == 0) {
        batches.Resize(batches.GetLength() + 1);
        batches.Set(batches.GetLength() - 1, 0);
    }
    uint8_t batch = batches.Get(current_batch_index);
    set_bit_in_batch(batch, current_bit_index, value);
    batches.Set(current_batch_index, batch);
    size++;
}

bool BitSequence::get_bit_value(size_t index) const {
    size_t current_batch_index = get_current_batch_index(index);
    size_t current_bit_index = get_current_bit_index(index);
    uint8_t batch = batches.Get(current_batch_index);
    return get_bit_from_batch(batch, current_bit_index);    
}

bool BitSequence::GetBit(size_t index) const {
    if (index >= size) {
        throw RangeError("index is out of range");
    }
    return get_bit_value(index);
}

Bit BitSequence::GetFirst() const {
    if (size == 0) {
        throw RangeError("buffer is empty");
    }
    return Bit(get_bit_value(0));
}

Bit BitSequence::GetLast() const {
    if (size == 0) {
        throw RangeError("buffer is empty");
    }
    return Bit(get_bit_value(size - 1));
}

Bit BitSequence::Get(size_t index) const {
    if (index >= size) {
        throw RangeError("index is out of range");
    }
    return Bit(get_bit_value(index));
}

Sequence<Bit>* BitSequence::GetSubsequence(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex || endIndex >= size) {
        throw InvalidArgumentError("start index must be less than end index");
    }
    BitSequence* result = new BitSequence();
    for (size_t i = startIndex; i <= endIndex; i++) {
        result->append_bit(get_bit_value(i));
    }
    return result;
}

size_t BitSequence::GetLength() const {
    return size;
}

Sequence<Bit>* BitSequence::Append(const Bit& item) const {
    BitSequence* result = new BitSequence(*this);
    result->append_bit(item.GetValue());
    return result;
}

Sequence<Bit>* BitSequence::Prepend(const Bit& item) const {
    BitSequence* result = new BitSequence();
    result->append_bit(item.GetValue());
    for (size_t i = 0; i < size; i++) {
        result->append_bit(get_bit_value(i));
    }
    return result;
}

Sequence<Bit>* BitSequence::InsertAt(const Bit& item, size_t index) const {
    if (index > size) {
        throw RangeError("index is out of range");
    }
    BitSequence* result = new BitSequence();
    for (size_t i = 0; i < index; i++) {
        result->append_bit(get_bit_value(i));
    }
    result->append_bit(item.GetValue());
    for (size_t i = index; i < size; i++) {
        result->append_bit(get_bit_value(i));
    }
    return result;
}

Sequence<Bit>* BitSequence::Concat(Sequence<Bit>* list) const {
    if (list == nullptr) {
        throw InvalidArgumentError("argument is nullptr");
    }
    BitSequence* result = new BitSequence(*this);
    for (size_t i = 0; i < list->GetLength(); i++) {
        result->append_bit(list->Get(i).GetValue());
    }
    return result;
}

BitSequence* BitSequence::And(const BitSequence& other) const {
    size_t new_size = 0;
    if (size < other.size) {
        new_size = size;
    } else {
        new_size = other.size;
    }
    BitSequence* result = new BitSequence();
    for (size_t i = 0; i < new_size; i++) {
        result->append_bit(get_bit_value(i) && other.get_bit_value(i));
    }
    return result;
} 

BitSequence* BitSequence::Or(const BitSequence& other) const {
    size_t new_size = 0;
    if (size < other.size) {
        new_size = size;
    } else {
        new_size = other.size;
    }
    BitSequence* result = new BitSequence();
    for (size_t i = 0; i < new_size; i++) {
        result->append_bit(get_bit_value(i) || other.get_bit_value(i));
    }
    return result;
}

BitSequence* BitSequence::Xor(const BitSequence& other) const {
    size_t new_size = 0;
    if (size < other.size) {
        new_size = size;
    } else {
        new_size = other.size;
    }
    BitSequence* result = new BitSequence();
    
    for (size_t i = 0; i < new_size; i++) {
        result->append_bit(get_bit_value(i) != other.get_bit_value(i));
    }
    return result;
}

BitSequence* BitSequence::Not() const {
    BitSequence* result = new BitSequence();
    for (size_t i = 0; i < size; i++) {
        result->append_bit(!get_bit_value(i));
    }
    return result;
}

BitSequence BitSequence::operator&(const BitSequence& other) const {
    size_t new_size = 0;
    if (size < other.size) {
        new_size = size;
    } else {
        new_size = other.size;
    }
    BitSequence result;
    for (size_t i = 0; i < new_size; i++) {
        result.append_bit(get_bit_value(i) && other.get_bit_value(i));
    }
    return result;
}

BitSequence BitSequence::operator|(const BitSequence& other) const {
    size_t new_size = 0;
    if (size < other.size) {
        new_size = size;
    } else {
        new_size = other.size;
    }
    BitSequence result;
    for (size_t i = 0; i < new_size; i++) {
        result.append_bit(get_bit_value(i) || other.get_bit_value(i));
    }
    return result;
}

BitSequence BitSequence::operator~() const {
    BitSequence result;
    for (size_t i = 0; i < size; i++) {
        result.append_bit(!get_bit_value(i));
    }
    return result;
}

bool BitSequence::operator[](size_t index) const {
    if (index >= size) {
        throw RangeError("index is out of range");
    }
    return get_bit_value(index);
}