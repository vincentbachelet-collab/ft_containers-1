//a reprendre
#include "../../../includes/includes.hpp"
/*AVOIR FINI vector avant de tout tester */

int test(void)
{
    std::vector<int> stv;

    stv.push_back(1);
    stv.push_back(2);
    stv.push_back(3);

    std::cout << "STD reverse iterator" << std::endl;
    std::cout << "--------------------" << std::endl;

    /* Quand on veut utiliser des reverse iterateur il faut 
    bien penser a appeler des fonctions qui retourne des reverse iterateurs
    et pas des iterateurs ! */
    std::vector<int>::reverse_iterator r1 = stv.rbegin();
    std::cout << "FT reverse iterator" << std::endl;
    std::cout << "--------------------" << std::endl;
    ft::vector<int>::reverse_iterator r2 = stv.rbegin();
    
    return (0);
}