#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>
#include <list>
#include <algorithm> // std::sort

typedef unsigned int uint;

namespace Tree{
  template<class T>
  class BinTree{
  protected:
    T data = T(0);
    BinTree* lftChild = nullptr;
    BinTree* rgtChild = nullptr;
    // can't access specific node via non const method
    BinTree* node(std::string path, char lc = 'L', char rc = 'R');
  public:
    BinTree(){}
    BinTree(T ele): data(ele) {}
    BinTree(const BinTree& tree);
    ~BinTree(){ this->release_self_node(); }
    // query, update, insert, delete function.
    T get_self_data()const{ return this->data; }
    const BinTree* get_left_tree()const{ return this->lftChild; }
    const BinTree* get_right_tree()const{ return this->rgtChild; }
    const BinTree* get_spec_node(std::string path, char lc = 'L', char rc = 'R')const
      { return (const_cast<BinTree*>(this))->node(path, lc, rc); }

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
    void release_spec_node(std::string path, char lc = 'L', char rc = 'R');
    // traverse function: prev, mid and post order.
    std::list< BinTree<T> > get_all_node()const; // prev method.
    std::list<T> pre_order_traverse()const;
    std::list<T> mid_order_traverse()const;
    std::list<T> post_order_traverse()const;
    // check atrribute function which is const function
    bool has_left_child()const{return this->lftChild != nullptr; }
    bool has_right_child()const{return this->rgtChild != nullptr; }
    uint count_node_number()const;
    uint depth()const;
    // display function: display the object on the screen as branch view
    void display(std::ostream& out)const;

    struct data_less_than{
      inline bool operator() (const BinTree<T>& bt1, const BinTree<T>& bt2){ return bt1.data < bt2.data; }
    };
  };

  template<class T>
  class HuffmanTree: public BinTree<T>{
  private:
    std::list< BinTree<T> > tree_lst = {};
  public:
    HuffmanTree(){};
    HuffmanTree(const std::list< BinTree<T> >& lst): tree_lst(lst){ this->gnr_huffman_tree(); };
    HuffmanTree(const std::list<T>& lst);
    HuffmanTree(const HuffmanTree<T>& hft): BinTree<T>(hft){}
    HuffmanTree(const BinTree<T>& bt): BinTree<T>(bt){}
    ~HuffmanTree(){this->tree_lst.clear();}

    void gnr_huffman_tree();
    void gnr_huffman_tree(const BinTree<T>& bt);
    void gnr_mini_tree();
  };
}

#include "BinTree.tpp"
#include "HuffmanTree.tpp"
