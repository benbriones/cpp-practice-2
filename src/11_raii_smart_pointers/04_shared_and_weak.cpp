// Exercise: shared_ptr and weak_ptr
// A std::shared_ptr is a reference-counted owner: the object dies when the last
// shared_ptr to it goes away. A std::weak_ptr watches without owning; call
// lock() to get a shared_ptr, which is null if the object is already gone.
//
// Parents own their children here. If children owned their parents too, the
// counts could never reach zero and the tree would leak, so each child points
// back with a weak_ptr.
//
//   auto node = std::make_shared<TreeNode>("root");
//
// Grade: grade 11_raii_smart_pointers/04_shared_and_weak

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
