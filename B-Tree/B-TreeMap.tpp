#include "Display.h"

template<class T, uint degree>
BTreeMap<T, degree>::BTreeMap(const BTree<T, degree>* tr): bind_tree(tr){
	auto wd = this->get_map_width();
	auto dp = this->get_map_depth();
	this->resize(wd, dp);

	
}
