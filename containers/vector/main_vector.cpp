#include <iostream>
#include <vector>

#include "VectorClass.hpp"
//Pour faire des tests
#include   "Array.hpp"

struct Vector3
{
    float x = 0.0f, y = 0.0f, z = 0.0f;
    Vector3(float scalar): x(scalar), y(scalar), z(scalar){}
    Vector3(float x, float y, float z): x(x), y(y), z(z) {}
    Vector3(): x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(const Vector3 &other)
    {
        std::cout << "Copy" << std::endl;
    }
    Vector3(const Vector3 &&other): x(other.x), y(other.y), z(other.z)
    {
        std::cout << "Move" << std::endl;
    }
    ~Vector3()
    {
        std::cout << "Destructor" << std::endl;
    }

    Vector3& operator=(const Vector3 &other)
    {
        std::cout << "Copy" << std::endl;
        x = other.x;
        y = other.y;
        z = other.z;
        return (*this);
    }

    Vector3& operator=(const Vector3 &&other)
    {
        std::cout << "Move" << std::endl;
        x = other.x;
        y = other.y;
        z = other.z;
        return (*this);
    }
};

//toujours faire un template quand on ne sait pas 
template <typename T>
void PrintVector(const Vector<T> &vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
    {
        std::cout << vector[i] << std::endl;
    }
    std::cout << "----------------" << std::endl;
}

//Specialisation
template <>
void PrintVector(const Vector<Vector3> &vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
    {
        std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;
    }
    std::cout << "----------------" << std::endl;
}

int main(void)
{
    /*
    Array<std::string, 2> data;
    data[0] = "Cherno";
    data[1] = "c++";
    */

    Vector<Vector3> vector;
    //Temporaries -> We have to avoid using temporaries
    vector.PushBack(Vector3(1.0f));
    vector.PushBack(Vector3(2, 3, 4));
    vector.PushBack(Vector3());
    PrintVector(vector);
    //Pour que le programme ne s'arrete pas
    //std::cin.get();
    return (0);
}