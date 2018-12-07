#pragma once
using namespace Display;

typedef unsigned int uint;

DisplayMap::DisplayMap(std::string default_string): default_string(default_string){
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
  ss << std::endl;
  for(uint i = 0; i < this->row; ++i){
    for(uint j = 0; j < this->column; ++j) ss << this->string_map[i][j];
    ss << std::endl;
  }
  return ss.str();
}

std::ostream& operator<<(std::ostream& out, Display::DisplayMap dp)
{
  return out << std::string(dp);
}
