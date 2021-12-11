
#pragma once

#include <iostream>

#include "tree.hpp"

// T must be comparable, printable type
template <typename T, class N = linked_binary_tree_node<T>>
class linked_binary_serach_tree {
public:
  typedef N node_type;
  typedef class linked_binary_tree<T, node_type> tree_type;

  linked_binary_serach_tree() { tree.refresh(-1); }

  node_type *root() const { return tree.root()->right; }

  void print(std::ostream &out) const { tree.print(out); }

  virtual void insert(const T &value) {
    node_type *new_node = tree_type::make_node(value);

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

  virtual node_type *find(const T &value) {
    node_type *iter = tree.root()->right;

    while (iter != nullptr) {
      if (iter->value == value)
        return iter;
      if (iter->value < value) {
        iter = iter->right;
      } else {
        iter = iter->left;
      }
    }

    return nullptr;
  }

  virtual void remove(const T &value) {
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

protected:
  tree_type tree;

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
  node_type *rotate_left(node_type *node, node_type *node_p) {
    node_type *B = nullptr;
    node_type *C = nullptr;
    node_type *D = nullptr;

    B = node;
    D = node->right;

    if (D != nullptr)
      C = D->left;

    if (node_p != nullptr)
      if (node_p->left == node)
        node_p->left = D;
      else
        node_p->right = D;

    D->left = B;
    B->right = C;

    return D;
  }

  node_type *rotate_right(node_type *node, node_type *node_p) {
    node_type *B = nullptr;
    node_type *C = nullptr;
    node_type *D = nullptr;

    D = node;
    B = D->left;

    if (B->right != nullptr)
      C = B->right;

    if (node_p != nullptr)
      if (node_p->left == node)
        node_p->left = B;
      else
        node_p->right = B;

    B->right = D;
    D->left = C;

    return B;
  }
};