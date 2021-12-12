//

#include "../src/balanced_tree.hpp"
#include <iostream>

int main() {
  avl_tree<int> tree;

  tree.insert(3);
  tree.insert(5);
  tree.insert(4);
  tree.insert(6);
  tree.insert(7);
  tree.insert(8);
  tree.insert(1);
  tree.insert(10);

  //   tree.rotate_left(tree.root());
  tree.print(std::cout);

  // tree.remove(6);
  // tree.print(std::cout);
  tree.remove(4);
  tree.print(std::cout);


  return 0;
}