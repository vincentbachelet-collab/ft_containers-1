
#include "../../../includes.hpp"

/* Inspiration des tests de mli */
//On va tester les deux namespace et faire des diffs sur les resultats
#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

int my_vector_assign(void)
{
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_two(4);
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_three;
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_four;
    return (0);
}