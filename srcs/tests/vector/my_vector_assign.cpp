
#include "../../../includes.hpp"
#include "../../../vector.hpp"

/* Inspiration des tests de mli */
//On va tester les deux namespace et faire des diffs sur les resultats
#define TESTED_NAMESPACE ft

#define TESTED_TYPE int

int my_vector_assign(void)
{
    //test main de la reference c plus plus
    TESTED_NAMESPACE::vector<int> first;
    TESTED_NAMESPACE::vector<int> second;
    TESTED_NAMESPACE::vector<int> third;

    first.assign(7, 100); // 7 ints with a value of 100

    TESTED_NAMESPACE::vector<int>::iterator it;
    //Pour pouvoir faire cela il faut que l'overload des iterateurs soit bien implemente
    it = first.begin() + 1;

    second.assign(it, first.end() - 1); // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3); // assigning from array.

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';

    //test avec le main de cpp reference (modifie)

    /* */
    TESTED_NAMESPACE::vector<char> characters(10);
    characters.assign(5, 'a');
    TESTED_NAMESPACE::vector<char>::iterator it1 = characters.begin();
    TESTED_NAMESPACE::vector<char>::iterator ite1 = characters.end();
    while (it1 != ite1)
    {
        std::cout << (*it1);
        it1++;
    }
    std::cout << std::endl;
    it1 = characters.begin();
    ite1 = characters.end();
    characters.assign(6, 'b');
    while (it1 != ite1)
    {
        std::cout << (*it1);
        it1++;
    }
    std::cout << std::endl;
    return (0);
}