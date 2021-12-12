
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

  virtual void remove(const T &value) {
    if (this->root() == nullptr)
      return;

    this->tree.root()->right =
        remove_internal(this->tree.root()->right, this->tree.root(), value);
  }

private:
  node_type *insert_internal(node_type *parent, node_type *n_node) {
    // if key exists, then dot not any behavior
    if (n_node->value < parent->value) {
      parent->left = parent->left != nullptr
                         ? insert_internal(parent->left, n_node)
                         : n_node;
    } else if (n_node->value > parent->value) {
      parent->right = parent->right != nullptr
                          ? insert_internal(parent->right, n_node)
                          : n_node;
    }

    return balance(parent);
  }

  node_type *remove_internal(node_type *parent, node_type *parent_parent,
                             const T &value) {
    if (value < parent->value) {
      if (parent->left == nullptr)
        return parent;

      parent->left = remove_internal(parent->left, parent, value);
    } else if (value > parent->value) {
      if (parent->right == nullptr)
        return parent;

      parent->right = remove_internal(parent->right, parent, value);
    } else {
      if (parent->left == nullptr || parent->right == nullptr) {
        node_type *tmp;

        if (parent_parent->left == parent) {
          tmp = parent_parent->left =
              parent->left == nullptr
                  ? parent->right == nullptr ? nullptr : parent->right
                  : parent->left;
        } else {
          tmp = parent_parent->right =
              parent->left == nullptr
                  ? parent->right == nullptr ? nullptr : parent->right
                  : parent->left;
        }

        parent->left = nullptr;
        parent->right = nullptr;
        this->tree.remove_node(parent);

        parent = tmp;

        if (parent == nullptr)
          return nullptr;
      } else {
        remove_internal_right_most_value(parent->left, parent, parent);
      }
    }

    return balance(parent);
  }

  node_type *remove_internal_right_most_value(node_type *p, node_type *pp,
                                              node_type *parent) {
    if (p->right != nullptr) {
      p->right = remove_internal_right_most_value(p->right, p, parent);
    } else {
      if (parent->left == p)
        parent->left = nullptr;

      if (p->left != nullptr)
        pp->left = p->left;

      p->swap_value(parent);

      p->left = nullptr;
      p->right = nullptr;
      this->tree.remove_node(p);

      return nullptr;
    }

    return balance(p);
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
               A              A              C
             /               /             /  \
            B      =>       C     =>      B    A
             \            /
              C          B
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
          A            A                C
           \            \             /  \
            B    =>      C     =>    A    B
          /               \
         C                 B
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