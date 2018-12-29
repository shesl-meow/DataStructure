#include "Sort.h"

using namespace Sort;

template<class T>
inline void ShellSort<T>::generate_seq(){
    uint next = this->length;
    while(next > 1){
        next = this->forward_f(next);
        this->sequence.push_back(next);
    }
}

template<class T>
inline void ShellSort<T>::sort_block(uint beg, uint step){
	assert(beg + step < this->length);
	for(uint i = beg + step; i < this->length; i += step){
		for(uint j = i; j >= beg + step; j -= step){
			if(!this->compare(j-step, j)){
				this->swap(j-step, j);
				if(this->debug) this->display(std::cout);
			}else break;
		}
	}
}

template<class T>
void ShellSort<T>::sort(){
    assert(!this->is_sorted);
    this->generate_seq();

	if(this->debug){
		std::cout << this->sequence.size() << std::endl;
		for(auto ch: this->sequence) std::cout << ch << " ";
		std::cout << std::endl;
	}

    for(auto ch: this->sequence){
		for(uint beg = 0; beg < ch; beg++){
			this->sort_block(beg, ch);
		}
    }
    this->is_sorted = true;
}

template<class T>
std::ostream& operator << (std::ostream& out, ShellSort<T> bs){
    return bs.display(out);
}
