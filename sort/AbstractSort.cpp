#include "Sort.h"
#include <cassert>
using namespace Sort;

template<class T>
inline bool AbstractSort<T>::compare(uint index1, uint index2)const{
    // we assert index2 is bigger than index1
    //      exp: return false if index1>index2 and sort is ascend.
    assert(index1 < length && index2 < length);
    assert(index2 > index1);
    if(this->is_ascend) return (this->src_list[index2] >= this->src_list[index1]);
    else return (this->src_list[index2] <= this->src_list[index1]);
}

template<class T>
inline void AbstractSort<T>::swap(uint index1, uint index2){
    assert(index1 < length && index2 < length);
    auto tmp = this->src_list[index1];
    this->src_list[index1] = this->src_list[index2];
    this->src_list[index2] = tmp;
}

template<class T>
std::ostream& AbstractSort<T>::display(std::ostream& out)const{
    for(uint i = 0; i < this->length; ++i)
        out << this->src_list[i] << " ";
    return out << std::endl;
}