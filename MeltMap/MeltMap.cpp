#include "Display.h"
#include <utility>
using namespace Display;

// the input string should end with '\n' instead of '\n\r'
void MeltMap::Init(std::string mmp){
  uint max_width = 0, max_depth = 0, cur_width = 0;
  for(auto i: mmp){
    if(i != '\n') cur_width += 1;
    else{
      max_width = (max_width > cur_width) ? max_width : cur_width;
      max_depth += 1, cur_width = 0;
    }
  }
  this->resize(max_depth, max_width);

  uint dp = 0, wd = 0;
  for(auto i: mmp){
    if(i == '\n') dp += 1, wd = 0;
    else this->string_map[dp][wd] = i, wd += 1;
  }
}

void MeltMap::Init(std::list< std::list<bool> > bl_llst){
  uint max_width = 0;
  auto max_depth = bl_llst.size();
  for(auto lst: bl_llst)
    max_width = (max_width > lst.size()) ? max_width : lst.size();
  this->resize(max_depth, max_width);

  uint i = 0, j = 0;
  for(auto bl_lst = bl_llst.begin(); bl_lst != bl_llst.end(); bl_lst++, i++, j=0){
    for(auto bl = bl_lst->begin(); bl != bl_lst->end(); bl++, j++){
      if(*bl) this->string_map[i][j] = this->metal_string;
      else this->string_map[i][j] = this->default_string;
    }
  }
}

void MeltMap::Fill(){
  std::list< std::pair<uint, uint> > fill_queue;
  uint r = this->get_row_size(), c = get_column_size();
  bool **is_travered = new bool*[r];
  for(int i = 0; i < r; i++){
    is_travered[i] = new bool[c];
    for(int j = 0; j < c; j++) is_travered[i][j] = false;
  }

  // the initial state of queue is set to be all the edges
  for(uint i = 0; i < c; ++i){
    fill_queue.push_back(std::make_pair(0, i));
    fill_queue.push_back(std::make_pair(r - 1, i));
  }
  for(uint i = 0; i < r; ++i){
    fill_queue.push_back(std::make_pair(i, 0));
    fill_queue.push_back(std::make_pair(i, c - 1));
  }
  // remove the pair from the queue if it is a metal
  for(auto q = fill_queue.begin(); q != fill_queue.end(); q++){
    is_travered[q->first][q->second] = true;
    if(this->string_map[q->first][q->second] == this->metal_string) fill_queue.erase(q);
  }
  // begin to fill all the posible position
  while(!fill_queue.empty()){
    auto to_fill = fill_queue.front();
    fill_queue.pop_front();
    uint i = to_fill.first, j = to_fill.second;
    this->string_map[i][j] = this->water_string;

    std::list< std::pair<uint, uint> > around =
      {{i-1, j}, {i+1, j}, {i, j+1}, {i, j-1}};
    for(auto pr: around){
      auto f = pr.first, s = pr.second;
      if(f>=0 && f<r && s>=0 && s<c)
        if(!is_travered[f][s] && (this->string_map[f][s] != this->metal_string)){
          fill_queue.push_back(pr);
          is_travered[f][s] = true;
        }
    }
  }
  for(int i = 0; i < r; ++i) delete []is_travered[i];
  delete []is_travered;
}

void MeltMap::Melt(){
  std::list< std::pair<uint, uint> > melt_pos;
  uint r = this->get_row_size(), c = get_column_size();

  for(uint i = 0; i < r; ++i){
    for(uint j = 0; j < c; ++j){
      if(this->string_map[i][j] != this->metal_string) continue;

      uint count = 0;
      std::list< std::pair<uint, uint> > around =
        {{i-1, j}, {i+1, j}, {i, j+1}, {i, j-1}};
      for(auto pr: around){
        auto f = pr.first, s = pr.second;
        if(f>=0 && f<r && s>=0 && s<c){
          if(this->string_map[f][s] == this->water_string) count += 1;
        }
      }

      if(count >= 2) melt_pos.push_back(std::make_pair(i, j));
    }
  }
  // begin to melt
  for(auto p: melt_pos)
    this->string_map[p.first][p.second] = this->water_string;

  this->Fill();
}

bool MeltMap::has_water()const{
  for(uint i = 0; i < this->get_row_size(); ++i)
    for(uint j = 0; j < this->get_column_size(); ++j)
      if(this->string_map[i][j] == this->water_string) return true;
  return false;
}

bool MeltMap::has_metal()const{
  for(uint i = 0; i < this->get_row_size(); ++i)
    for(uint j = 0; j < this->get_column_size(); ++j)
      if(this->string_map[i][j] == this->metal_string) return true;
  return false;
}

uint MeltMap::metal_block_acount()const{
  uint acount = 0;
  for(uint i = 0; i < this->get_row_size(); ++i)
    for(uint j = 0; j < this->get_column_size(); ++j)
      if(this->string_map[i][j] == this->metal_string) acount++;
  return acount;
}
