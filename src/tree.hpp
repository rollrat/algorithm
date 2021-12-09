

#pragma once

#include <ostream>

template <typename T> struct linked_binary_tree_node {
  typedef class linked_binary_tree_node<T> this_type;
  this_type *left = nullptr;
  this_type *right = nullptr;
  T value;

  linked_binary_tree_node(T value) : value(value) {}

  void swap_value(this_type *node) { std::swap(this->value, node->value); }
};

template <typename T> class linked_binary_tree {
  typedef class linked_binary_tree_node<T> node_type;
  node_type *root_node = nullptr;

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
    remove_node(node->left);
    remove_node(node->right);
    delete node;
  }

  void print(std::ostream &out) const {
    if (root_node == nullptr)
      return;

    print_internal(out, root_node, 0, true);
  }

  static void print(std::ostream &out, node_type *node) {
    if (node == nullptr)
      return;

    print_internal(out, node, 0, true);
  }

private:
  static void print_internal(std::ostream &out, node_type *node,
                             int indent_depth, bool is_left) {
    auto indent = std::string(indent_depth, ' ');

    if (is_left) {
      out << indent << " - L: " << node->value << std::endl;
    } else {
      out << indent << " - R: " << node->value << std::endl;
    }

    if (node->left != nullptr)
      print_internal(out, node->left, indent_depth + 2, true);
    if (node->right != nullptr)
      print_internal(out, node->right, indent_depth + 2, false);
  }
};

template <typename T> class binary_tree {
  T *array;
  int capacity = 1;
  int depth = 0;

  /*
       O     <== depth 0

    Capacity = 1

       O     <== depth 0
     /  \    <== depth 1
    O   O    <== depth 2

    Capacity = 3

          O
        /  \
       O    O
     /  \ /  \
    O   OO   O   <== depth 3

    Capacity = 7

    Capacity = 2**depth - 1
  */

public:
  void ensure_depth(int depth) { ensure_capacity(depth); }

  T &operator[](int index) { return this->array[index]; }

private:
  void ensure_capacity(int depth) {
    if (this->depth < depth) {
      this->depth += 1;
      int tsize = 1 << this->depth - 1;
      T *tarr = new T[tsize];
      if (this->array != nullptr)
        for (int i = 0; i < this->capacity; i++)
          tarr[i] = array[i];
      this->capacity = tsize;
      this->array = tarr;
    }
  }
};