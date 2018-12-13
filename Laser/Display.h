#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <map>
#include <list>
#include <functional>

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

  class CircuitBoard: public DisplayMap{
  private:
    std::string cond_string = "#";  // indicate conduction uint
    std::string disc_string = "=";  // indicate dis conduction uint
    uint laser_size = 0;
  public:
    CircuitBoard(){}
    CircuitBoard(std::list< std::list<bool> > sll){ this->set_circuit(sll); }

    void interactive_init();
    void set_circuit(std::list< std::list<bool> > state_llst);
    std::list<uint> potential_lines()const;
    std::list<bool> mode_data(std::list<uint> range)const;
    void emit_laser(std::list<bool> laser);
    uint conduct_rows()const;

    std::list<uint> get_row(std::function<bool(std::list<bool>, uint l_num)> condition)const;
    //std::list<uint> get_column(std::function<bool(std::list<bool>)> condition)const;
  };
}
