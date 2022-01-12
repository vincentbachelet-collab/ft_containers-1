#include "../../../includes.hpp"
#include "../../../vector.hpp"

#define TESTED_NAMESPACE std

#define TESTED_TYPE int

/*
void print_vec(ft::vector<int> vec)
{
    ft::vector<int>::iterator it = vec.begin();
    ft::vector<int>::iterator ite = vec.end();

    std::cout << "Printing vec : ";
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    return;
}
*/

int my_vector_insert(void)
{
    //Main d'exemple c plus plus referenc
    /* */
    ft::vector<int> vec(3, 100);
    //print_vec(vec);
    ft::vector<int>::iterator it;
    it = vec.begin();
    it = vec.insert(it, 200);
    //print_vec(vec);

    vec.insert(it, 2, 300);
    //print_vec(vec);

    it = vec.begin();

    ft::vector<int> vec2(2, 400);
    vec.insert(it + 2, vec2.begin(), vec2.end());
    //print_vec(vec);

    int arr[] = {501, 502, 503};
    vec.insert(vec.begin(), arr, arr + 3);
    //print_vec(vec);
    return (0);
}