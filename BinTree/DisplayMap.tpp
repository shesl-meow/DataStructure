#pragma once
#include <exception>
#include <stdexcept>
#include <sstream>
#include "BinTree.h"

typedef unsigned int uint;

namespace DisplayMap{
  DisplayMap::DisplayMap(std::string default_string){
    this->string_map = new std::string*[1];
    this->string_map[0] = new std::string[1];
    this->string_map[0][0] = default_string;
  }

  DisplayMap::DisplayMap(uint r, uint c, std::string dflt): row(r), column(c), default_string(dflt){
    this->string_map = new std::string*[r];
    for(uint i = 0; i < r; ++i){
      this->string_map[i] = new std::string[c];
      for(uint j = 0; j < c; ++j)
        string_map[i][j] = default_string;
    }
  }

  DisplayMap::DisplayMap(const DisplayMap& dm): 
    row(dm.row), column(dm.column), default_string(dm.default_string){
    this->string_map = new std::string*[this->row];
    for(uint i = 0; i < this->row; ++i){
      this->string_map[i] = new std::string[this->column];
      for(uint j = 0; j < this->column; ++j)
        string_map[i][j] = dm.string_map[i][j];
    }
  }

  DisplayMap::~DisplayMap(){
    for(uint i = 0; i < row; ++i) delete []this->string_map[i];
    delete []this->string_map;
  }

  void DisplayMap::resize(uint r, uint c){
    //std::cout << row << " x " << column << std::endl;
    for(uint i = 0; i < row; ++i) delete []this->string_map[i];
    delete []this->string_map;
    //std::cout << row << " x " << column << std::endl;
    this->string_map = new std::string*[r];
    for(uint i = 0; i < r; ++i){
      this->string_map[i] = new std::string[c];
      for(uint j = 0; j < c; ++j)
        this->string_map[i][j] = this->default_string;
    }
    //std::cout << r << " x " << c << std::endl;
    this->row = r, this->column = c;
  }

  void DisplayMap::set_map_row(uint r, std::string str){
    if(str.size() != this->column)
      throw std::length_error("Invalid string length when set map row.");
    for(uint j = 0; j < this->column; ++j)
      this->string_map[r][j] = str[j];
  }

  void DisplayMap::set_map_column(uint c, std::string str){
    if(str.size() != this->row)
      throw std::length_error("Invalid string length when set map column.");
    for(uint i = 0; i < this->row; ++i)
      this->string_map[i][c] = str[i];
  }

  void DisplayMap::set_sub_area(uint x, uint y, DisplayMap* submap){
    if(x + submap->row > row || y + submap->column > column)
      throw std::range_error("Request area out of range.");
    for(uint i = 0; i < submap->row; ++i)
      for(uint j = 0; j < submap->column; ++j)
        this->string_map[x + i][y + j] = submap->string_map[i][j];
  }

  DisplayMap::operator std::string()const{
    std::stringstream ss;
    //std::cout << "mm:" << this->string_map[this->row - 1][this->column - 1] << std::endl;
    for(uint i = 0; i < this->row; ++i){
      for(uint j = 0; j < this->column; ++j) ss << this->string_map[i][j];
      ss << std::endl;
    }
    //std::cout << "[1] Hello World!" << std::endl;
    //std::cout << ss.str() << std::endl;
    return ss.str();
  }

  template<class T>
  BinTreeMap<T>::BinTreeMap(const BinTree<T> *tree, std::string default_string):
      bind_tree(tree),
      DisplayMap(
        tree->count_node_number(),
        tree->depth()*2 - 1,
        default_string
      ){ this->draw(); }

  template<class T>
  void BinTreeMap<T>::draw(){
    BinTreeMap<T> *lft_map = nullptr, *rgt_map = nullptr;
    if(this->bind_tree->has_left_child()){
      lft_map = new BinTreeMap<T>(this->bind_tree->get_left_tree());
      lft_map->draw();
      this->set_sub_area(0, 2, lft_map);
    }
    if(this->bind_tree->has_right_child()){
      rgt_map = new BinTreeMap<T>(this->bind_tree->get_right_tree());
      rgt_map->draw();
      this->set_sub_area(lft_map->row + 1, 2, rgt_map);
    }
    this->root_row = (lft_map == nullptr) ? 0 : lft_map->row;
    std::stringstream ss;
    ss << this->bind_tree->get_self_node();

    // begin to draw the tree branch
    if(lft_map != nullptr)
    {
      this->string_map[lft_map->root_row][1] = "--";
      this->string_map[lft_map->root_row][0] = ".-";
      for(uint i = lft_map->root_row + 1; i < this->root_row; ++i)
        this->string_map[i][0] = std::string("| ");
      delete lft_map;
    }
    this->string_map[this->root_row][0] = ss.str();
    if(rgt_map != nullptr)
    {
      for(uint i = this->root_row + 1; i < rgt_map->root_row + this->root_row + 1; ++i)
        this->string_map[i][0] = std::string("| ");
      this->string_map[this->root_row + rgt_map->root_row + 1][0] = "'-";
      this->string_map[this->root_row + rgt_map->root_row + 1][1] = "--";
      delete rgt_map;
    }
  }
}

std::ostream& operator<<(std::ostream& out, DisplayMap::DisplayMap dp)
{
  return out << std::string(dp);
}

template<class T>
std::ostream& operator<<(std::ostream& out, DisplayMap::BinTreeMap<T> dm)
{
  return out << std::string(dm);
}