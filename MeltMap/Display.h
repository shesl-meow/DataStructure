#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <map>
#include <list>

typedef unsigned int uint;

// used to display a string map
namespace Display{
  struct Point{
    uint x = 0;
    uint y = 0;
  };

  class DisplayMap{
  protected:
    std::string **string_map;
    uint row = 1, column = 1;
    const std::string default_string = "  ";
  public:
    DisplayMap(std::string default_string = "  ");
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

  class MeltMap: public DisplayMap{
  protected:
    std::string water_string = "=", metal_string = "#";
    // blank_symbol is the default_string
  public:
    MeltMap(): DisplayMap(" "){}
    MeltMap(std::string metal){ this->Init(metal); }
    void Init(std::string metal); // init
    // init with a list of list of boolen where true stand for metal
    void Init(std::list< std::list<bool> > bl_llst);
    void Fill(); // fill water from the edge
    void Melt(); // melt the metal once

    bool has_water()const;
    bool has_metal()const;
    uint metal_block_acount()const;
  };
}
