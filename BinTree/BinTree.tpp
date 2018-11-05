#pragma once
#include "BinTree.h"
#include "DisplayMap.h"
#include <sstream>

template<class T>
bool BinTree<T>::update_left_tree(BinTree<T> lft_t)
{
  if(this->lftChild == nullptr) return false;
  else *(this->lftChild) = lft_t;
  return true;
}

template<class T>
bool BinTree<T>::update_right_tree(BinTree<T> rgt_t)
{
  if(this->rgtChild == nullptr) return false;
  *(this->rgtChild) = rgt_t;
  return true;
}

template<class T>
bool BinTree<T>::insert_left_tree(BinTree<T> lft_t)
{
  if(this->lftChild != nullptr) return false;
  this->lftChild = new BinTree<T>;
  *(this->lftChild) = lft_t;
  return true;
}

template<class T>
bool BinTree<T>::insert_right_tree(BinTree<T> rgt_t)
{
  if(this->rgtChild != nullptr) return false;
  this->rgtChild = new BinTree<T>;
  *(this->rgtChild) = rgt_t;
  return true;
}

template<class T>
void BinTree<T>::release_left_tree()
{
  if(this->lftChild == nullptr) return;
  delete this->lftChild;
  this->lftChild = nullptr;
}

template<class T>
void BinTree<T>::release_right_tree()
{
  if(this->rgtChild == nullptr) return;
  delete this->rgtChild;
  this->rgtChild = nullptr;
}

template<class T>
unsigned int BinTree<T>::depth()const{
  unsigned int result = 1;
  if(this->has_left_child()){
    auto lft_depth = this->lftChild->depth() + 1;
    result = (result > lft_depth) ? result : lft_depth;
  }
  if(this->has_right_child()){
    auto rgt_depth = this->rgtChild->depth() + 1;
    result = (result > rgt_depth) ? result : rgt_depth;
  }
  return result;
}

template<class T>
void BinTree<T>::display()const{
  // auto dp = this->depth();
  // DisplayMap::DisplayMap dm(fast_pow(2, dp-1), 2*dp - 1);
}
