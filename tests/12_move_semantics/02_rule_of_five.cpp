#include "grader.hpp"
#include "12_move_semantics/02_rule_of_five.cpp"

#include <vector>

TEST("move constructor: takes the block without allocating") {
    Buffer source(3);
    source.set(0, 7);
    const int *block = source.data();
    Buffer moved(std::move(source));
    CHECK(moved.data() == block, "the new buffer should own the very same block");
    CHECK_EQ(moved.size(), 3);
    CHECK_EQ(moved.get(0), 7);
    CHECK_EQ(allocations, 1);
}

TEST("move constructor: leaves the source empty") {
    Buffer source(3);
    Buffer moved(std::move(source));
    CHECK_EQ(source.size(), 0);
    CHECK(source.data() == nullptr, "a moved-from buffer should hold a null pointer");
}

TEST("move constructor: is noexcept") {
    Buffer source(1);
    Buffer moved(std::move(source));
    CHECK(std::is_nothrow_move_constructible_v<Buffer>, "mark the move constructor noexcept");
}

TEST("move constructor: no double release") {
    {
        Buffer source(2);
        Buffer moved(std::move(source));
        CHECK_EQ(live_blocks, 1);
    }
    CHECK_EQ(live_blocks, 0);
}

TEST("move assignment: takes the block and frees the old one") {
    Buffer source(3);
    source.set(2, 9);
    const int *block = source.data();
    Buffer target(10);
    target = std::move(source);
    CHECK(target.data() == block, "the target should now own source's block");
    CHECK_EQ(target.size(), 3);
    CHECK_EQ(target.get(2), 9);
    CHECK_EQ(source.size(), 0);
    CHECK(source.data() == nullptr, "a moved-from buffer should hold a null pointer");
    CHECK_EQ(live_blocks, 1);
    CHECK_EQ(allocations, 2);
}

TEST("move assignment: is noexcept and returns *this") {
    Buffer source(1);
    Buffer target(1);
    Buffer &result = (target = std::move(source));
    CHECK(&result == &target, "operator= should return *this");
    CHECK(std::is_nothrow_move_assignable_v<Buffer>, "mark the move assignment noexcept");
}

TEST("a moved-from buffer can be reused") {
    Buffer a(2);
    Buffer b(std::move(a));
    a = Buffer(4);
    a.set(3, 1);
    CHECK_EQ(a.size(), 4);
    CHECK_EQ(a.get(3), 1);
    Buffer empty_copy(std::move(b));
    CHECK_EQ(b.size(), 0);
}

TEST("returning a Buffer allocates nothing extra") {
    auto make = [] {
        Buffer local(5);
        local.set(0, 1);
        return local;
    };
    Buffer result(1);
    result = make();
    CHECK_EQ(result.size(), 5);
    CHECK_EQ(result.get(0), 1);
    CHECK_EQ(allocations, 2);
    CHECK_EQ(live_blocks, 1);
}

TEST("std::swap moves instead of copying") {
    Buffer a(1);
    Buffer b(2);
    a.set(0, 10);
    std::swap(a, b);
    CHECK_EQ(a.size(), 2);
    CHECK_EQ(b.size(), 1);
    CHECK_EQ(b.get(0), 10);
    CHECK_EQ(allocations, 2);
}

TEST("vector growth moves buffers (needs noexcept)") {
    std::vector<Buffer> buffers;
    for (int i = 0; i < 5; ++i) buffers.push_back(Buffer(4));
    // One allocation per buffer; growing the vector must not copy any of them.
    CHECK_EQ(allocations, 5);
    CHECK_EQ(live_blocks, 5);
}
