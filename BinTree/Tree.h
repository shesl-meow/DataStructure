#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>

typedef unsigned int uint;

namespace Tree{
  template<class T>
  class BinTree{
  protected:
    T data = T(0);
    BinTree* lftChild = nullptr;
    BinTree* rgtChild = nullptr;
  public:
    BinTree(){}
    BinTree(T ele): data(ele) {}
    BinTree(const BinTree& tree);
    ~BinTree(){ this->release_self_node(); }
    // query, update, insert, delete function.
    T get_self_node()const{ return this->data; }
    const BinTree* get_left_tree()const{ return this->lftChild; }
    const BinTree* get_right_tree()const{ return this->rgtChild; }
    const BinTree* get_spec_node(std::string path, char lc = 'L', char rc = 'R')const;
    void update_self_node(T ele){ this->data = ele; }
    void update_left_tree(const BinTree& lft_t);
    void update_right_tree(const BinTree& rgt_t);
    void update_spec_node(std::string path, T val, char lc = 'L', char rc = 'R');
    void insert_left_tree(const BinTree& lft_t);
    void insert_right_tree(const BinTree& rgt_t);
    void insert_spec_node(std::string path, T val, char lc = 'L', char rc = 'R');
    void release_self_node();
    void release_left_tree();
    void release_right_tree();
    // check atrribute function which is const function
    bool has_left_child()const{return this->lftChild != nullptr; }
    bool has_right_child()const{return this->rgtChild != nullptr; }
    uint count_node_number()const;
    uint depth()const;
    // display function: display the object on the screen as branch view
    void display(std::ostream& out)const;
  };

  template<class T>
  class Forest: public BinTree<T>{
  public:
    Forest(){};
    Forest(const BinTree<T>& bt);
  };
}

#include "BinTree.tpp"
#include "Forest.tpp"
