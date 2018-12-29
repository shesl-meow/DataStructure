#include "Sort.h"

using namespace Sort;

template<class T>
void QuickSort<T>::partialize(uint start, uint len, uint pivot){
    // pivot is relative shift from `start`
    assert(pivot < len);
    assert(start + len < this->length);

    uint init_pivot = pivot;
    for(uint i = 0; i < init_pivot; ++i){
        if(i == pivot) continue;
        if(!this->compare(start + i, start + pivot)){
            this->swap()
        }
    }
}

template<class T>
void QuickSort<T>::sort(){
    assert(!this->is_sorted);
    
    this->is_sorted = true;
}

template<class T>
std::ostream& operator << (std::ostream& out, QuickSort<T> ss){
    return ss.display(out);
}