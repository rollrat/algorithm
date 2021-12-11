//

#include "../src/heap_tree.hpp"
#include <iostream>

int main() {
  linked_heap_tree<int> tree;

  tree.push(8);
  tree.push(7);
  tree.push(6);
  tree.push(10);
  tree.push(9);
  tree.push(54);
  tree.push(1);

  tree.print(std::cout);

  tree.pop();
  tree.print(std::cout);
  tree.pop();
  tree.print(std::cout);
  tree.pop();
  tree.print(std::cout);
  tree.pop();
  tree.print(std::cout);
  tree.pop();
  tree.print(std::cout);
  tree.pop();
  tree.print(std::cout);
  tree.pop();
  tree.print(std::cout);
  tree.pop();
  tree.print(std::cout);

  return 0;
}