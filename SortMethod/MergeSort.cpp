#include "Sort.h"
#include <cassert>

using namespace Sort;

template<class T>
inline void MergeSort<T>::merge(uint start1, uint len1, uint start2, uint len2)
{
    assert(start1 + len1 <= start2);
    assert(start2 + len2 <= this->length);
    T* merge_result = new T[len1 + len2];
    for(uint i = 0, j = 0; i < len1 || j < len2;)
    {
        if(i != len1 && (j == len2 || this->compare(start1 + i, start2 + j)))
            merge_result[i + j] = this->src_list[start1 + i], i++;
        else merge_result[i + j] = this->src_list[start2 + j], j++;
    }

    this->assign(start1, len1, merge_result);
    this->assign(start2, len2, merge_result + len1);
    delete []merge_result;
}

template<class T>
void MergeSort<T>::sort(){
    for(uint i = 1; i < this->length; i *= 2){
        for(uint pr = 0; /*step < this->length*/; pr += i*2){
            if(pr + i*2 < this->length){
                this->merge(pr, i, pr + i, i);
                continue;
            }
            if(pr + i < this->length)
                this->merge(pr, i, pr + i, this->length - pr - i);
            break;
        }
    }
}

template<class T>
std::ostream& operator << (std::ostream& out, MergeSort<T> bs){
    return bs.display(out);
}