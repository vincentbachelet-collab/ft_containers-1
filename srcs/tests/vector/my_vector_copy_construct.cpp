#include "../../../includes.hpp"

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

int my_vector_copy_construct(void)
{
    TESTED_NAMESPACE::vector<TESTED_TYPE> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(13);

    //on va tester tous les constructeurs ici
    return (0);
}