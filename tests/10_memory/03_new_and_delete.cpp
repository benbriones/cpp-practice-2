#include <cstdlib>
#include <new>

#include "grader.hpp"
#include "10_memory/03_new_and_delete.cpp"

// Every new[] / delete[] in this program goes through these, so tests can count live arrays.
int live_arrays = 0;

void* operator new[](std::size_t size) {
    if (void* block = std::malloc(size == 0 ? 1 : size)) {
        ++live_arrays;
        return block;
    }
    throw std::bad_alloc();
}

void operator delete[](void* block) noexcept {
    if (block == nullptr) return;
    --live_arrays;
    std::free(block);
}

void operator delete[](void* block, std::size_t) noexcept { operator delete[](block); }

// The list's values front to back (stops after 100 nodes in case of a cycle).
std::vector<int> values(const Node* head) {
    std::vector<int> out;
    for (; head != nullptr && out.size() < 100; head = head->next) out.push_back(head->value);
    return out;
}

TEST("make_squares: values") {
    int* squares = make_squares(5);
    CHECK_EQ(std::vector<int>(squares, squares + 5), {0, 1, 4, 9, 16});
    delete[] squares;
}

TEST("make_squares: one element") {
    int* squares = make_squares(1);
    CHECK_EQ(squares[0], 0);
    delete[] squares;
}

TEST("make_squares: allocates exactly one array") {
    int before = live_arrays;
    int* squares = make_squares(10);
    const int arrays_allocated = live_arrays - before;
    CHECK_EQ(arrays_allocated, 1);
    delete[] squares;
}

TEST("resize_array: growing keeps values and zero-fills") {
    int* old_values = new int[3]{1, 2, 3};
    int* bigger = resize_array(old_values, 3, 5);
    CHECK_EQ(std::vector<int>(bigger, bigger + 5), {1, 2, 3, 0, 0});
    delete[] bigger;
}

TEST("resize_array: shrinking keeps the first values") {
    int* old_values = new int[4]{1, 2, 3, 4};
    int* smaller = resize_array(old_values, 4, 2);
    CHECK_EQ(std::vector<int>(smaller, smaller + 2), {1, 2});
    delete[] smaller;
}

TEST("resize_array: frees the old array") {
    int before = live_arrays;
    int* old_values = new int[3]{1, 2, 3};
    int* resized = resize_array(old_values, 3, 6);
    const int arrays_still_allocated = live_arrays - before;
    CHECK_EQ(arrays_still_allocated, 1);
    delete[] resized;
}

TEST("push_front: builds the list front to back") {
    Node* list = nullptr;
    list = push_front(list, 3);
    list = push_front(list, 2);
    list = push_front(list, 1);
    CHECK_EQ(values(list), {1, 2, 3});
    CHECK_EQ(Node::live, 3);
}

TEST("list_sum") {
    Node* list = nullptr;
    CHECK_EQ(list_sum(list), 0);
    for (int v : {4, -1, 10}) list = push_front(list, v);
    CHECK_EQ(list_sum(list), 13);
}

TEST("reverse_list: re-links the same nodes") {
    Node* list = nullptr;
    for (int v : {4, 3, 2, 1}) list = push_front(list, v);
    Node* old_head = list;
    list = reverse_list(list);
    CHECK_EQ(values(list), {4, 3, 2, 1});
    CHECK(old_head->next == nullptr, "The old head should now be the last node");
    CHECK_EQ(Node::live, 4);
}

TEST("reverse_list: empty and one-node lists") {
    CHECK(reverse_list(nullptr) == nullptr, "reverse_list(nullptr) should return nullptr");
    Node* single = push_front(nullptr, 7);
    CHECK_EQ(values(reverse_list(single)), {7});
}

TEST("free_list: deletes every node") {
    Node* list = nullptr;
    for (int i = 0; i < 50; ++i) list = push_front(list, i);
    CHECK_EQ(Node::live, 50);
    free_list(list);
    CHECK_EQ(Node::live, 0);
}

TEST("free_list: empty list is fine") {
    free_list(nullptr);
    CHECK_EQ(Node::live, 0);
}
