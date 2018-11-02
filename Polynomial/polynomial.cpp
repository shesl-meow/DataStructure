#include "polynomial.h"
#include <sstream>
#include <iostream> //temp
#include <stdexcept>

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
	for(auto it = this->begin(); it != this->end(); ++it)
		if(it->coff == 0) this->erase(it++);
	return *this;
}

template<class T>
Polynomial<T> Polynomial<T>::diff() const
{
	Polynomial<T> result;
	for(auto it = this->begin(); it != this->end(); ++it)
	{
		if(it->power == 0) continue;
		else
		{
			Monomial<T> temp(it->coff * it->power, it->power - 1);
			result.push_back(temp);
		}
	}
	return result;
}

template<class T>
inline int Polynomial<T>::power() const
{
	int max_power = this->bengin()->power;
	for(auto it = this->begin(); it != this->end(); it++)
		if( max_power < it->power ) max_power = it->power;
	return max_power;
}

template<class T>
inline int Polynomial<T>::mini_power() const
{
	int min_power = this->begin()->power;
	for(auto it = this->begin(); it != this->end(); it++)
		if( min_power > it->power ) min_power = it->power;
	return min_power;
}

template<class T>
inline Monomial<T> Polynomial<T>::power_ele()const
{
	auto result = this->begin();
	for(auto it = this->begin(); it != this->end(); ++it)
		if( it->power > result->power ) result = it;
	return *result;
}


template<class T>
Polynomial<T> Polynomial<T>::multiply(const Polynomial<T>& P1, const Polynomial<T>& P2)
{
	// FFT here. Too lazy to write.
	Polynomial<T> result;
	for(auto it = P1.begin(); it != P1.end(); ++it)
		for(auto jt = P2.begin(); jt != P2.end(); ++jt)
		{
			result.push_back((*it) * (*jt));
		}
	return result.unique();
}

template<class T>
typename Polynomial<T>::DivResult Polynomial<T>::divide(Polynomial P1, Polynomial P2)
{
	if(P2.size() == 0) throw std::overflow_error("divisor can't be 0!");
	auto mini1 = P1.mini_power(), mini2 = P2.mini_power();
	auto temp = Monomial<T>(1, (mini1 > mini2) ? -mini2 : -mini1);
	P1 = P1*Polynomial<T>({temp}); P2 = P2*Polynomial<T>({temp});

	Polynomial<T> quotient;
	for(auto it = P1.power_ele(), diver = P2.power_ele();
	 it.power > diver.power; it = P1.unique().power_ele())
	{
		auto quot = it/diver;
		quotient.push_back(quot);
		P1 -= Polynomial({quot})*P2;
	}

	for(auto it = P1.begin(); it != P1.end(); ++it) *it = (*it)/temp;
	for(auto it = quotient.begin(); it != quotient.end(); ++it) *it = (*it)/temp;
	return DivResult(quotient, P1);
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
	if(this->size() == 0) return "0";
	std::stringstream ss;
	auto it = this->begin();
	ss << std::string(*it);
	for(it++ ; it != this->end(); ++it)
		ss << (it->coff > 0 ? "+" : "") << std::string(*it);
	return ss.str();
}
