#include <iostream>
#include "BinTree.h"
#include "DisplayMap.h"

int main(){
  std::cout << "Hello World!" << std::endl;
  BinTree<double> test_t1(3), test_t2(4), test_t3(2);
  test_t1.insert_left_tree(BinTree<double>(1));
  test_t1.insert_right_tree(BinTree<double>(2));
  test_t2.insert_left_tree(test_t1);
  test_t2.insert_right_tree(test_t1);
  test_t3.insert_left_tree(test_t3);
  test_t3.insert_right_tree(test_t2);
  std::cout << test_t1.depth() << std::endl;
  std::cout << test_t3.depth() << std::endl;
  std::cout << test_t3.count_node_number() << std::endl;
  //std::cout << "[1] Hello!" << std::endl;
  DisplayMap::BinTreeMap<double> btm(&test_t3);
  //std::cout << "[2] Hello!" << std::endl;
  std::cout << btm << std::endl;
  test_t2.display(std::cout);
  //std::cout << "[3] Hello!" << std::endl; 
  return 0;
}
