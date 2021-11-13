#pragma once

#include "../../../includes/includes.hpp"

/*
** std::pair is defined in utility
** std::pair is a class template that provides a way to store two heterogeneous objects as a single unit. 
** A pair is a specific case of a std::tuple with two elements.
*/

/*
** TODO: verifier que tout a bien ete implemente (en suivant la doc)
*/
namespace ft
{
    /*
    ** https://en.cppreference.com/w/cpp/utility/pair
    */
   //types of the elements in the pair
   template<class T1, class T2>
   class pair 
   {
    /* voir s'il faut mieux de mettre en prive */
    public:
        typedef T1   first_type;
        typedef T2   second_type;

    private:
        first_type  first;
        second_type second;

    /* Classe canonique */
    public:
    //TO DO: ajouter des fonctions de debug 
        pair() {}

        template<typename U, typename V>
        pair(const pair<U,V> &ref): first(ref.first), second(ref.second)
        {
            if (DEBUG)
                std::cout << "Pair second constructor called" << std::endl;
        }

        pair(const first_type &a, const second_type &b) : first(a), second(b)
        {
            if (DEBUG)
                std::cout << "Pair third constructor called" << std::endl;
        }

        virtual ~pair()
        {
            if (DEBUG)
                std::cout << "Pair destructor called" << std::endl;
        }

        pair &operator=(const pair &src)
        {
            this->first = src.first;
            this->second = src.second;
            return (*this);
        }
   };
   
   /*
   ** Surchage d'operateurs
   */
  template <typename T1, typename T2>
  bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
      return (lhs.first == rhs.first && lhs.second == rhs.second);
  }

 template <typename T1, typename T2>
 bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
      return (!(lhs==rhs));
  }

  template <typename T1, typename T2>
  bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
      return (lhs.first < rhs.first  || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
  }

  /*
  ** Attention a checker 
  */
  template <typename T1, typename T2>
  bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
  {
      return (lhs > rhs);
  }

 template <typename T1, typename T2>
 bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
 {
    return (lhs <= rhs);
 }

template <typename T1, typename T2>
 bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
 {
    return (lhs >= rhs);
 }
}