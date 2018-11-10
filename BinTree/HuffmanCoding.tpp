#pragma once
#include "Display.h"

using namespace Coding;
typedef unsigned int uint;

void HuffmanCoding::count_char_times()
{
  this->char_times.clear();
  for(auto c = this->text.begin(); c != this->text.end(); ++c)
    this->char_times[*c] += 1;
}

void HuffmanCoding::gnr_coding_tree()
{
  std::list<uint> data_lst = {};
  for(auto p = this->char_times.begin(); p != this->char_times.end(); ++p)
    data_lst.push_back(p->second);
  this->coding_tree.convert_from_list(data_lst);
}

void HuffmanCoding::link_char_nodes()
{
  auto leaf_lst = this->coding_tree.get_leaf_nodes();
  for(auto cp = this->char_times.begin(); cp != this->char_times.end(); ++cp)
  {
    for(auto leaf = leaf_lst.begin(); leaf != leaf_lst.end(); ++leaf)
      if((*leaf)->get_self_data() == cp->second){
        this->char_nodes[cp->first] = *leaf;
        leaf_lst.erase(leaf);
        break;
      }
  }
}

void HuffmanCoding::init_coding_tree()
{
  this->count_char_times();
  this->gnr_coding_tree();
  this->link_char_nodes();
}

void HuffmanCoding::encode(char left, char right)
{
  std::string encode_text = "";
  this->init_coding_tree();
  for(auto c = this->text.begin(); c != this->text.end(); ++c)
  {
    const BinTree<uint>* node = this->char_nodes.find(*c)->second;
    std::string rev_encode = "";
    while( !(node->is_root_node()) )
    {
      if(node->is_left_child()) rev_encode += left;
      else if(node->is_right_child()) rev_encode += right;
      node = node->get_parent_tree();
    }
    std::reverse(rev_encode.begin(), rev_encode.end());
    encode_text += rev_encode;
  }
  this->assign_text(encode_text);
}

void HuffmanCoding::decode(char left, char right)
{
  std::string decode_text = "";
  const BinTree<uint>* node = this->coding_tree.get_spec_node("");
  for(auto c = this->text.begin(); c != this->text.end(); ++c)
  {
    if(*c == left) node = node->get_left_tree();
    else if(*c == right) node = node->get_right_tree();
    else{
      throw std::logic_error("Illegal character when decode.");
      return;
    }

    if(node->is_leaf_node())
      for(auto iter = this->char_nodes.begin(); iter != this->char_nodes.end(); ++iter)
        if(iter->second == node){
          decode_text += iter->first;
          node = this->coding_tree.get_spec_node("");
        }
  }
  this->assign_text(decode_text);
}

std::string HuffmanCoding::read_coding_tree()const
{
  return std::string(Display::CodingMap(this));
}

std::string HuffmanCoding::read_char_times()const
{
  std::stringstream ss;
  ss << std::endl << std::string(this->char_times.size()*8, '-') + '-' << std::endl;
  for(auto it = this->char_times.begin(); it != this->char_times.end(); ++it)
  {
    if(it->first == '\n') ss << "|\\n\t";
    else if(it->first == ' ') ss << "|[ ]\t";
    else ss << "|" << it->first << "\t";
  }
  ss << "|" << std::endl;
  for(auto it = this->char_times.begin(); it != this->char_times.end(); ++it)
    ss << "|" << it->second << "\t";
  ss << "|" << std::endl;
  ss << std::string(this->char_times.size()*8, '-') + '-' << std::endl;
  return ss.str();
}
