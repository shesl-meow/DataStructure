#include "Sort.h"

using namespace Sort;

template<class T>
void SelectionSort<T>::sort(){
    for(uint i = 0; i < this->length; ++i){
        uint next_pos = i;
        for(uint j = i + 1; j < this->length; ++j){
            if(!this->compare(next_pos, j)) next_pos = j;
        }
        if(next_pos != i) this->swap(i, next_pos);
    }
}

template<class T>
std::ostream& operator << (std::ostream& out, SelectionSort<T> ss){
    return ss.display(out);
}