#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <map>
#include "Tree.h"

typedef unsigned int uint;

// used to display a string map
namespace Display{
	class DisplayMap{
	protected:
		std::string **string_map;
		uint row = 1, column = 1;
		const std::string default_string = "	";
	public:
		DisplayMap(std::string default_string = " ");
		DisplayMap(uint r, uint c, std::string dflt = "	");
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

	template<class T, uint degree>
	class BTreeMap: public DisplayMap{
	protected:
		const BTree<T, degree>* bind_tree = nullptr;
	public:
		BTreeMap(const BTree<T, degree>* tr);
		uint get_map_width()const{ return this->bind_tree->keywords_acount() + this->bind_tree->nodes_acount()*2; }
		uint get_map_depth()const{ return this->bind_tree->depth()*2 - 1;}
	};
}
