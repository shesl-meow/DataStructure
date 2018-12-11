#include "Sort.h"

using namespace Sort;

template<class T>
void InsertSort<T>::sort(){
    assert(!this->is_sorted);
    for(uint i = 0; i < this->length; ++i){
        for(uint j = i; j > 0; --j){
            if(!this->compare(j-1, j))
                this->swap(j-1, j);
            else break;
        }
    }
    this->is_sorted = true;
}

template<class T>
std::ostream& operator << (std::ostream& out, InsertSort<T> bs){
    return bs.display(out);
}