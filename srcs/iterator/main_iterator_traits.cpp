#include <iostream>
#include <iterator>
//Iterator traits is part of the iterator library 
#include <typeinfo>// typeid - ?

int main(void)
{
    typedef std::iterator_traits<int *> traits;
    if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
    {
        std::cout << "int * is a random-acess iterator" << std::endl;
    }
    return (0);
}

