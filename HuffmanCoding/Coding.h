#pragma once
#include<string>
#include<map>
#include<algorithm>
#include<exception>
#include<sstream>
#include "Tree.h"

typedef unsigned int uint;

namespace Coding{
  class AbstractCoding{
  protected:
    std::string text = "";
  public:
    AbstractCoding(){}
    AbstractCoding(const std::string& str): text(str){}
    void assign_text(std::string str){ this->text = str; }
    std::string read_text()const{ return this->text; }
    virtual void encode(char zero, char one) = 0;
    virtual void decode(char zero, char one) = 0;
  };

  class HuffmanCoding: public AbstractCoding{
  private:
    void count_char_times();
    void gnr_coding_tree();
    void link_char_nodes();
  protected:
    std::map<char, uint> char_times;
    Tree::HuffmanTree<uint> coding_tree;
    std::map<char, const Tree::BinTree<uint>* > char_nodes;
  public:
    void init_coding_tree();
    HuffmanCoding(){}
    HuffmanCoding(const std::string& str): AbstractCoding(str){ this->init_coding_tree(); }

    void encode(char left='0', char right='1') override;
    void decode(char left='0', char right='1') override;

    const Tree::HuffmanTree<uint>* get_coding_tree()const{ return &(this->coding_tree); }
    const std::map<char, const Tree::BinTree<uint>* >* get_char_nodes()const{ return &(this->char_nodes);}
    std::string read_coding_tree()const;
    std::string read_char_times()const;
  };
}
