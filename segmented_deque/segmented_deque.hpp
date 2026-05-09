#include "../sequence/sequence.hpp"
#include "../exceptions/exceptions.hpp"

template <typename T>
class SegmentedDeque : public Sequence <T> {
    private:
        static const size_t batch_size = 16;
        struct Batch {
            T data[batch_size];
            size_t batch_number = 0;
            size_t elem_count = 0;
            Batch* next = nullptr;
            Batch* prev = nullptr;
        }
        Batch* head = nullptr;
        Batch* tail = nullptr;
        Batch* init_batch() {
            return new Batch();
        };
        void delete_batch(Batch* batch) {
            for(size_t i = 0; i < batch.elem_count; i++) {
                batch->data[i].~T();
            }
            delete batch;
        };
    public:
        SegmentedDeque();
};