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
/*
** Verifier si elles doivent etre prives ou publiques
** Noter tous les protos de la reference
** reprendre les typedef du vrai vector en regardant le code via VScode
*/
template<typename T>
class Vector
{
public:
    Vector()
    {
        //allocates the memory
        ReAlloc(2);
        return;
    }

    /*
    ** PushBack function (will do copie - bad)
    */
    void PushBack(const T& value)
    {
        //Il faut d'abord verifier qu'il y a assez de place pour ajouter un elem
        if (this->m_Size >= this->m_Capacity)
            ReAlloc(this->m_Capacity + this->m_Capacity / 2);

        m_Data[this->m_Size] = value;
        this->m_Size++;
    }

    //lvalues and rvalues (a revoir)
    //Ce n est pas dans le standard 98 !
    void PushBack(T&& value)
    {
        //Il faut d'abord verifier qu'il y a assez de place pour ajouter un elem
        if (this->m_Size >= this->m_Capacity)
            ReAlloc(this->m_Capacity + this->m_Capacity / 2);

        //move va aussi permettre de faire un cast (lvalue)
        m_Data[this->m_Size] = std::move(value);
        this->m_Size++;
    }

    /*
    ** Operateur pour acceder a notre data
    ** On va faire une version const et une version non const
    */
    //version const
    const    T& operator[](size_t index) const
    {
        /*
        if (index >= this->m_Size)
        {
            if (this->m_Size >= this->m_Capacity)
                ReAlloc(this->m_Capacity + this->m_Capacity / 2);

            m_Data[this->m_Size] = value;
            this->m_Size++;
        }
        */
        return (this->m_Data[index]);
    }

    //Version non const
    T& operator[](size_t index)
    {
        return (this->Data[index]);
    }

    //Know the size
    size_t Size() const { return this->m_Size;}



//Un vector store un pointeur sur n'importe quel type
private:
    T *m_Data = nullptr;
    //Besoin de savoir combien d elem on a dans notre vector
    size_t m_Size = 0;
    //Aussi besoin de savoir combien de memoire on a alloue
    size_t m_Capacity = 0;
    //A chaque fois qu on aura besoin d'allouer a nouveau on allouera la moitie de la capacite qu on a actuellement

    /*
    ** Reallocation function
    */
    void ReAlloc(size_t newCapacity)
    {
        //1. allocate a new block of memory
        //2. copy existings elements into this new block of memory / (move)
        T * newBlock = new T[newCapacity];

        //check if we are down sizing
        if (newCapacity < this->m_Size)
            this->m_Size = newCapacity;

        //Theoriquement ca ne marcherait pas pour reduire notre size
        for (size_t i = 0; i < this->m_Size; i++)
            newBlock[i] = this->m_Data[i];

        delete [] this->m_Data;
        this->m_Data = newBlock;
        this->m_Capacity = newCapacity;
    }
};

#endif
