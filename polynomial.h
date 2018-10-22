#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <list>
#include <iterator>
#include <fstream>
#include "monomial.h"

// polynomial is inherited from STL-list<Monomial>
// which means `a Polynomial is a Monomial-list`
template<class T>
class Polynomial: public std::list< Monomial<T> >
{
public:
	// construction method
	Polynomial(){}
	Polynomial(std::list< Monomial<T> > lst): std::list< Monomial<T> >(lst) {}
	Polynomial(std::initializer_list< Monomial<T> > lst): std::list< Monomial<T> >(lst) {}
	// public member function
	inline Polynomial& add(const Polynomial& other){ return this->merge(other); }
	inline Polynomial& substract(const Polynomial& other){ return this->merge( -other ); }
	Polynomial& merge(Polynomial other);
	Polynomial& unique();
	//static method
	static Polynomial multiply(const Polynomial& P1, const Polynomial& P2);
	// mathmatic operator
	Polynomial& operator+=(const Polynomial<T>& other){ return this->add(other); }
	Polynomial& operator-=(const Polynomial<T>& other){ return this->substract(other); }
	Polynomial operator+(const Polynomial<T>& other)const{ return Polynomial(*this).add(other); }
	Polynomial operator-(const Polynomial<T>& other)const{ return Polynomial(*this).substract(other); }
	Polynomial operator*(const Polynomial<T>& other){ return multiply(*this, other); }
	Polynomial operator-()const;
	// convert operator
	operator std::string()const;
};

// stream operator
template<class T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& P){
	return out << std::string(P);
}

template<class T>
std::istream& operator>>(std::istream& in, const Polynomial<T>& P){
	Monomial<T> new_m;
	in >> new_m;
	P.push_back(new_m);
	return in;
}

#endif // POLYNOMIAL_H


