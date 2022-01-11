#include "../../../includes.hpp"

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

//Permet de tester push et pop
int my_vector_push_pop(void)
{
    TESTED_NAMESPACE::vector<TESTED_TYPE> vec;
    int i = 0;
    while (i < 100)
    {
        vec.push_back(i);
        i++;
    }

    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vec.begin();
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator ite = vec.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }
    int cap = vec.capacity(); //on appelle bien capacity et pas get capacity
    std::cout << "Capacity is " << cap << std::endl;
    return (0);
}