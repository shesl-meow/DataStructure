#include <iostream>
#include "Tree.h"

int main(){
  std::cout << "Hello World!" << std::endl;
  BinTree<double> test_t1(3), test_t2(4), test_t3(2);
  test_t1.insert_left_tree(BinTree<double>(1));
  test_t1.insert_right_tree(BinTree<double>(2));
  test_t2.insert_left_tree(test_t1);
  test_t2.insert_right_tree(8);
  test_t3.insert_left_tree(5);
  test_t3.insert_right_tree(test_t2);
  std::cout << test_t1.depth() << std::endl;
  std::cout << test_t3.depth() << std::endl;
  std::cout << test_t3.count_node_number() << std::endl;

  std::cout << test_t3 << std::endl;

  auto prev = test_t3.pre_order_traverse();
  std::cout << "Prev-Order:";
  for(auto i = prev.begin(); i != prev.end(); ++i) std::cout << *i;
  std::cout << std::endl;

  auto mid = test_t3.mid_order_traverse();
  std::cout << "Mid-Order:";
  for(auto i = mid.begin(); i != mid.end(); ++i) std::cout << *i;
  std::cout << std::endl;

  auto post = test_t3.post_order_traverse();
  std::cout << "Post-Order:";
  for(auto i = post.begin(); i != post.end(); ++i) std::cout << *i;
  std::cout << std::endl;

  std::cout << "access `RL`: " << *(test_t3.get_spec_node("RL")) << std::endl;
  //auto t = test_t3.get_all_node();

  HuffmanTree<double> test_hf(test_t3.get_all_node());
  //test_hf.gnr_huffman_tree();
  std::cout << test_hf;
  return 0;
}
