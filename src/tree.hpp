

#pragma once

template <typename T> struct linked_binary_tree_node {
  typedef class linked_binary_tree_node<T> this_type;
  this_type *left;
  this_type *right;
  this_type *parent;
  T value;

  linked_binary_tree_node(T value) : value(value) {}
};

template <typename T> class linked_binary_tree {
  typedef class linked_binary_tree_node<T> node_type;
  node_type *root_node;

public:
  node_type *root() const { return root_node; }

  void refresh(const T &value) {
    remove_node(this->root_node);
    root_node = make_node(value);
  }

  node_type *make_node(const T &type) {
    node_type *node = new node_type(type);
    return node;
  }

  void remove_node(node_type *node) {
    if (node == nullptr)
      return;
  }
};
