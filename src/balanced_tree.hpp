
#pragma once

#include "binary_search_tree.hpp"

template <typename T> class avl_tree : public linked_binary_serach_tree<T> {
  typedef typename linked_binary_serach_tree<T>::node_type node_type;
  typedef typename linked_binary_serach_tree<T>::tree_type tree_type;

public:
  avl_tree() {}

  virtual void insert(const T &value) {
    node_type *new_node = tree_type::make_node(value);

    if (this->tree.root()->right == nullptr) {
      this->tree.root()->right = new_node;
      return;
    }

    this->tree.root()->right = insert_internal(this->root(), new_node);
  }

  virtual void remove(const T &value) {}

private:
  node_type *insert_internal(node_type *parent, node_type *n_node) {
    if (n_node->value < parent->value) {
      if (parent->left != nullptr)
        parent->left = insert_internal(parent->left, n_node);
      else
        parent->left = n_node;

    } else {
      if (parent->right != nullptr)
        parent->right = insert_internal(parent->right, n_node);
      else
        parent->right = parent->right = n_node;
    }

    return balance(parent);
  }

  node_type *balance(node_type *target) {
    int diff = this->diff(target);

    if (diff > 1) {
      /*
                 A                 B
               /                 /  \
              B         =>      C    A
            /
          C
      */
      if (this->diff(target->left) > 0) {
        target = this->rotate_right(target, nullptr);
      }

      /*
                 A                 C
               /                 /  \
              B         =>      B    A
               \
                C
      */
      else {
        this->rotate_left(target->left, target);
        target = this->rotate_right(target, nullptr);
      }
    } else if (diff < -1) {

      /*
          A                    B
           \                 /  \
            B         =>    A    C
             \
              C
      */
      if (this->diff(target->right) <= 0) {
        target = this->rotate_left(target, nullptr);
      }

      /*
          A                    C
           \                 /  \
            B         =>    A    B
          /
         C
      */
      else {
        this->rotate_right(target->right, target);
        target = this->rotate_left(target, nullptr);
      }
    }

    return target;
  }

  int height(node_type *parent) {
    if (parent == nullptr)
      return 0;
    return std::max(height(parent->left), height(parent->right)) + 1;
  }

  int diff(node_type *parent) {
    return height(parent->left) - height(parent->right);
  }
};

template <typename T> class rb_tree_node {};

template <typename T> class rb_tree {};