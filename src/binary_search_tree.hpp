
#pragma once

#include <iostream>

#include "tree.hpp"

// T must be comparable, printable type
template <typename T> class linked_binary_serach_tree {
  typedef class linked_binary_tree_node<T> node_type;
  typedef class linked_binary_tree<T> tree_type;

  tree_type tree;

public:
  linked_binary_serach_tree() { tree.refresh(-1); }

  node_type *root() const { return tree.root()->right; }

  void print(std::ostream &out) const { tree.print(out); }

  void insert(const T &value) {
    node_type *new_node = tree.make_node(value);

    // if root node not exists
    if (tree.root()->right == nullptr) {
      tree.root()->right = new_node;
      return;
    }

    node_type *iter = tree.root()->right;

    while (iter != nullptr) {
      if (iter->value <= value) {
        if (iter->right == nullptr) {
          iter->right = new_node;
          return;
        }
        iter = iter->right;
      } else {
        if (iter->left == nullptr) {
          iter->left = new_node;
          return;
        }
        iter = iter->left;
      }
    }
  }

  void remove(const T &value) {
    node_type *iter = tree.root()->right;
    node_type *iter_p = tree.root();

    while (iter != nullptr && iter->value != value) {
      iter_p = iter;
      iter = iter->value <= value ? iter->right : iter->left;
    }

    if (iter == nullptr)
      return;

    if (iter->left == nullptr || iter->right == nullptr) {
      if (iter_p->left == iter)
        iter_p->left = iter->left == nullptr
                           ? iter->right == nullptr ? nullptr : iter->right
                           : iter->left;
      else
        iter_p->right = iter->left == nullptr
                            ? iter->right == nullptr ? nullptr : iter->right
                            : iter->left;
    } else {
      // pull left most large node
      node_type *l_node = iter->left;
      node_type *l_node_p = iter;
      while (l_node->right != nullptr) {
        l_node_p = l_node;
        l_node = l_node->right;
      }
      if (iter->left != l_node)
        l_node_p->right = nullptr;
      else
        iter->left = nullptr;
      if (l_node->left != nullptr)
        l_node_p->left = l_node->left;
      l_node->swap_value(iter);
      iter = l_node;
    }

    iter->left = nullptr;
    iter->right = nullptr;
    tree.remove_node(iter);
  }

private:
  /*
             B
           /  \
          A    D
             /  \
            C    E

          <====>

                D
              /  \
             B    E
           /  \
          A    C
  */
  node_type *rotate_left(node_type *node) {
    node_type *B = node;
    node_type *D = node->right;
    node_type *C = D->left;

    D->parent = B->parent;
    B->parent = D;
    if (C != nullptr)
      C->parent = B;
    B->right = C;
    D->left = B;

    return D;
  }
  node_type *rotate_right(node_type *node) {
    node_type *B = node->right;
    node_type *D = node;
    node_type *C = B->right;

    B->parent = D->parent;
    D->parent = B;
    if (C != nullptr)
      C->parent = D;
    B->right = D;
    D->left = C;

    return B;
  }
};