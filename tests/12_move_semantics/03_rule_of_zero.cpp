#include "grader.hpp"
#include "12_move_semantics/03_rule_of_zero.cpp"

#include <type_traits>
#include <utility>
#include <vector>

TEST("name and songs") {
    Playlist p("Road trip");
    p.add("Song A");
    p.add("Song B");
    p.add("Song C");
    CHECK_EQ(p.name(), "Road trip");
    CHECK_EQ(p.size(), 3);
    CHECK_EQ(p.song(0), "Song A");
    CHECK_EQ(p.song(2), "Song C");
}

TEST("song(): a bad index throws") {
    Playlist p("Empty");
    CHECK_THROWS(std::out_of_range, p.song(0));
    p.add("Only");
    CHECK_THROWS(std::out_of_range, p.song(1));
    CHECK_THROWS(std::out_of_range, p.song(-1));
}

TEST("holds lots of songs") {
    Playlist p("Long");
    for (int i = 0; i < 100; ++i) p.add("track " + std::to_string(i));
    CHECK_EQ(p.size(), 100);
    CHECK_EQ(p.song(99), "track 99");
}

TEST("copy: same name and songs, but independent") {
    Playlist original("Mix");
    original.add("One");
    Playlist copy = original;
    copy.add("Two");
    CHECK_EQ(copy.name(), "Mix");
    CHECK_EQ(copy.size(), 2);
    CHECK_EQ(original.size(), 1);
}

TEST("copy assignment: copies the name too") {
    Playlist source("Source");
    source.add("A");
    Playlist target("Target");
    target = source;
    CHECK_EQ(target.name(), "Source");
    CHECK_EQ(target.size(), 1);
    CHECK_EQ(target.song(0), "A");
}

TEST("copy assignment: self-assignment is safe") {
    Playlist p("Self");
    p.add("A");
    p.add("B");
    Playlist &same = p;
    p = same;
    CHECK_EQ(p.size(), 2);
    CHECK_EQ(p.song(1), "B");
    CHECK_EQ(p.name(), "Self");
}

TEST("moving takes the songs") {
    Playlist original("Moving");
    original.add("A");
    original.add("B");
    Playlist moved = std::move(original);
    CHECK_EQ(moved.name(), "Moving");
    CHECK_EQ(moved.size(), 2);
    CHECK_EQ(moved.song(1), "B");
}

TEST("moves are noexcept") {
    Playlist p("Check");
    p.add("A");
    Playlist moved = std::move(p);
    CHECK(std::is_nothrow_move_constructible_v<Playlist>,
          "Playlist's moves should be noexcept; with std::string and std::vector members, "
          "the compiler-generated ones are");
    CHECK(std::is_nothrow_move_assignable_v<Playlist>, "move assignment should be noexcept");
}

TEST("works inside a std::vector") {
    std::vector<Playlist> shelf;
    for (int i = 0; i < 5; ++i) {
        Playlist p("List " + std::to_string(i));
        p.add("Song " + std::to_string(i));
        shelf.push_back(p);
    }
    std::vector<Playlist> copy = shelf;
    CHECK_EQ(copy.size(), 5u);
    CHECK_EQ(copy[4].name(), "List 4");
    CHECK_EQ(copy[4].song(0), "Song 4");
}
