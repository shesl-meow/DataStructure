#include "Sort.h"

using namespace Sort;

template<class T>
inline void ShellSort<T>::generate_seq(){
    uint next = 1;
    while(next < this->length){
        this->sequence.push_front(next);
        next = this->forward_f(next);
    }
}

template<class T>
void ShellSort<T>::sort(){
    assert(!this->is_sorted);
    this->generate_seq();
    for(auto ch: this->sequence){
        for(uint i = 0; i < this->length; i += ch){
            for(uint j = i; j > 0; j -= ch){
                if(!this->compare(j - ch, j))
                    this->swap(j - ch, j);
                else break;
            }
        }
    }
    this->is_sorted = true;
}

template<class T>
std::ostream& operator << (std::ostream& out, ShellSort<T> bs){
    return bs.display(out);
}