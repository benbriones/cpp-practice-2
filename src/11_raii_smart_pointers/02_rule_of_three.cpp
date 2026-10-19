// Exercise: The rule of three
// Buffer owns a block of ints on the heap. Write the constructor (acquire the
// block) and destructor (release it), then copying. The compiler's default copy
// would copy only the pointer, leaving two Buffers that release the same block.
//
// Rule of three: a class that needs a destructor almost always needs a copy
// constructor and a copy assignment operator too.
//
// Use allocate() and release() instead of new[]/delete[], so the tests can
// count live blocks and catch leaks.
//
// ./grade 11_raii_smart_pointers/02_rule_of_three

#include <cstddef>

// Blocks handed out by allocate() and not yet passed to release().
inline int live_blocks = 0;

// A block of `size` zeros.
int* allocate(int size) {
    ++live_blocks;
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
    // A buffer of `size` zeros, in a block from allocate().
    explicit Buffer(int size) {
        throw "TODO";
    }

    // Release the block.
    ~Buffer() {
        // TODO
    }

    // A deep copy: a new block with the same contents.
    Buffer(const Buffer& other) {
        throw "TODO";
    }

    // Make this buffer an independent copy of other and return *this.
    // Don't leak the block this buffer held before, and survive `b = b`.
    Buffer& operator=(const Buffer& other) {
        throw "TODO";
    }

    int size() const { return size_; }
    int get(int index) const { return data_[index]; }
    void set(int index, int value) { data_[index] = value; }

private:
    int size_;
    int* data_;
};
