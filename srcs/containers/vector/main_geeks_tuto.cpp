//Toujours tester chaque fonction faite
//+ la comparer avec celle du vrai container

#include "VectorTuto.hpp"
#include <vector>

int main(void)
{
    std::vector<int> stdvInt;
    //changer le nom apres
    //ft::VectorClass<int> ftvInt;

    stdvInt.push_back(5);
    //ftVint.push_back(5);

    //ne pas faire des for range loop car c est du cpp11
    std::vector<int>::iterator it = stdvInt.begin();
    std::vector<int>::iterator ite = stdvInt.end();
    while (it != ite)
    {
        std::cout << *it << std::endl;
        it++;
    }
    return (0);
}