#include "../../../includes/tests/tests.hpp"

/* Tests basiques persos: construction... */
int my_vector_tests(void)
{
    //Appel du constructeur par defaut
    std::cout << "Default constructor testing : " << std::endl;
    ft::vector<int> ft_vec;
    std::vector<int> std_vec;
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

    //TODO: tester les iterateurs (simple)
    //TODO: rajouter des tests en pushant des chiffres differents
    std::cout << "TESTING ITERATORS" << std::endl;
    std::cout << "1. Testing begin" << std::endl;
    std::vector<int>::iterator std_it = std_vec3.begin();
    std::cout << "Std iterator : " << std::endl;
    std::cout << (*std_it) << std::endl;
    ft::vector<int>::iterator ft_it = ft_vec3.begin();
    std::cout << "ft iterator : " << std::endl;
    std::cout << (*ft_it) << std::endl;
    if ((*ft_it) == (*std_it))
        std::cout << "OK !" << std::endl;
    else
        std::cout << "KO :(" << std::endl;
    std::cout << "-----------------" << std::endl;
    std_it = std_vec3.end();
    //Tester les reverses iterateurs
    std::cout << "1. Testing end" << std::endl;
    std::cout << "Std iterator : " << std::endl;
    std::cout << (*std_it) << std::endl;
    ft_it = ft_vec3.end();
    std::cout << "ft iterator : " << std::endl;
    std::cout << (*ft_it) << std::endl;
    if ((*ft_it) == (*std_it))
        std::cout << "OK !" << std::endl;
    else
        std::cout << "KO :(" << std::endl;
    std::cout << "-----------------" << std::endl;
    //TODO: tester rbegin et rend

    //TODO: test empty
    std::cout << std::endl;
    std::cout << "TESTING CAPACITY" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Testing size :" << std::endl;
    std::cout << ft_vec3.size() << std::endl;
    std::cout << std_vec3.size() << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Testing max size :" << std::endl;
    std::cout << ft_vec3.max_size() << std::endl;
    std::cout << std_vec3.max_size() << std::endl;
    std::cout << "-----------------" << std::endl;
    //TODO: resize capacity reserve
    std::cout << "Testing empty" << std::endl;
    std::cout << std_vec3.empty() << std::endl;
    std::cout << ft_vec3.empty() << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << std_vec.empty() << std::endl;
    std::cout << ft_vec.empty() << std::endl;
    std::cout << "-----------------" << std::endl;
    //TODO: reprendre enable if
    //TODO: tester ce qu il y a dans utils
    return (0);
}