#include "../../../includes/tests/tests.hpp"

/* Tests basiques persos: construction... */
int my_vector_tests(void)
{
    //Appel du constructeur par defaut
    std::cout << "Default constructor testing : " << std::endl;
    ft::vector<int> ft_vec;
    std::cout << "OK !" << std::endl;
    std::cout << "-----------------" << std::endl;

    //Appel du constructeur par defaut avec un allocateur pour test
    std::cout << "Default constructor with allocator : " << std::endl;
    std::allocator<int> my_alloc;
    ft::vector<int> ft_vec1(my_alloc);
    std::cout << "OK !" << std::endl;
    std::cout << "-----------------" << std::endl;

    //Test deuxieme constructeur
    std::cout << "Copying constructor with allocator : " << std::endl;
    std::vector<int> std_vec2(5);
    ft::vector<int> ft_vec2(5);
    std::cout << "OK !" << std::endl;
    std::cout << "-----------------" << std::endl;

    //affichage des deux vecteurs
    ft::vector<int>::iterator it = ft_vec2.begin();
    ft::vector<int>::iterator ite = ft_vec2.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }
    std::cout << "OK !" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Testing fill constructor : " << std::endl;
    std::vector<int> std_vec3(5, 4);
    ft::vector<int> ft_vec3(5, 4);
    ft::vector<int>::iterator it1 = ft_vec3.begin();
    ft::vector<int>::iterator ite1 = ft_vec3.end();
    while (it1 != ite1)
    {
        std::cout << (*it1) << std::endl;
        it1++;
    }
    std::cout << "OK !" << std::endl;
    std::cout << "-----------------" << std::endl;

    //Tester reserve
    std::cout << "Testing reserve function" << std::endl;
    int test = 10;
    ft_vec3.reserve(test);
    int check = ft_vec3.get_capacity();
    std::cout << "The resulting capacity is : " << check << std::endl;
    if (check == test)
        std::cout << "OK !" << std::endl;
    else
        std::cout << "KO :(" << std::endl;
    std::cout << "-----------------" << std::endl;

    //TODO: tester les iterateurs
    //TODO: test empty
    //TODO: test size
    //TODO: reprendre enable if
    return (0);
}