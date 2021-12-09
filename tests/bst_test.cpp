//

#include "../src/binary_search_tree.hpp"
#include <iostream>

int main() {
  linked_binary_serach_tree<int> tree;

  tree.insert(3);
  tree.insert(5);
  tree.insert(4);
  tree.insert(6);

  tree.print(std::cout);

  tree.remove(5);

  tree.print(std::cout);

  tree.insert(5);
  tree.print(std::cout);
  tree.insert(1);
  tree.print(std::cout);
  tree.insert(2);
  tree.print(std::cout);

  tree.remove(3);
  tree.print(std::cout);
  tree.remove(6);
  tree.print(std::cout);

  tree.remove(10);
  tree.print(std::cout);


  return 0;
}