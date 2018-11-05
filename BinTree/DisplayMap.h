#pragma once
#include <string>
#include <iostream>
#include "BinTree.h"

typedef unsigned int uint;

// used to display a string map
namespace DisplayMap{
  class DisplayMap{
  protected:
    std::string **string_map;
    uint row = 1, column = 1;
    const std::string default_string = "  ";
  public:
    DisplayMap(std::string default_string = "0");
    DisplayMap(uint r, uint c, std::string dflt = "  ");
    ~DisplayMap();
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
    const BinTree<T> * bind_tree = nullptr;
  public:
    BinTreeMap(const BinTree<T> *tree, std::string default_string = "  ");
    uint get_map_width()const;
    uint get_map_depth()const{ return this->bind_tree->depth()*2 - 1; }
    void draw()const;
  };
}

#include "DisplayMap.tpp"
