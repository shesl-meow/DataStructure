#include "Sort.h"

using namespace Sort;

template<class T>
void BubbleSort<T>::sort(){
    assert(!this->is_sorted);
    for(uint i = this->length; i > 1; i--){
        for(uint j = 0; j < i - 1; ++j){
            if(!this->compare(j, j+1))
                this->swap(j, j+1);
        }
    }
    this->is_sorted = true;
}

template<class T>
std::ostream& operator << (std::ostream& out, BubbleSort<T> bs){
    return bs.display(out);
}