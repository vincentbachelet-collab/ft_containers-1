//https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/
//Attention aux noms dans le tutoriel geeks for geeks
//TO DO: verifier les prototypes

#pragma once
/*
** Il est interessant de connaitre la time complexity des operations sur Vector
** 1. Inserting at the end takes differential time.
** 2. Removing the last element takes only constant time. 
** 3. Inserting or erasing at beginning or in the middle is linear time. 
*/

#include <bits/stdc++.h>

namespace ft 
{ 
    template <typename T>
    class VectorClass
    {
    private:
        //Stores the address of our vector
        T *arr;

        //capacity is the total storage
        //capacity of the vector
        int capacity;

        //current is the number of elements 
        //currently present in the vector
        int current;

    public:

        //Default constructor to initialise 
        //an initial capacity of 1 element 
        //and allocating storage using dynamic allocation
        vectorClass()
        {
            arr = new T[1];
            capacity = 1;
            current = 0;
        }

        //function to add an element at the last
        void push_back(T data)
        {
            //if the number of elements is equall to
            //capacity, that means we don't have space
            //to accomodate more elements. We need to 
            //double the capacity
            if (current == capacity)
            {
                T* temp = new T[2 * capacity];
            }

            //copying old array elements to new array
            for (int i; i < capacity; i++)
            {
                temp[i] = array[i];
            }
            //deleteting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;

            //inserting data
            arr[current] = data;
            current++; 
        }
        
    };
}