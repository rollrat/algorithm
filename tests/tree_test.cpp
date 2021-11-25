//

#include "../src/tree.hpp"
#include <iostream>

int main() {
  linked_binary_tree<int> tree;

  // init tree
  tree.refresh(0);

  // get root and push some nodes
  auto cur_node = tree.root();
  cur_node->left = tree.make_node(4);
  cur_node->left->right = tree.make_node(5);

  if (tree.root()->left->right->value != 5)
    return -1;

  std::cout << "success";

  return 0;
}