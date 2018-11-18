#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <map>
#include "Tree.h"
#include "Coding.h"

typedef unsigned int uint;

// used to display a string map
namespace Display{
  class DisplayMap{
  protected:
    std::string **string_map;
    uint row = 1, column = 1;
    const std::string default_string = "  ";
  public:
    DisplayMap(std::string default_string = "0");
    DisplayMap(uint r, uint c, std::string dflt = "  ");
    DisplayMap(const DisplayMap& dm);
    ~DisplayMap();
    uint get_row_size()const{ return this->row; }
    uint get_column_size()const{ return this->column; }
    void resize(uint r, uint c);
    void set_map_node(uint r, uint c, std::string data){ this->string_map[r][c] = data; }
    void set_map_row(uint r, std::string str);
    void set_map_column(uint c, std::string str);
    void set_sub_area(uint x, uint y, DisplayMap* submap); // x,y is the left upper point
    operator std::string()const;
  };

  template<class T>
  class BinTreeMap: public DisplayMap{
  protected:
    uint root_row = 0;
    const Tree::BinTree<T> * bind_tree = nullptr;
  public:
    BinTreeMap(const Tree::BinTree<T> *tree, std::string default_string = "  ");
    ~BinTreeMap(){}
    uint get_map_width()const{ return this->bind_tree->count_node_number(); }
    uint get_map_depth()const{ return this->bind_tree->depth()*2 - 1; }
    void draw();
    friend class CodingMap;
  };

  class CodingMap: public BinTreeMap<uint>{
  protected:
    const std::map<char, const Tree::BinTree<uint>*>* bind_char_nodes;
  public:
    CodingMap(const Tree::BinTree<uint> *tree,
      const std::map<char, const Tree::BinTree<uint>*>* char_nodes,
      std::string default_string = "  ");
    CodingMap(const Coding::HuffmanCoding* code, std::string default_string = "  "):
      BinTreeMap(code->get_coding_tree(), default_string), bind_char_nodes(code->get_char_nodes())
      { this->draw(); }
    
    void draw();
  };
}
