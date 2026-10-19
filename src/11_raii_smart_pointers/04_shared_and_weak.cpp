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

// A new node with no parent.
std::shared_ptr<TreeNode> make_root(const std::string& name) {
    throw "TODO";
}

// Create a node called name, attach it as the last child of parent, return it.
std::shared_ptr<TreeNode> add_child(const std::shared_ptr<TreeNode>& parent,
                                    const std::string& name) {
    throw "TODO";
}

// Names from the root down to node, joined by '/': "root/docs/notes".
std::string path(const std::shared_ptr<TreeNode>& node) {
    throw "TODO";
}

// Number of ancestors: a root has depth 0, its children depth 1.
int depth(const std::shared_ptr<TreeNode>& node) {
    throw "TODO";
}

// Remove node from its parent's children and clear its parent link.
// Return false (and change nothing) if node has no parent.
bool detach(const std::shared_ptr<TreeNode>& node) {
    throw "TODO";
}
