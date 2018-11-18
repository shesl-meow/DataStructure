#pragma once
using namespace Display;
typedef unsigned int uint;

CodingMap::CodingMap(const Tree::BinTree<uint> *tree,
  const std::map<char, const Tree::BinTree<uint>*>* char_nodes,
  std::string default_string):
    BinTreeMap(tree, default_string),
    bind_char_nodes(char_nodes)
  { this->draw(); }

void CodingMap::draw()
{
  BinTreeMap<uint> *lft_map = nullptr, *rgt_map = nullptr;
  if(this->bind_tree->has_left_child()){
    lft_map = new CodingMap(this->bind_tree->get_left_tree(), this->bind_char_nodes);
    this->set_sub_area(0, 2, lft_map);
  }
  if(this->bind_tree->has_right_child()){
    rgt_map = new CodingMap(this->bind_tree->get_right_tree(), this->bind_char_nodes);
    this->set_sub_area(lft_map->row + 1, 2, rgt_map);
  }
  this->root_row = (lft_map == nullptr) ? 0 : lft_map->row;
  std::stringstream ss;
  ss << this->bind_tree->get_self_data();
  if(this->bind_tree->is_leaf_node())
  {
    for(auto it = this->bind_char_nodes->begin(); it != this->bind_char_nodes->end(); ++it)
      if(it->second == this->bind_tree){
        if(it->first == '\n') ss << ": \\n";
        else if(it->first == ' ') ss << ": [blank]";
        else if(it->first == '\t') ss << ": \\t";
        else ss << ": " << it->first;
        break;
      }
  }

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
