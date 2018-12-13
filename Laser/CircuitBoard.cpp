#include "Display.h"
#include <cassert>
#include <iostream>

using namespace Display;

static inline bool is_blank(char c){
    return c == ' ' || c == '\n' || c == '\t';
}
static inline void assign(std::list<bool>& l,const std::list<bool>& r){
    l.clear();
    for(auto it = r.begin(); it != r.end(); ++it) l.push_back(*it);
}

bool operator==(const std::list<bool>& l, const std::list<bool>& r){
    if(l.size() != r.size()) return false;
    for(auto i = l.begin(), j = r.begin(); i != l.end() && j != r.end(); i++, j++){
        if(*i != *j) return false;
    }
    return true;
}


void CircuitBoard::interactive_init()
{
    std::string msg = "Assign the initial map where\n"
        "- `0` stand for disconduct of circuit board.\n"
        "- `1` stand for conduct of circuit board.\n"
        "- any illegal input will end input.\n";
    std::cout << msg;
    std::string line;
    uint width = 0, height = 0;
    std::list< std::list<bool> > llst;
    while(true){
        getline(std::cin, line);
        for(auto ch = line.begin(); ch != line.end();){
            if(is_blank(*ch)) line.erase(ch);
            else ch++;
        }
        if(width == 0) width = line.size();
        else height++;

        std::list<bool> lst;
        for(auto ch = line.begin(); ch != line.end(); ++ch){
            if(*ch == '0') lst.push_back(false);
            else if(*ch == '1') lst.push_back(true);
            else goto INIT_EXIT1;
        }
        llst.push_back(lst);
    }
INIT_EXIT1:
    std::cout << "You provide a " << height << "*" << width << " circuit board";
    this->set_circuit(llst);
    std::cout << std::string(*this);

    std::cout << "Please provided the laser size:";
    std::cin >> this->laser_size;
    while(this->laser_size > this->get_column_size()){
        std::cout << "Your column size is " << this->get_column_size() << std::endl;
        std::cout << "Please specify a number smaller or equal than it:";
        std::cin >> this->laser_size;
    }
}

std::list<uint> CircuitBoard::potential_lines()const{
    std::list<uint> res;
    for(uint i = 0; i < this->get_row_size(); ++i){
        uint zero_acount = 0;
        for(auto j = 0; j < this->get_column_size(); ++j){
            zero_acount += uint(this->disc_string == this->string_map[i][j]);
        }
        if(zero_acount > laser_size) continue;
        if((laser_size - zero_acount)%2 == 1) continue;
        res.push_back(i);
    }
    return res;
}

std::list<bool> CircuitBoard::mode_data(std::list<uint> range)const{
    assert(range.size() > 0);

    std::map<std::list<bool>, uint> occ_times;
    for(auto i: range){
        std::list<bool> row = {};
        for(uint j = 0; j < this->get_column_size(); ++j){
            if(this->string_map[i][j] == this->disc_string) row.push_back(false);
            else if(this->string_map[i][j] == this->cond_string) row.push_back(true);
            else assert(false);
        }

        auto it = occ_times.begin();
        for(;it != occ_times.end(); ++it)
            if(it->first == row) break;
        if(it == occ_times.end()) occ_times[row] = 1;
        else it->second++;
    }

    uint mode = 0;
    std::list<bool> data;
    for(auto it = occ_times.begin(); it != occ_times.end(); it++){
        if(mode < it->second) mode = it->second, assign(data, it->first);
    }
    assert(data.size() == this->get_column_size());
    return data;
}

void CircuitBoard::set_circuit(std::list< std::list<bool> > state_llst){
    this->resize(state_llst.size(), state_llst.begin()->size());

    uint r_pos = 0, c_pos = 0;
    for(auto s_lst = state_llst.begin(); s_lst != state_llst.end(); ++s_lst, ++r_pos){
        assert(r_pos < this->get_row_size());
        assert(s_lst->size() == this->get_column_size());
        for(auto s = s_lst->begin(); s != s_lst->end(); ++s, ++c_pos){
            this->string_map[r_pos][c_pos] = *s ? (this->cond_string) : (this->disc_string);
        }
        c_pos = 0;
    }  
}

void CircuitBoard::emit_laser(std::list<bool> laser){
    uint i = 0, j = 0;
    for(auto atom = laser.begin(); atom != laser.end(); ++atom, ++j){
        for(i = 0; i < this->get_row_size(); ++i){
            bool next = (*atom) ^ (this->string_map[i][j] == this->cond_string);
            this->string_map[i][j] = next ? this->cond_string : this->disc_string;
        }
    }
}

uint CircuitBoard::conduct_rows()const{
    uint acount = 0;
    for(uint i = 0; i < this->get_row_size(); ++i){
        bool flag = true;
        for(uint j = 0; j < this->get_column_size(); ++j){
            if(this->string_map[i][j] == this->cond_string) continue;
            if(this->string_map[i][j] == this->disc_string){
                flag = false; break;
            }
            assert(false);
        }
        if(flag) acount++;
    }
    return acount;
}

std::list<uint> CircuitBoard::get_row(std::function<bool(std::list<bool>, uint l_num)> condition)const{
    std::list<uint> res;
    for(uint i = 0; i < this->get_row_size(); ++i){
        std::list<bool> line;
        for(uint j = 0; j < this->get_column_size(); ++j){
            if(this->string_map[i][j] == this->cond_string)
                line.push_back(true);
            else if(this->string_map[i][j] == this->disc_string)
                line.push_back(false);
            else assert(false);
        }
        if(condition(line, i)) res.push_back(i);
    }
    return res;
}