// Exercise: Classes and templates across files
// This folder compiles but doesn't link: grade shows "Undefined symbols", the
// linker's way of saying "this was declared but never defined". Fix all three:
//
//   1. inventory.cpp is missing some of Inventory's member functions. Define
//      them there, outside the class:
//          int Inventory::count(const std::string& item) const { ... }
//   2. The static data member created_ (below) is declared but never defined.
//      Give it exactly one definition in inventory.cpp:  int Inventory::created_ = 0;
//      (or declare it `inline static int created_ = 0;` here instead).
//   3. clamp_value is a template whose body sits in clamp.cpp. The compiler only
//      generates clamp_value<int> where it can see the body, so template bodies
//      belong in the header. Move it into clamp.hpp (clamp.cpp can then go).
//
// Then implement Inventory::add.
//
// Grade: grade 16_multi_file_programs/03_classes_and_templates_in_headers

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
