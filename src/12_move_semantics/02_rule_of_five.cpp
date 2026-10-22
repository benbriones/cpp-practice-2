// === Lesson: The rule of five ================================================
//
// A class that owns a resource directly (a raw pointer, a file handle, a socket)
// has five special members to think about:
//
//     ~T();                                // destructor
//     T(const T& other);                   // copy constructor
//     T& operator=(const T& other);        // copy assignment
//     T(T&& other) noexcept;               // move constructor
//     T& operator=(T&& other) noexcept;    // move assignment
//
// The rule of five: if you write any of them, think about all five. One trap
// makes it a rule: once you declare a destructor or a copy operation, the
// compiler stops generating the move operations. Nothing breaks visibly. An
// rvalue can still bind to const T&, so every "move" quietly becomes a copy.
//
// Moving a resource handle means taking the source's handle, then putting the
// source into an "owns nothing" state its destructor can run on safely. Without
// that second step, two objects hold the same handle and both release it.
// std::exchange from <utility> does "read the old value, store a new one" in one
// step:
//
//     int ticket = 41;
//     int served = std::exchange(ticket, ticket + 1);   // served 41, ticket 42
//
// Move assignment differs from the move constructor the same way copy assignment
// differs from the copy constructor: the target already owns something, which
// has to be released, and `a = std::move(a)` mustn't destroy a's own resource.
//
// Why noexcept matters: when a std::vector grows, it moves its elements into the
// new storage only if the move constructor is noexcept. If a move could throw
// halfway through, the vector couldn't undo it, so it copies instead. Plenty of
// library code relies on cheap moves too. std::swap, for example, is three moves:
//
//     T tmp = std::move(a);
//     a = std::move(b);
//     b = std::move(tmp);
//
// Check your class with the type traits from <type_traits>:
//
//     static_assert(std::is_nothrow_move_constructible_v<MyType>);
//
// Read more: https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/
//            https://www.learncpp.com/cpp-tutorial/stdmove_if_noexcept/
//
// === Exercise: The rule of five ==============================================
// Buffer is back, with its destructor and copy operations already written.
// Copying allocates a new block; moving should just take the pointer. Add the
// move constructor and move assignment operator, both noexcept.
//
// A moved-from Buffer must be empty (size 0, null data) so its destructor
// releases nothing.
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

    // Move other's block into the new buffer without allocating anything.
    // Take other's size and data pointer as they are.
    // Leave other empty: size 0 and a null data pointer.
    //
    // Example:
    //   Buffer source(3);
    //   source.set(0, 7);
    //   Buffer moved(std::move(source));
    //   // moved.size() is 3, moved.get(0) is 7, moved.data() is source's old block.
    //   // source.size() is 0, source.data() is nullptr; allocations is still 1.
    //
    // An empty source releases nothing in its destructor, so the block is freed once.
    Buffer(Buffer&& other) {
        throw "TODO";
    }

    // Move other's block into this existing buffer, then return *this.
    // Release this buffer's old block first, then take other's size and pointer.
    // Leave other empty: size 0 and a null data pointer.
    //
    // Example:
    //   Buffer source(3);
    //   Buffer target(10);
    //   target = std::move(source);
    //   // target.size() is 3 and owns source's old block; target's old block is freed.
    //   // source.size() is 0, source.data() is nullptr; live_blocks is 1.
    //
    // Unlike the move constructor, the target already owns a block that must be released.
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
