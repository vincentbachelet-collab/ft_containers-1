#include "../../../includes.hpp"

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

//TODO: a tester
int my_vector_size(void)
{
    TESTED_NAMESPACE::vector<TESTED_TYPE> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 10; i++)
        myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert(myints.end(), 10, 100);
    std::cout << "2. size: " << myints.size() << '\n';

    //myints.pop_back();
    //std::cout << "3. size: " << myints.size() << '\n';

    return 0;
    return (0);
}