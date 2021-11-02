#include <iostream>

#include "VectorClass.hpp"
//Pour faire des tests
#include   "Array.hpp"

int main(void)
{
    Array<std::string, 2> data;
    data[0] = "Cherno";
    data[1] = "c++";

    Vector<std::string> vector;
    vector.PushBack("Cherno");
    vector.PushBack("C++");
    vector.PushBack("Vector");

    std::cin.get();
    return (0);
}