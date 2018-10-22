#include "monomial.cpp"
#include "polynomial.cpp"
#include <iostream>
#include <string>
#include <sstream>

template<typename T>
inline void readin(Polynomial<T> *P, std::stringstream& ss);
template<typename T>
inline void testop(Polynomial<T> P1, Polynomial<T> P2);

int main(int argv, char*argc[]){
    std::stringstream ss;
    for(int i = 1; i < argv; ++i)
        ss << std::string(argc[i]) << "\n";
    
    Polynomial<double> P1, P2;
    readin(&P1, ss);
    readin(&P2, ss);
    testop(P1, P2);
    return 0;
}

template<typename T>
inline void readin(Polynomial<T> *P, std::stringstream& ss)
{
    int count = 0;
    ss >> count;
    for(int i = 0; i < count; ++i)
    {
        T coff, power;
        ss >> coff >> power;
        Monomial<T> m_new(coff, power);
        P->push_front(m_new);
    }
}

template<typename T>
inline void testop(Polynomial<T> P1, Polynomial<T> P2)
{
    P1.unique(), P2.unique();
    std::cout << "P1:\t" << P1 << std::endl;
    std::cout << "P2:\t" << P2 << std::endl;
    std::cout << "P1+P2:\t" << P1+P2 << std::endl;
    std::cout << "P1-P2:\t" << P1-P2 << std::endl;
    std::cout << "P1*P2:\t" << P1*P2 << std::endl;
}