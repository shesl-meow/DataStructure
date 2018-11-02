#include "monomial.h"
#include <stdexcept>
#include <sstream>

template<class T>
inline Monomial<T>& Monomial<T>::multiply(const Monomial<T>& other)
{
    this->coff *= other.coff;
    this->power += other.power;
    return *this;
}

template<class T>
inline Monomial<T>& Monomial<T>::devide(const Monomial<T>& other)
{
    if(this->sign != other.sign){
        throw std::invalid_argument("Can't devide monomial with different sign symbol.");
    }else{
        this->coff /= other.coff;
        this->power -= other.power;
    }
    return *this;
}

template<class T>
Monomial<T>::operator std::string () const
{
    std::stringstream ss;
    if(this->coff == 0) ss << 0;
    else if(this->power == 0) ss << this->coff;
    else ss << this->coff << this->sign << "^{" << this->power << "}";
    return ss.str();
}

// int main(){
//     Monomial<int> t1(1,2);
//     auto a = std::string(t1);
//     return 0;
// }
