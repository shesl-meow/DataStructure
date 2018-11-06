#pragma once
using namespace Tree;

typedef unsigned int uint;

template<class T>
HuffmanTree<T>::HuffmanTree(const std::list<T>& lst)
{
  for(auto it = lst.begin(); it != lst.end(); ++it)
    this->tree_lst.push_back(BinTree<T>(*it));
}

template<class T>
void HuffmanTree<T>::gnr_huffman_tree()
{
  while(tree_lst.size() > 1){ this->gnr_mini_tree(); }
  this->release_self_node();
  BinTree<T> *new_tree = new BinTree<T>(tree_lst.front());
  this->data = new_tree->get_self_data();
  if(new_tree->has_left_child())
    this->insert_left_tree( *(new_tree->get_left_tree()) );
  if(new_tree->has_right_child())
    this->insert_right_tree( *(new_tree->get_right_tree()) );
}

template<class T>
void HuffmanTree<T>::gnr_huffman_tree(const BinTree<T>& bt)
{
  this->tree_lst = bt.get_all_node();
  this->gnr_huffman_tree();
}

template<class T>
void HuffmanTree<T>::gnr_mini_tree()
{
  if(this->tree_lst.size() < 2) throw std::logic_error("The tree_lst parameter required two parameter at least.");
  this->tree_lst.sort(typename BinTree<T>::data_less_than());

  BinTree<T> rgt_t = tree_lst.front();
  tree_lst.erase(tree_lst.begin());
  BinTree<T> lft_t = tree_lst.front();
  tree_lst.erase(tree_lst.begin());

  BinTree<T> new_tree(lft_t.get_self_data() + rgt_t.get_self_data());
  new_tree.insert_left_tree(lft_t);
  new_tree.insert_right_tree(rgt_t);
  tree_lst.push_back(new_tree);
}
