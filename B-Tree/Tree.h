#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>
#include <list>
#include <algorithm> // std::sort

typedef unsigned int uint;
using namespace std;

template<class T, uint degree>
class BTree{
private:
	void split_self();

protected:
	BTree* parent = nullptr;
	// always satisfy `children.size() = data.size() + 1`
	list<BTree*> children;
	list<T> data;
public:
	BTree(){ this->children.push_back(nullptr); }
	BTree(T val);
	BTree(initializer_list<T> l) { for(auto i: l) this->insert(i); }
	template<class InputIt>
	BTree(InputIt l, InputIt r) { for(auto i = l; i != r; ++i) this->insert(*i); }

	list<T> traverse()const;
	BTree* search(const T& val)const;
	void insert(const T& val);

	// public property method
	bool is_leaf_node()const;
	bool is_root_node()const{ return this->parent == nullptr; }
	uint data_width()const{ return this->data.size(); }
	uint nodes_acount()const;
	uint keywords_acount()const;
	uint depth()const;

	// cast operator
	operator string()const;

	friend class BTreeMap<T, degree>;
};

