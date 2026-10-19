// === Lesson: new, delete and linked lists ====================================
//
// A local variable dies when its function returns. `new` creates an object on
// the heap instead and returns a pointer to it; the object then lives until
// some code calls `delete` on that pointer, in whatever function that happens.
// There's no garbage collector: if nobody deletes it, the memory leaks.
//
//     struct Point { int x; int y; };
//     Point* p = new Point{3, 4};
//     p->x = 10;                         // -> reaches a member through a pointer
//     delete p;                          // gone; p now dangles
//
// Arrays use their own pair of operators, and the two must match:
//
//     int n = 4;
//     double* readings = new double[n]();   // n zeros; without (), garbage values
//     readings[0] = 1.5;
//     delete[] readings;                    // new[] pairs with delete[]
//
// The classic mistakes, all of which compile without complaint:
//
//     leak             forgetting to delete (or losing the last pointer to it)
//     double delete    deleting the same object twice
//     use after free   reading or writing through a pointer after its delete
//     mismatch         delete on memory from new[], or delete[] on memory from new
//
// The last three are undefined behavior. The grader's sanitizer catches double
// deletes and use after free; the tests count allocations to catch leaks.
// delete on a nullptr is allowed and does nothing.
//
// Ownership. Whoever is responsible for the final delete "owns" the object.
// Raw pointers don't say who that is, so it has to be written down: "returns
// a new array; the caller owns it and must delete[] it". Module 11 replaces
// this bookkeeping with types that delete for you.
//
// Linked lists. A list node holds a value and a pointer to the next node; the
// last node's next is nullptr, and a list is a pointer to its first node (an
// empty list is nullptr). You visit every node by following the links:
//
//     struct Item { std::string name; Item* next; };
//     for (const Item* it = first; it != nullptr; it = it->next) {
//         std::cout << it->name << '\n';
//     }
//
// Changing a list means re-pointing `next` fields, and the order of the
// assignments matters: once you overwrite a pointer, or delete a node, whatever
// you can no longer reach is lost. Drawing boxes and arrows on paper helps.
//
// Read more:
// https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/
// https://www.learncpp.com/cpp-tutorial/dynamically-allocating-arrays/
//
// === Exercise: new and delete ================================================
// The tests count every allocation, so leaks fail too.
//
// ./grade 10_memory/03_new_and_delete

// A new heap array of `count` ints (count >= 1) holding the square of each
// index: 0, 1, 4, 9, ... The caller owns it and will delete[] it.
int* make_squares(int count) {
    throw "TODO";
}

// Resize a heap array: allocate new_size ints, copy as many old values as fit,
// set any extra elements to 0, delete[] the old array, and return the new one.
// resize_array({1, 2, 3}, 3, 5) gives {1, 2, 3, 0, 0}.
int* resize_array(int* old_values, int old_size, int new_size) {
    throw "TODO";
}

// One node of a singly linked list. Node::live counts the Nodes that exist
// right now, so the tests can spot leaks. (Constructors and destructors like
// these are covered properly in module 11.)
struct Node {
    int value;
    Node* next;

    inline static int live = 0;
    Node(int v, Node* n) : value(v), next(n) { ++live; }
    ~Node() { --live; }
};

// Put a new node holding `value` in front of head and return it as the new head.
//     Node* list = nullptr;
//     list = push_front(list, 3);
//     list = push_front(list, 1);     // list is now 1 -> 3
Node* push_front(Node* head, int value) {
    throw "TODO";
}

// Sum of every value in the list; an empty list (nullptr) sums to 0.
int list_sum(const Node* head) {
    throw "TODO";
}

// Reverse the list by re-linking the existing nodes (create no new ones) and
// return the new head: 1 -> 2 -> 3 becomes 3 -> 2 -> 1.
Node* reverse_list(Node* head) {
    throw "TODO";
}

// Delete every node. Careful: read node->next before deleting node.
void free_list(Node* head) {
    throw "TODO";
}
