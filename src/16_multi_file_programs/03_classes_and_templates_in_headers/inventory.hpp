// === Lesson: Classes and templates across files ==============================
//
// A class definition goes in a header, because every file that creates or uses
// the class needs to see its members. The bodies of its member functions can
// stay in the class (implicitly inline, fine for one-liners) or move to the
// .cpp file, written with the class name and :: in front:
//
//     // playlist.hpp
//     class Playlist {
//     public:
//         Playlist();
//         void add(const std::string& song, int seconds = 180);
//         int total_seconds() const;
//         static int playlists_made();
//     private:
//         std::vector<int> lengths_;
//         static int made_;   // declared here, but not yet defined
//     };
//
//     // playlist.cpp
//     #include "playlist.hpp"
//     int Playlist::made_ = 0;   // the one definition; no `static` here
//     Playlist::Playlist() { ++made_; }
//     void Playlist::add(const std::string& song, int seconds) { ... }   // no default
//     int Playlist::total_seconds() const { ... }   // const must be repeated
//     int Playlist::playlists_made() { return made_; }   // no `static` here
//
// The signature outside the class must match the declaration exactly, const
// included. Default arguments and the `static` keyword appear only in the class.
//
// A static data member like made_ is shared by all objects. Inside the class
// it's only declared, so exactly one .cpp must define it, as above. Since C++17
// you can instead write `inline static int made_ = 0;` in the class, which is
// a definition the linker merges across files. static constexpr members are
// inline automatically.
//
// Templates are different. The compiler writes the code for pick<int> at the
// call, from the template body it can see right there. If the body lives in a
// .cpp file, other files see only the declaration, assume pick<int> was
// generated somewhere else, and the link fails because it never was. So a
// template's whole definition goes in the header:
//
//     // pick.hpp
//     template <typename T>
//     const T& pick(bool first, const T& a, const T& b) { return first ? a : b; }
//
// Templates are exempt from "define it only once", like inline functions.
//
// Read more: https://www.learncpp.com/cpp-tutorial/classes-and-header-files/
//            https://www.learncpp.com/cpp-tutorial/static-member-variables/
//
// === Exercise: Classes and templates across files ============================
// This folder compiles but doesn't link: grade shows "Undefined symbols". Fix
// all three causes:
//
//   1. inventory.cpp is missing some of Inventory's member functions. Define
//      them there, outside the class:
//          int Inventory::count(const std::string& item) const { ... }
//   2. The static data member created_ (below) is declared but never defined.
//      Give it exactly one definition in inventory.cpp:  int Inventory::created_ = 0;
//      (or declare it `inline static int created_ = 0;` here instead).
//   3. clamp_value is a template whose body sits in clamp.cpp. Move it into
//      clamp.hpp (clamp.cpp can then go).
//
// Then implement Inventory::add.
//
// ./grade 16_multi_file_programs/03_classes_and_templates_in_headers

#pragma once

#include <cstddef>
#include <map>
#include <string>

class Inventory {
public:
    // The most of any one item an Inventory will hold.
    static constexpr int kMaxPerItem = 999;

    Inventory();

    // Change an item's count by quantity (negative removes). Keep the result in
    // 0..kMaxPerItem using clamp_value. An item whose count reaches 0 is dropped.
    void add(const std::string& item, int quantity);

    // The item's count; 0 if it isn't stocked.
    int count(const std::string& item) const;

    // Sum of every item's count.
    int total_items() const;

    // How many different items are stocked.
    std::size_t distinct_items() const;

    // How many Inventory objects have been constructed so far.
    static int created();

private:
    std::map<std::string, int> stock_;
    static int created_;
};
