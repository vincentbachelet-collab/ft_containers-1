#include <iostream>
#include <type_traits>

#include "../srcs/utils.hpp"

class A {};
 
enum E : int {};
 
template <class T>
T f(T i)
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    return i;
}
 
int main() 
{
    //std::cout << std::boolalpha;
    /* Ajouter plus de tests pour verifier les types que j ai ajoute au code source */
    /* Implementation std */
    std::cout << std::is_integral<A>::value << std::endl;
    std::cout << std::is_integral<E>::value << std::endl;
    std::cout << std::is_integral<float>::value << std::endl;
    std::cout << std::is_integral<int>::value << std::endl;
    std::cout << std::is_integral<const int>::value << std::endl;
    std::cout << std::is_integral<bool>::value << std::endl;
    //std::cout << f(123) << std::endl;
    //std::cout << "------------------" << std::endl;
    /* mon implementation */
    std::cout << ft::is_integral<A>::value << std::endl;
    std::cout << ft::is_integral<E>::value << std::endl;
    std::cout << ft::is_integral<float>::value << std::endl;
    std::cout << ft::is_integral<int>::value << std::endl;
    std::cout << ft::is_integral<const int>::value << std::endl;
    std::cout << ft::is_integral<bool>::value << std::endl;
}