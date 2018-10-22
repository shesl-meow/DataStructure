#ifndef MONOMIAL_H
#define MONOMIAL_H
#include <string>
#include <fstream>

template<class T>
class Monomial
{
public:
    // construction method
    Monomial() {}
    Monomial(T c, T p): coff(c), power(p) {}
    Monomial(T c, char s, T p): coff(c), sign(s), power(p) {}
    // public member function
    inline Monomial& multiply(const Monomial& other);
    inline Monomial& devide(const Monomial& other);
    // static method
    static inline bool similar(const Monomial& M1, const Monomial& M2) {
        return (M1.power == M2.power); } 
    // logic operator
	bool operator<(const Monomial& other)const { return this->power < other.power; }
	bool operator>(const Monomial& other)const { return this->power > other.power; }
	bool operator==(const Monomial& other)const {
		return (this->power == other.power) && (this->coff == other.coff); }
    // mathmatic operator
    Monomial operator*=(const Monomial& other){ return this->multiply(other); }
    Monomial operator/=(const Monomial& other){ return this->devide(other); }
    Monomial operator*(const Monomial& other)const{ return Monomial(*this).multiply(other); }
    Monomial operator/(const Monomial& other)const{ return Monomial(*this).devide(other); }
    Monomial operator-()const { return Monomial(-this->coff, this->power); }
    // conversion operator
    operator std::string () const;
    // friend class and method
    template<class S> friend class Polynomial;
    template<class S> friend std::ostream& operator<<(std::ostream& out, const Monomial<S>& M);
    template<class S> friend std::istream& operator>>(std::istream& in, const Monomial<S>& M);
private:
    // member variables are private. Monomial: $coff*sign^{power}$
    char sign = 'x';
    T coff = 1, power = 0;
};

// stream operator
template<class T>
std::ostream& operator<<(std::ostream& out, const Monomial<T>& M){
    return out << std::string(M);
}
template<class T>
std::istream& operator>>(std::istream& in, const Monomial<T>& M){
    return in >> M.coff >> M.power;
}

#endif // MONOMIAL_H
