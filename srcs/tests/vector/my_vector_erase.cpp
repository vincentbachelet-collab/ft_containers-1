#include "../../../includes.hpp"
#include "../../../vector.hpp"

#define TESTED_NAMESPACE ft

#define TESTED_TYPE int

int my_vector_erase(void)
{
    //reference cpp
    ft::vector<int> myvector;

    // set some values (from 1 to 10)
    for (int i = 1; i <= 10; i++)
        myvector.push_back(i);

    // erase the 6th element
    myvector.erase(myvector.begin() + 5);

    // erase the first 3 elements:
    myvector.erase(myvector.begin(), myvector.begin() + 3);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); ++i)
        std::cout << ' ' << myvector[i];
    std::cout << std::endl;

    //reference c plus plus
    ft::vector<int> cnt;
    cnt.push_back(4);
    cnt.push_back(-1);
    cnt.push_back(10);
    cnt.push_back(2);
    //print_container("Init:\n", cnt);

    ft::vector<int>::iterator it = cnt.begin();

    //prend un iterateur et pas un int/position
    cnt.erase(it);
    it = cnt.begin();
    std::cout << "second test : ";
    ft::vector<int>::iterator ite = cnt.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    return (0);
}