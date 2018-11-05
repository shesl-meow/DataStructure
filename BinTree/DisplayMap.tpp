#pragma once
#include <exception>
#include <sstream>

static inline uint fast_pow(uint base, uint power){
  uint res=1;
  while( power ){
    if( power&1 ) res *= base;
    base *= base; power >>= 1;
  }
  return res;
}

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

  DisplayMap::~DisplayMap(){
    for(uint i = 0; i < row; ++i) delete this->string_map[i];
    delete this->string_map;
  }

  void DisplayMap::resize(uint r, uint c){
    for(uint i = 0; i < row; ++i) delete this->string_map[i];
    delete this->string_map;
    this->string_map = new std::string*[r];
    for(uint i = 0; i < r; ++i) this->string_map[i] = new std::string[c];
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
    if(x + submap->row >= row || y + submap->column >= column)
      throw std::range_error("Request area out of range.");
    for(uint i = 0; i < submap->row; ++i)
      for(uint j = 0; j < submap->column; ++j)
        this->string_map[x + i][y + j] = submap->string_map[i][j];
  }

  DisplayMap::operator std::string()const{
    std::stringstream ss;
    for(uint i = 0; i < this->row; ++i){
      for(uint j = 0; j < this->column; ++j) ss << this->string_map[i][j];
      ss << std::endl;
    }
    return ss.str();
  }

  template<class T>
  BinTreeMap<T>::BinTreeMap(const BinTree<T> *tree, std::string default_string):
    bind_tree(tree), DisplayMap(this->get_map_width(), this->get_map_depth(), default_string){}

  template<class T>
  uint BinTreeMap<T>::get_map_width()const{
    uint lw = 0, rw = 0;
    if(this->bind_tree->has_left_child())
      lw = BinTreeMap<T>(this->bind_tree->get_left_tree()).row;
    if (this->bind_tree->has_right_child())
      rw = BinTreeMap<T>(this->bind_tree->get_right_tree()).row;
    return lw + rw + 1;
  }

  template<class T>
  void BinTreeMap<T>::draw()const{
    BinTreeMap<T> *lft_map = nullptr, *rgt_map = nullptr;
    if(this->bind_tree->has_left_child()){
      lft_map = new BinTreeMap<T>;
      *lft_map = BinTreeMap<T>(*(this->bind_tree->get_left_tree));
      lft_map->draw();
      this->set_sub_area(0, 2, lft_map);
    }
    if(this->bind_tree->has_right_child()){
      rgt_map = new BinTreeMap<T>;
      *rgt_map = BinTreeMap<T>(*(this->bind_tree->get_right_tree));
      rgt_map->draw();
      this->set_sub_area(0, 2, rgt_map);
    }
    this->root_row = (lft_map == nullptr) ? 0 : lft_map->row;
    std::stringstream ss;
    ss << this->bind_tree->data;

    // begin to draw the tree branch
    if(lft_map != nullptr)
    {
      this->string_map[lft_map->root_row][1] = "--";
      this->string_map[lft_map->root_row][0] = ".";
      for(uint i = lft_map->root_row + 1; i < this->root_row; ++i)
        this->string_map[i][0] = std::string("|");
      delete lft_map;
    }
    this->string_map[this->root_row][0] = ss.str();
    if(rgt_map != nullptr)
    {
      for(uint i = this->root_row + 1; i < rgt_map->root_row + this->root_row; ++i)
        this->string_map[i][0] = std::string("|");
      this->string_map[this->root_row + rgt_map->root_row + 1][0] = "'";
      this->string_map[this->root_row + rgt_map->root_row + 1][1] = "--";
      delete rgt_map;
    }
  }
}

std::ostream& operator<<(std::ostream& out, DisplayMap::DisplayMap dp)
{
  return out << std::string(dp);
}
