#include "grader.hpp"
#include "16_multi_file_programs/03_classes_and_templates_in_headers/clamp.hpp"
#include "16_multi_file_programs/03_classes_and_templates_in_headers/inventory.hpp"

TEST("clamp_value works for any ordered type") {
    CHECK_EQ(clamp_value(5, 0, 10), 5);
    CHECK_EQ(clamp_value(-5, 0, 10), 0);
    CHECK_NEAR(clamp_value(1.5, 0.0, 1.0), 1.0);
    CHECK_EQ(clamp_value('z', 'a', 'm'), 'm');
}

TEST("a new Inventory is empty") {
    const Inventory inventory;
    CHECK_EQ(inventory.count("apple"), 0);
    CHECK_EQ(inventory.total_items(), 0);
    CHECK_EQ(inventory.distinct_items(), 0);
}

TEST("Inventory::created counts every construction") {
    const int before = Inventory::created();
    Inventory first;
    Inventory second;
    CHECK_EQ(Inventory::created() - before, 2);
}

TEST("add and count") {
    Inventory inventory;
    inventory.add("apple", 5);
    inventory.add("pear", 2);
    inventory.add("apple", 3);
    CHECK_EQ(inventory.count("apple"), 8);
    CHECK_EQ(inventory.count("pear"), 2);
    CHECK_EQ(inventory.count("kiwi"), 0);
}

TEST("total_items and distinct_items") {
    Inventory inventory;
    inventory.add("apple", 5);
    inventory.add("pear", 2);
    inventory.add("fig", 1);
    CHECK_EQ(inventory.total_items(), 8);
    CHECK_EQ(inventory.distinct_items(), 3);
}

TEST("removing never goes below zero, and empty items disappear") {
    Inventory inventory;
    inventory.add("apple", 5);
    inventory.add("apple", -8);
    CHECK_EQ(inventory.count("apple"), 0);
    CHECK_EQ(inventory.distinct_items(), 0);
    inventory.add("pear", -3);
    CHECK_EQ(inventory.distinct_items(), 0);
}

TEST("counts are capped at kMaxPerItem") {
    Inventory inventory;
    inventory.add("bolt", 600);
    inventory.add("bolt", 600);
    CHECK_EQ(inventory.count("bolt"), Inventory::kMaxPerItem);
    inventory.add("bolt", -99);
    CHECK_EQ(inventory.count("bolt"), 900);
}
