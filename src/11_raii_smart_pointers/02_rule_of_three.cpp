// === Lesson: Copying a class that owns memory ================================
//
// If you don't write them, the compiler generates a copy constructor and a copy
// assignment operator that copy each member in turn. For an int or a std::string
// that's right. For a raw pointer it copies the address, not what it points to:
// a "shallow copy", leaving two objects that both think they own the same block.
//
//     struct Holder {
//         int* value = new int(0);
//         ~Holder() { delete value; }
//     };
//
//     Holder a;
//     Holder b = a;      // copies the pointer, not the int
//     *b.value = 5;      // a sees 5 too: one int, two owners
//                        // at the end of the scope both destructors delete it:
//                        // a double free, which the sanitizer reports
//
// A "deep copy" gives the new object its own block with the same contents. There
// are two copy operations to write, and they start from different places:
//
//     Holder(const Holder& other);             // copy constructor: Holder b = a;
//                                              // b is brand new and owns nothing yet
//     Holder& operator=(const Holder& other);  // copy assignment: b = a;
//                                              // b already exists and owns a block
//
// Copy assignment is the tricky one:
// - The old block has to be released, or it leaks.
// - `x = x` must work. Inside a member function, `this` points at the current
//   object, so `this == &other` tells you it's a self-assignment. Release your
//   block first and you'd then copy from memory you just freed.
// - If getting the new block can fail (throw), get it before giving up the old
//   one, so the object is never left pointing at freed memory.
// - Return *this, a reference to the object itself. `a = b = c` runs b = c first,
//   then assigns its result to a.
//
// The rule of three: a class that needs a hand-written destructor almost always
// needs a hand-written copy constructor and copy assignment too, because all
// three deal with the same resource. The alternatives are to forbid copying with
// `= delete`, or, better, to hold the resource in a member that already manages
// itself, like std::vector (that's module 12's rule of zero).
//
// Read more: https://www.learncpp.com/cpp-tutorial/shallow-vs-deep-copying/
//            https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/
//
// === Exercise: The rule of three =============================================
// Buffer owns a block of ints on the heap. Write the constructor (acquire the
// block) and destructor (release it), then copying.
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
