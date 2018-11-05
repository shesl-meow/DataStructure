#include <iostream>
#include "BinTree.h"
#include "DisplayMap.h"

int main(){
  std::cout << "Hello World!" << std::endl;
  BinTree<double> test_t1(3), test_t2(4);
  test_t1.insert_left_tree(BinTree<double>(1));
  test_t1.insert_right_tree(BinTree<double>(2));
  test_t2.insert_left_tree(test_t1);
  test_t2.insert_right_tree(test_t1);
  std::cout << test_t1.depth() << std::endl;
  std::cout << test_t2.depth() << std::endl;
  DisplayMap::BinTreeMap<double> btm(&test_t2);
  return 0;
}
