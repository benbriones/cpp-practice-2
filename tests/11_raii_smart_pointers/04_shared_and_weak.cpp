#include "grader.hpp"
#include "11_raii_smart_pointers/04_shared_and_weak.cpp"

TEST("make_root: a node with no parent") {
    auto root = make_root("root");
    CHECK_EQ(root->name, "root");
    CHECK(root->parent.lock() == nullptr, "a root's parent should be empty");
    CHECK_EQ(nodes_alive, 1);
}

TEST("add_child: attaches the child both ways") {
    auto root = make_root("root");
    auto docs = add_child(root, "docs");
    CHECK_EQ(docs->name, "docs");
    CHECK_EQ(root->children.size(), 1u);
    CHECK(root->children[0] == docs, "the parent's children should hold the new node");
    CHECK(docs->parent.lock() == root, "the child's parent should be the root");
}

TEST("add_child: children keep their order") {
    auto root = make_root("root");
    add_child(root, "a");
    add_child(root, "b");
    add_child(root, "c");
    CHECK_EQ(root->children.size(), 3u);
    CHECK_EQ(root->children[2]->name, "c");
}

TEST("add_child: shared ownership is counted") {
    auto root = make_root("root");
    auto child = add_child(root, "child");
    // One owner in root->children, one in `child`.
    CHECK_EQ(child.use_count(), 2L);
    CHECK_EQ(root.use_count(), 1L);
}

TEST("path: from the root down") {
    auto root = make_root("root");
    auto docs = add_child(root, "docs");
    auto notes = add_child(docs, "notes");
    CHECK_EQ(path(root), "root");
    CHECK_EQ(path(docs), "root/docs");
    CHECK_EQ(path(notes), "root/docs/notes");
}

TEST("depth") {
    auto root = make_root("root");
    auto a = add_child(root, "a");
    auto b = add_child(a, "b");
    auto c = add_child(b, "c");
    CHECK_EQ(depth(root), 0);
    CHECK_EQ(depth(a), 1);
    CHECK_EQ(depth(c), 3);
}

TEST("children don't keep their parent alive") {
    auto root = make_root("root");
    auto child = add_child(root, "child");
    root.reset();
    CHECK_EQ(nodes_alive, 1);
    CHECK(child->parent.expired(), "the parent was destroyed, so the weak_ptr should be expired");
}

TEST("the whole tree is freed with its root") {
    auto root = make_root("root");
    auto a = add_child(root, "a");
    add_child(a, "a1");
    add_child(a, "a2");
    add_child(root, "b");
    a.reset();
    CHECK_EQ(nodes_alive, 5);
    root.reset();
    CHECK_EQ(nodes_alive, 0);
}

TEST("detach: removes the node from its parent") {
    auto root = make_root("root");
    add_child(root, "a");
    auto b = add_child(root, "b");
    add_child(root, "c");
    CHECK_EQ(detach(b), true);
    CHECK_EQ(root->children.size(), 2u);
    CHECK_EQ(root->children[0]->name, "a");
    CHECK_EQ(root->children[1]->name, "c");
    CHECK(b->parent.lock() == nullptr, "a detached node should have no parent");
    CHECK_EQ(path(b), "b");
}

TEST("detach: a root has nothing to detach from") {
    auto root = make_root("root");
    CHECK_EQ(detach(root), false);
}

TEST("detach: the node survives while someone holds it") {
    auto root = make_root("root");
    auto child = add_child(root, "child");
    detach(child);
    root.reset();
    CHECK_EQ(nodes_alive, 1);
    child.reset();
    CHECK_EQ(nodes_alive, 0);
}
