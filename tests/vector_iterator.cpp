#include "../srcs/vector_iterator.hpp"
#include <vector>
#include <iterator>
#include <cstddef>//ptrdiff_t
#include <iostream>

int main(void)
{
    /* Test constructeur par defaut */
    {
        std::vector<int>::iterator i;
        ft::vector_iterator<int> vi;

        /* Can not be printed if created by default constructor */
        //std::cout << "is is " << i << std::endl;
        // std::cout << "vi id" << vi << std::endl;
    }
    /*Test avec le constructeur qui prend une reference */
    {
        int test = 4;
        //int &ref = test;
        //int *ptr = &ref;

       // std::vector<int>::iterator i(ref);
        std::vector<int>::iterator i(&test);
        //ft::vector_iterator<int> vi(ref);
    }
    return (0);
}
