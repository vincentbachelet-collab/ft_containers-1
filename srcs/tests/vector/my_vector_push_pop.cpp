#include "../../../includes.hpp"

#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

void printvec(TESTED_NAMESPACE::vector<TESTED_TYPE> vec)
{
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vec.begin();
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator ite = vec.end();

    std::cout << "[ ";
    while (it != ite)
    {
        std::cout << (*it) << ' ';
        it++;
    }
    std::cout << "]" << std::endl;
}

//Permet de tester push et pop
int my_vector_push_pop(void)
{
    std::cout << "Testing push_back :" << std::endl;
    TESTED_NAMESPACE::vector<TESTED_TYPE> vec;
    int i = 0;
    while (i < 100)
    {
        vec.push_back(i);
        i++;
    }
    std::cout << "OK !" << std::endl;
    std::cout << "--------------" << std::endl;
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vec.begin();
    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator ite = vec.end();
    while (it != ite)
    {
        //std::cout << (*it) << std::endl;
        it++;
    }
    int cap = vec.capacity(); //on appelle bien capacity et pas get capacity
    std::cout << "Capacity is " << cap << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << "Testing pop_back :" << std::endl;
    TESTED_NAMESPACE::vector<TESTED_TYPE> myvector;
    int sum(0);
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    while (!myvector.empty())
    {
        sum += myvector.back();
        myvector.pop_back();
    }

    std::cout << "The elements of myvector add up to " << sum << '\n';
    std::cout << "OK !" << std::endl;
    std::cout << "--------------" << std::endl;

    TESTED_NAMESPACE::vector<TESTED_TYPE> numbers;

    printvec(numbers);

    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);

    printvec(numbers);

    numbers.pop_back();

    printvec(numbers);
    std::cout << "OK !" << std::endl;
    std::cout << "--------------" << std::endl;
    return (0);
}