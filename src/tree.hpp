

#pragma once

template <typename T>
struct linked_binary_tree_node {
    typedef class linked_binary_tree_node<T> this_type;
    this_type* left;
    this_type* right;
    this_type* parent;
    T value;
};

template <typename T>
class linked_binary_tree {

};
