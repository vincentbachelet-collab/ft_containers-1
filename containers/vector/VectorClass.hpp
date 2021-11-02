#ifndef VECTORCLASS_HPP
# define VECTORCLASS_HPP

//pragma once
/* Le vrai vecteur est defini dans <vector> */
#include <memory>

//git@github.com:mli42/containers_test.git
//voir videos Bradley Sward

//template <class T, class Allocator = std::allocator<T>>
//class vector;

//Video tuto the cherno
template<typename T>
class Vector
{
public:
    Vector();
    {
        //allocates the memory
    }
    //Un vector store un pointeur sur n'importe quel type
private:
    
    T *m_Data = nullptr;
    //Besoin de savoir combien d elem on a dans notre vector
    size_t m_Size = 0;
    //Aussi besoin de savoir combien de memoire on a alloue
    size_t m_Capacity = 0;
}

#endif