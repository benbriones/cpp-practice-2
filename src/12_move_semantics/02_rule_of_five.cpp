// Exercise: The rule of five
// Buffer is back, with its destructor and copy operations already written.
// Copying allocates a new block; moving should just take the pointer. Add the
// move constructor and move assignment operator.
//
// A moved-from Buffer must be empty (size 0, null data) so its destructor
// releases nothing. Mark both move operations noexcept: std::vector only moves
// elements while growing if the move constructor promises not to throw;
// otherwise it copies them.
//
// ./grade 12_move_semantics/02_rule_of_five

#include <cstddef>
#include <utility>

// Blocks allocated and not yet released, and every allocate() call ever made.
inline int live_blocks = 0;
inline int allocations = 0;

int* allocate(int size) {
    ++live_blocks;
    ++allocations;
    return new int[static_cast<std::size_t>(size)]();
}

void release(int* block) {
    if (block != nullptr) {
        --live_blocks;
        delete[] block;
    }
}

class Buffer {
public:
    explicit Buffer(int size) : size_(size), data_(allocate(size)) {}

    ~Buffer() { release(data_); }

    Buffer(const Buffer& other) : size_(other.size_), data_(allocate(other.size_)) {
        for (int i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            int* fresh = allocate(other.size_);
            for (int i = 0; i < other.size_; ++i) fresh[i] = other.data_[i];
            release(data_);
            data_ = fresh;
            size_ = other.size_;
        }
        return *this;
    }

    // Take other's block; leave other empty.
    Buffer(Buffer&& other) {
        throw "TODO";
    }

    // Release this buffer's block, take other's, leave other empty, return *this.
    Buffer& operator=(Buffer&& other) {
        throw "TODO";
    }

    int size() const { return size_; }
    const int* data() const { return data_; }
    int get(int index) const { return data_[index]; }
    void set(int index, int value) { data_[index] = value; }

private:
    int size_;
    int* data_;
};
