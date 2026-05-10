#include "../sequence/sequence.hpp"
#include "../exceptions/exceptions.hpp"

template <typename T>
class SegmentedDeque : public Sequence <T> {
    private:
        static const size_t batch_size = 16;
        struct Batch {
            T data[batch_size];
            size_t first_elem = 0;
            size_t elem_count = 0;
            Batch* next = nullptr;
            Batch* prev = nullptr;
        };
        size_t total_size = 0;
        Batch* head = nullptr;
        Batch* tail = nullptr;
        Batch* init_batch() {
            return new Batch();
        };
        void delete_batch(Batch* batch) {
            for(size_t i = 0; i < batch->elem_count; i++) {
                batch->data[i].~T();
            }
            delete batch;
        };
    public:
        SegmentedDeque();
        SegmentedDeque(const SegmentedDeque<T>& other);
        ~SegmentedDeque();
        T GetFirst() const override;
        T GetLast() const override;
        T Get(size_t index) const override;
        SegmentedDeque<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
        size_t GetLength() const override;
        SegmentedDeque<T>* Append(const T& item) const override;
        SegmentedDeque<T>* Prepend(const T& item) const override;
        SegmentedDeque<T>* Concat(Sequence <T> *list) const override;
        SegmentedDeque<T>* InsertAt(const T& item, size_t index) const override;

        template <typename F> 
        SegmentedDeque<F>* Map(F (*func)(const T&)) const;
        T Reduce(T (*func)(const T& x1, const T& x2), const T& c) const;
        SegmentedDeque<T>* Where(bool (*func)(const T&)) const;
};