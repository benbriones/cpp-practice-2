// Exercise: new and delete
// `new` creates an object on the heap and returns a pointer to it. The object
// lives until you `delete` it, whichever function you're in by then.
//
//     int* one = new int(5);      ...   delete one;
//     int* many = new int[n]();   ...   delete[] many;   ← arrays need delete[]
//
// Forget the delete and you leak; delete twice, or touch the memory after
// deleting it, and you get undefined behavior. The tests count every
// allocation, so leaks fail too.
//
// Grade: grade 10_memory/03_new_and_delete

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
