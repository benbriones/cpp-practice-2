// === Lesson: std::shared_ptr and std::weak_ptr ===============================
//
// Sometimes an object has no single owner. A std::shared_ptr<T> is one of
// several owners: copying it adds an owner, destroying or reset()ting one removes
// one, and the object is deleted when the count of owners reaches zero. It's the
// reference counting Python does for every object, but opt-in and per pointer.
//
// A std::weak_ptr<T> watches a shared object without owning it, so it doesn't
// keep the object alive. You can't use it directly: lock() gives you a
// shared_ptr, which is null if the object is gone, and expired() asks the same.
//
//     auto song = std::make_shared<std::string>("Hey Jude");   // use_count() == 1
//     auto again = song;                     // a copy: two owners, use_count() == 2
//     std::weak_ptr<std::string> watch = song;   // watching doesn't count: still 2
//     song.reset();                          // one owner left
//     again.reset();                         // none: the string is deleted
//     watch.expired();                       // true
//     watch.lock();                          // an empty (null) shared_ptr
//
// The usual way to use a weak_ptr is to lock it into a local shared_ptr, which
// also keeps the object alive while you use it:
//
//     if (std::shared_ptr<Account> account = weak_account.lock()) {
//         account->notify();       // only runs if the Account still exists
//     }
//
// Cycles leak. There's no garbage collector to notice that two objects only
// keep each other alive:
//
//     struct Person {
//         std::shared_ptr<Person> best_friend;   // if two people pick each other,
//     };                                         // neither count can reach zero
//
// The fix is to decide which direction owns. Make that one a shared_ptr, and
// make the way back a weak_ptr. Two shared_ptrs (or a lock()ed weak_ptr and a
// shared_ptr) compare equal with == when they point at the same object.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdshared_ptr/
//            https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/
//
// === Exercise: shared_ptr and weak_ptr =======================================
// A tree where parents own their children through shared_ptrs, and each child
// points back to its parent with a weak_ptr, so the tree can't keep itself alive.
//
//   auto node = std::make_shared<TreeNode>("root");
//
// ./grade 11_raii_smart_pointers/04_shared_and_weak

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// The tests use this to check that nodes are freed.
inline int nodes_alive = 0;

struct TreeNode {
    explicit TreeNode(std::string node_name) : name(std::move(node_name)) { ++nodes_alive; }
    ~TreeNode() { --nodes_alive; }

    std::string name;
    std::vector<std::shared_ptr<TreeNode>> children;
    std::weak_ptr<TreeNode> parent;
};

// Return a new node called name, with no parent.
//
// Example:
//   auto root = make_root("root");
//   // root->name == "root", root->parent.lock() == nullptr, and nodes_alive == 1
//
// The returned shared_ptr is the node's only owner.
std::shared_ptr<TreeNode> make_root(const std::string &name) {
    throw "TODO";
}

// Create a node called name, attach it as the last child of parent, and return it.
// Link it both ways: parent's children holds it, and its parent points back at parent.
//
// Example:
//   auto root = make_root("root");
//   auto docs = add_child(root, "docs");
//   // root->children[0] == docs, and docs->parent.lock() == root
//   // docs.use_count() == 2 (root->children and docs), root.use_count() == 1
//
// The parent owns its children; the weak parent link doesn't keep the parent alive.
std::shared_ptr<TreeNode> add_child(const std::shared_ptr<TreeNode> &parent,
                                    const std::string &name) {
    throw "TODO";
}

// Return the names from the root down to node, joined by '/'.
// A node with no parent has just its own name as its path.
//
// Example:
//   root has a child docs, and docs has a child notes
//   path(root) == "root"
//   path(docs) == "root/docs"
//   path(notes) == "root/docs/notes"
std::string path(const std::shared_ptr<TreeNode> &node) {
    throw "TODO";
}

// Return the number of ancestors node has.
// A root has depth 0, its children depth 1, their children depth 2, and so on.
//
// Example:
//   root has a child a, a has a child b, and b has a child c
//   depth(root) == 0, depth(a) == 1, depth(c) == 3
int depth(const std::shared_ptr<TreeNode> &node) {
    throw "TODO";
}

// Remove node from its parent's children and clear its parent link.
// Return true once it's detached. The other children keep their order.
// Return false (and change nothing) if node has no parent.
//
// Example:
//   root has children a, b, c
//   detach(b) == true    // root's children are now a, c, and path(b) == "b"
//   detach(root) == false
//
// A detached node lives on as long as someone still holds a shared_ptr to it.
bool detach(const std::shared_ptr<TreeNode> &node) {
    throw "TODO";
}
