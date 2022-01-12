#include "../../../includes.hpp"
#include "../../../vector.hpp"

#define TESTED_NAMESPACE ft

#define TESTED_TYPE int

//Teste des iterator (const et pas const) (et operateur de comparaison)
//TODO

void prepost_incdec(TESTED_NAMESPACE::vector<TESTED_TYPE> &vct)
{
    ft::vector<int>::iterator it = vct.begin();
    ft::vector<int>::iterator it_tmp;

    std::cout << "Pre inc" << std::endl;
    it_tmp = ++it;
    std::cout << *it_tmp << " | " << *it << std::endl;

    std::cout << "Pre dec" << std::endl;
    it_tmp = --it;
    std::cout << *it_tmp << " | " << *it << std::endl;

    std::cout << "Post inc" << std::endl;
    it_tmp = it++;
    std::cout << *it_tmp << " | " << *it << std::endl;

    std::cout << "Post dec" << std::endl;
    it_tmp = it--;
    std::cout << *it_tmp << " | " << *it << std::endl;
    std::cout << "###############################################" << std::endl;
}

int my_vector_ite(void)
{
    const int size = 5;
    ft::vector<int> vct(size);
    ft::vector<int>::iterator it = vct.begin();
    //TODO: revoir les const
    ft::vector<int>::iterator const ite = vct.begin();

    for (int i = 0; i < size; ++i)
        it[i] = (size - i) * 5;
    prepost_incdec(vct);

    it = it + 5;
    it = 1 + it;
    it = it - 4;
    std::cout << *(it += 2) << std::endl;
    std::cout << *(it -= 1) << std::endl;

    //TODO: a faire
    // *(it -= 2) = 42;
    // *(it += 2) = 21;

    std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
    std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

    std::cout << "(it == const_it): " << (ite == it) << std::endl;
    std::cout << "(const_ite - it): " << (ite - it) << std::endl;
    std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

    //printSize(vct, true);
    return (0);
}
