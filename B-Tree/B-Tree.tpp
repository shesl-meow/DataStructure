#include "Tree.h"

template<class T, uint degree>
void BTree<T, degree>::split_self(){
	// mid is the postion where to split
	auto mid = this->data.begin();
	advance(mid, degree - 1);

	if(this->is_root_node()){
		// create a parent node and set its value equal to mid
		this->parent = new BTree(*mid);
		this->parent->children.push_back(this);

		// create a new brother node which contain value lower than mid
		BTree* new_tr = new BTree(this->data.begin(), mid);
		this->parent->children.push_front(new_tr);
	}else{
		auto i = this->parent->data.begin();
		auto j = this->parent->children.begin();
		// shift to the position where self node in the family
		for(;*i < *mid || i != this->parent->data.end(); ++i, ++j);

		// insert the mid to corrsponding postion
		this->parent->data.insert(i, *mid);

		// create a new brother node which contain value lower than mid
		BTree* new_tr = new BTree(this->data.begin(), mid);
		this->parent->children.insert(j, new_tr);
	}

	// erase the self node data from the begin to mid
	this->data.erase(this->data.begin(), mid);
	auto mid_c = this->children.begin();
	advance(mid_c, degree - 1);
	this->children.erase(this->children.begin(), mid_c);
}

template<class T, uint degree>
BTree<T, degree>::BTree(T val){
	this->data.push_back(val);
	for(auto i: {0,1})
		this->children.push_back(nullptr);
}


template<class T, uint degree>
list<T> BTree<T, degree>::traverse()const{
	// terminated condition: this is a leaf node
	if(this->is_leaf_node()) return this->data;

	auto i = this->data.begin();
	auto j = this->children.begin();
	// traverse the first child tree
	list<T> res = (*j)->traverse();
	// begin with the first data node =>
	// traverse the node and its next node tree in order
	for(++j; i != this->data.end(); ++j, ++i){
		res.push_back(*i);
		auto tr = (*j)->traverse();
		res.insert(res.end(), tr.begin(), tr.end());
	}
	return res;
}

template<class T, uint degree>
bool BTree<T, degree>::is_leaf_node()const{
	if(this->children.size() == 0) return true;
	for(auto i: this->children) if(i != nullptr) return false;
	return true;
}

template<class T, uint degree>
uint BTree<T, degree>::nodes_acount()const{
	uint acount = 1;
	for(auto i: this->children){
		if(i == nullptr) continue;
		else acount += i->nodes_acount();
	}
	return acount;
}

template<class T, uint degree>
uint BTree<T, degree>::keywords_acount()const{
	uint acount = this->data.size();
	for(auto i: this->children){
		if(i == nullptr) continue;
		else acount += i->keywords_acount();
	}
}

template<class T, uint degree>
uint BTree<T, degree>::depth()const{
	// we have: all the leaf node are at the same level
	// 		so the depth to the first node is exactly the tree depth
	for(auto i: this->children){
		if(i == nullptr) continue
		return i->depth() + 1;
	}
	return 1;
}

template<class T, uint degree>
void BTree<T, degree>::insert(const T& val){
	while(this->data.size() >= 2*degree - 1) this->split_self();

	// find the corresponding position
	auto i = this->data.begin();
	auto j = this->children.begin();
	for(;i != this->data.end(); ++i, ++j) if(*i > val) break;

	if(this->is_leaf_node()){
		this->data.insert(i, val);
		this->children.insert(j, nullptr);
	}else (*j)->insert(val);
}

template<class T, uint degree>
BTree<T, degree>* BTree<T, degree>::search(const T& val)const{
	auto i = this->data.begin();
	auto j = this->children.begin();
	for(;i != this->data.end(); ++i)
		if(*i < val) ++j; else break;

	if(*i == val) return this;
	if(this->is_leaf_node()) return NULL;

	return (*j)->search(val);
}


template<class T, uint degree>
BTree<T, degree>::operator string()const{
	auto trv = this->traverse();
	string res;
	for(auto i = trv.begin(); i != trv.end(); ++i)
		res += string(*i);
	return res;
}
