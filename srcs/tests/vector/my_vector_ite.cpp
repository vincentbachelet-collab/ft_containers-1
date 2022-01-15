#include "../../../includes.hpp"
#include "../../../vector.hpp"

#define TESTED_NAMESPACE ft

#define TESTED_TYPE int

int my_vector_ite(void)
{
    const int size = 5;
    ft::vector<int> vct(size);
    ft::vector<int>::iterator it = vct.begin();
    ft::vector<int>::iterator const ite = vct.begin();
    return (0);
}
