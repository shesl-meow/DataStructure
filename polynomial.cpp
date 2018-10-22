#include "polynomial.h"
#include <sstream>
#include <iostream> //temp

template<class T>
Polynomial<T>& Polynomial<T>::merge(Polynomial<T> other)
{
	this->sort(), other.sort();
	this->std::list< Monomial<T> >::merge(other);
	return this->unique();
}

template<class T>
Polynomial<T>& Polynomial<T>::unique()
{
	this->sort();
	for(auto it = this->begin(), prev = it++; it != this->end(); ++it, ++prev)	
		if(Monomial<T>::similar(*prev, *it))
		{
			prev->coff += it->coff;
			this->erase(it++);
		}
	return *this;
}

template<class T>
Polynomial<T> Polynomial<T>::multiply(const Polynomial<T>& P1, const Polynomial<T>& P2)
{
	// FFT here. Too lazy to write.
	Polynomial<T> result;
	for(auto it = P1.begin(); it != P1.end(); ++it)
		for(auto jt = P2.begin(); jt != P2.end(); ++jt)
			result.push_back((*it) * (*jt));
	return result.unique();
}

template<class T>
Polynomial<T> Polynomial<T>::operator-()const
{
	Polynomial result = *this;
	for(auto it = result.begin(); it != result.end(); ++it) *it = -(*it);
	return result;
}

template<class T>
Polynomial<T>::operator std::string()const
{
	std::stringstream ss;
	auto it = this->begin();
	ss << std::string(*it);
	for(it++ ; it != this->end(); ++it)
		ss << (it->coff > 0 ? "+" : "") << std::string(*it);
	return ss.str();
}