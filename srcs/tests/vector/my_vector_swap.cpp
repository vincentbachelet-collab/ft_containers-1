#include "../../../includes.hpp"

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

//TODO: a mettre dans un fichier commun pour ne pas avoir a reinclure
void print_vec(TESTED_NAMESPACE::vector<TESTED_TYPE> vec)
{
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vec.begin();
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator ite = vec.end();

    std::cout << "Printing vec : ";
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
}

int my_vector_swap(void)
{
    TESTED_NAMESPACE::vector<TESTED_TYPE> foo(3, 100); // three ints with a value of 100
    TESTED_NAMESPACE::vector<TESTED_TYPE> bar(5, 200); // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (unsigned i = 0; i < foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << std::endl;

    std::cout << "bar contains:";
    for (unsigned i = 0; i < bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << std::endl;

    //std::cout << "Other test" << std::endl;
    TESTED_NAMESPACE::vector<int> a1;
    a1.push_back(1);
    a1.push_back(2);
    a1.push_back(3);
    print_vec(a1);
    TESTED_NAMESPACE::vector<int> a2;
    a2.push_back(4);
    a2.push_back(5);
    print_vec(a2);
    a1.swap(a2);
    print_vec(a1);
    print_vec(a2);
    return (0);
}