#include "../../../includes.hpp"
#include "../../../vector.hpp"

#define TESTED_NAMESPACE ft

#define TESTED_TYPE int

int my_vector_copy_construct(void)
{
    ft::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(13);

    //on va tester tous les constructeurs ici
    return (0);
}