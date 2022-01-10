#include "../../../includes/tests/tests.hpp"

/* Tests basiques persos: construction... */
int my_vector_tests(void)
{
    //std::vector<int> std_vec;
    //Appel du constructeur par defaut
    ft::vector<int> ft_vec;

    //Appel du constructeur par defaut avec un allocateur pour test
    std::allocator<int> my_alloc;
    ft::vector<int> ft_vec1(my_alloc);

    //std::vector<int> std_vec1(my_alloc);

    //Test deuxieme constructeur
    std::vector<int> std_vec2(5);
    ft::vector<int> ft_vec2(5);

    //affichage des deux vecteurs
    ft::vector<int>::iterator it = ft_vec2.begin();
    ft::vector<int>::iterator ite = ft_vec2.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }
    return (0);
}