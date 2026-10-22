#include "grader.hpp"
#include "11_raii_smart_pointers/02_rule_of_three.cpp"

TEST("constructor: a zero-filled block of the right size") {
    Buffer b(3);
    CHECK_EQ(b.size(), 3);
    CHECK_EQ(b.get(0), 0);
    CHECK_EQ(b.get(2), 0);
    CHECK_EQ(live_blocks, 1);
}

TEST("destructor: releases the block") {
    {
        Buffer b(4);
    }
    CHECK_EQ(live_blocks, 0);
}

TEST("copy constructor: same size and contents") {
    Buffer original(3);
    original.set(0, 7);
    original.set(2, 9);
    Buffer copy = original;
    CHECK_EQ(copy.size(), 3);
    CHECK_EQ(copy.get(0), 7);
    CHECK_EQ(copy.get(2), 9);
}

TEST("copy constructor: the copy is independent") {
    Buffer original(2);
    original.set(0, 7);
    Buffer copy = original;
    copy.set(0, 99);
    CHECK_EQ(original.get(0), 7);
    CHECK_EQ(copy.get(0), 99);
}

TEST("copy constructor: each buffer owns its own block") {
    {
        Buffer original(2);
        Buffer copy = original;
        CHECK_EQ(live_blocks, 2);
    }
    CHECK_EQ(live_blocks, 0);
}

TEST("copy assignment: copies size and contents") {
    Buffer source(3);
    source.set(1, 5);
    Buffer target(10);
    target = source;
    CHECK_EQ(target.size(), 3);
    CHECK_EQ(target.get(1), 5);
}

TEST("copy assignment: the target is independent afterwards") {
    Buffer source(2);
    Buffer target(2);
    target = source;
    target.set(0, 42);
    CHECK_EQ(source.get(0), 0);
}

TEST("copy assignment: releases the target's old block") {
    Buffer source(2);
    Buffer target(5);
    target = source;
    CHECK_EQ(live_blocks, 2);
}

TEST("copy assignment: self-assignment is safe") {
    Buffer b(3);
    b.set(1, 5);
    Buffer &same = b;
    b = same;
    CHECK_EQ(b.size(), 3);
    CHECK_EQ(b.get(1), 5);
    CHECK_EQ(live_blocks, 1);
}

TEST("copy assignment: returns *this, so a = b = c works") {
    Buffer a(1), b(1), c(2);
    c.set(1, 8);
    a = b = c;
    CHECK_EQ(a.size(), 2);
    CHECK_EQ(a.get(1), 8);
    CHECK_EQ(b.get(1), 8);
}

TEST("no leaks after lots of copying") {
    {
        Buffer a(4);
        Buffer b = a;
        Buffer c(1);
        c = b;
        b = c;
        Buffer d = c;
        a = d;
    }
    CHECK_EQ(live_blocks, 0);
}
