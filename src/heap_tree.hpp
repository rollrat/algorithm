
#pragma once

#include <iostream>
#include <queue>

#include "tree.hpp"

template <typename T> class linked_heap_tree {
  typedef class linked_binary_tree_node_allow_parent<T> node_type;
  typedef class linked_binary_tree<T, node_type> tree_type;

  tree_type tree;

public:
  linked_heap_tree() { tree.refresh(-1); }

  inline node_type *root() const { return tree.root()->right; }

  void print(std::ostream &out) const { tree.print(out); }

  const T &top() const { return root()->value; }

  void push(const T &value) {
    node_type *new_node = tree.make_node(value);

    // if root node not exists
    if (tree.root()->right == nullptr) {
      tree.root()->right = new_node;
      return;
    }

    // find null leaf
    node_type *leaf = find_null_leaf();

    // put node to leaf
    new_node->parent = leaf;
    if (leaf->left == nullptr)
      leaf->left = new_node;
    else
      leaf->right = new_node;

    // proccessing bottom up
    bottom_up(new_node);
  }

  void pop() {
    if (root() == nullptr)
      return;

    node_type *leaf = find_leaf();

    if (leaf == root()) {
      tree.root()->right = nullptr;
      tree.remove_node(leaf);
      return;
    }

    // swap root with leaf
    root()->swap_value(leaf);

    // remove leaf node
    if (leaf->parent->left == leaf)
      leaf->parent->left = nullptr;
    else
      leaf->parent->right = nullptr;
    tree.remove_node(leaf);

    top_down(root());
  }

private:
  node_type *find_null_leaf() {
    std::queue<node_type *> bfs;
    node_type *latest;
    bfs.push(root());
    while (!bfs.empty()) {
      latest = bfs.front();
      bfs.pop();
      if (latest->left == nullptr || latest->right == nullptr)
        break;
      if (latest->left != nullptr)
        bfs.push(latest->left);
      if (latest->right != nullptr)
        bfs.push(latest->right);
    }
    return latest;
  }

  node_type *find_leaf() {
    std::queue<node_type *> bfs;
    node_type *latest;
    bfs.push(root());
    while (!bfs.empty()) {
      latest = bfs.front();
      bfs.pop();
      if (latest->left != nullptr)
        bfs.push(latest->left);
      if (latest->right != nullptr)
        bfs.push(latest->right);
    }
    return latest;
  }

  void bottom_up(node_type *node) {
    node_type *cur = node;

    while (cur != nullptr) {
      if (cur->parent == nullptr)
        return;
      if (cur->value > cur->parent->value)
        return;

      cur->parent->swap_value(cur);
      cur = cur->parent;
    }
  }

  void top_down(node_type *node) {
    node_type *cur = node;

    while (cur != nullptr) {
      if (cur->left != nullptr && cur->left->value < cur->value) {
        cur->left->swap_value(cur);
        cur = cur->left;
      } else if (cur->right != nullptr && cur->right->value < cur->value) {
        cur->right->swap_value(cur);
        cur = cur->right;
      } else
        break;
    }
  }
};

template <typename T> class heap_tree {
  typedef class binary_tree<T> tree_type;
};