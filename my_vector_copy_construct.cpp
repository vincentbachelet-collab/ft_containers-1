#include "vector.hpp"

#define TESTED_NAMESPACE ft

#define TESTED_TYPE int

void printSize(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct, bool print_content = 1)
{
    std::cout << "size: " << vct.size() << std::endl;
    std::cout << "capacity: " << vct.capacity() << std::endl;
    std::cout << "max_size: " << vct.max_size() << std::endl;
    if (print_content)
    {
        TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator it = vct.begin();
        TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite = vct.end();
        std::cout << std::endl
                  << "Content is:" << std::endl;
        for (; it != ite; ++it)
            std::cout << "- " << *it << std::endl;
    }
}

int my_vector_copy_construct(void)
{
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct(5);
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin(), ite = vct.end();

    std::cout << "len: " << (ite - it) << std::endl;
    for (; it != ite; ++it)
        *it = (ite - it);

    it = vct.begin();
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_range(it, ite);
    for (int i = 0; it != ite; ++it)
        *it = ++i * 5;

    it = vct.begin();
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_copy(vct);
    for (int i = 0; it != ite; ++it)
        *it = ++i * 7;
    vct_copy.push_back(42);
    vct_copy.push_back(21);

    std::cout
        << "\t-- PART ONE --" << std::endl;
    printSize(vct);
    printSize(vct_range);
    printSize(vct_copy);

    vct = vct_copy;
    vct_copy = vct_range;
    vct_range.clear();

    std::cout << "\t-- PART TWO --" << std::endl;
    printSize(vct);
    printSize(vct_range);
    printSize(vct_copy); //le troisieme a bcp trop d element
    return (0);
}