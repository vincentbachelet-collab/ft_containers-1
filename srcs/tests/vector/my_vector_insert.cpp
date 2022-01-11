#include "../../../includes.hpp"

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE std
#endif

#define TESTED_TYPE int

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

int my_vector_insert(void)
{
    //Main d'exemple c plus plus reference
    TESTED_NAMESPACE::vector<TESTED_TYPE> vec(3, 100);
    //print_vec(vec);
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it;
    it = vec.begin();
    it = vec.insert(it, 200);
    print_vec(vec);

    vec.insert(it, 2, 300);
    print_vec(vec);

    it = vec.begin();

    std::vector<int> vec2(2, 400);
    vec.insert(it + 2, vec2.begin(), vec2.end());
    print_vec(vec);

    /**/
    int arr[] = {501, 502, 503};
    vec.insert(vec.begin(), arr, arr + 3);
    print_vec(vec);
    return (0);
}