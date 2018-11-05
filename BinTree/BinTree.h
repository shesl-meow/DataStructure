#pragma once
#include <exception>
#include <string>

template<class T>
class BinTree{
private:
  T data = T(0);
  BinTree* lftChild = nullptr;
  BinTree* rgtChild = nullptr;
public:
  BinTree(){}
  BinTree(T ele): data(ele) {}
  // query, update, insert, delete function.
  void set_self_node(T ele){ this->data = ele; }
  const BinTree* get_left_tree()const{ return this->lftChild; }
  const BinTree* get_right_tree()const{ return this->rgtChild; }
  bool update_left_tree(BinTree lft_t);
  bool update_right_tree(BinTree rgt_t);
  bool insert_left_tree(BinTree lft_t);
  bool insert_right_tree(BinTree rgt_t);
  void release_left_tree();
  void release_right_tree();
  // check atrribute
  bool has_left_child()const{return this->lftChild != nullptr; }
  bool has_right_child()const{return this->rgtChild != nullptr; }
  unsigned int depth()const;
  // display function

  void display()const;
};

#include "BinTree.tpp"
