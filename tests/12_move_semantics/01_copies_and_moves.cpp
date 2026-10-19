#include "grader.hpp"
#include "12_move_semantics/01_copies_and_moves.cpp"

TEST("copy constructor: copies the text, counts one copy") {
    Message original("hello");
    Message copy(original);
    CHECK_EQ(copy.text(), "hello");
    CHECK_EQ(original.text(), "hello");
    CHECK_EQ(copies, 1);
    CHECK_EQ(moves, 0);
}

TEST("move constructor: takes the text, counts one move") {
    Message original("hello");
    Message moved(std::move(original));
    CHECK_EQ(moved.text(), "hello");
    CHECK_EQ(moves, 1);
    CHECK_EQ(copies, 0);
}

TEST("move constructor: leaves the source empty") {
    Message original("a message long enough to live on the heap");
    Message moved(std::move(original));
    CHECK_EQ(original.text(), "");
}

TEST("move constructor: is noexcept") {
    Message original("hi");
    Message moved(std::move(original));
    CHECK(std::is_nothrow_move_constructible_v<Message>,
          "mark the move constructor noexcept");
}

TEST("copy assignment: copies the text, counts one copy") {
    Message source("source");
    Message target("target");
    target = source;
    CHECK_EQ(target.text(), "source");
    CHECK_EQ(source.text(), "source");
    CHECK_EQ(copies, 1);
}

TEST("copy assignment: returns *this, and a = a is safe") {
    Message a("same");
    Message& alias = a;
    Message& result = (a = alias);
    CHECK(&result == &a, "operator= should return *this");
    CHECK_EQ(a.text(), "same");
}

TEST("move assignment: takes the text, empties the source") {
    Message source("source");
    Message target("target");
    target = std::move(source);
    CHECK_EQ(target.text(), "source");
    CHECK_EQ(source.text(), "");
    CHECK_EQ(moves, 1);
    CHECK_EQ(copies, 0);
}

TEST("move assignment: is noexcept") {
    Message source("source");
    Message target("target");
    target = std::move(source);
    CHECK(std::is_nothrow_move_assignable_v<Message>, "mark the move assignment noexcept");
}

TEST("store: a temporary costs no copies") {
    std::vector<Message> box;
    box.reserve(4);
    store(box, Message("temp"));
    CHECK_EQ(box.size(), 1u);
    CHECK_EQ(box[0].text(), "temp");
    CHECK_EQ(copies, 0);
    CHECK_EQ(moves, 1);
}

TEST("store: a named message is copied once, then moved") {
    std::vector<Message> box;
    box.reserve(4);
    Message keep("keep me");
    store(box, keep);
    CHECK_EQ(keep.text(), "keep me");
    CHECK_EQ(box[0].text(), "keep me");
    CHECK_EQ(copies, 1);
    CHECK_EQ(moves, 1);
}

TEST("store: std::move(named) costs no copies") {
    std::vector<Message> box;
    box.reserve(4);
    Message give("give away");
    store(box, std::move(give));
    CHECK_EQ(box[0].text(), "give away");
    CHECK_EQ(copies, 0);
    CHECK_EQ(moves, 2);
}

TEST("make_message: no copies or moves") {
    Message m = make_message("built in place");
    CHECK_EQ(m.text(), "built in place");
    CHECK_EQ(copies, 0);
    CHECK_EQ(moves, 0);
}

TEST("make_batch: builds every message in place") {
    std::vector<Message> batch = make_batch(3);
    CHECK_EQ(batch.size(), 3u);
    CHECK_EQ(batch[0].text(), "message 1");
    CHECK_EQ(batch[2].text(), "message 3");
    CHECK_EQ(copies, 0);
    CHECK_EQ(moves, 0);
}

TEST("make_batch: zero messages") {
    CHECK_EQ(make_batch(0).size(), 0u);
}
