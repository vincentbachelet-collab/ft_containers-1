#pragma once
#include <iostream>

//Trouve dans le tuto mais j aurais pu reprendre les exos du cpp
template<typename T, size_t S>
class Array
{
public:
    Array()
    {

    }
    //revoir constexpr
    constexpr size_t Size() const {return S;}
    T& operator[](size_t index) {return m_Data[index];}
    const T& operator[](size_t index) const { return m_Data[index];}

    T *Data() {return m_Data;}
    const T* Data() const [ return m_Data;}

private:
    T m_Data[S];
};