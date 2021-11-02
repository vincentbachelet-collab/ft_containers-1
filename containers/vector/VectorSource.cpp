#include "VectorSource.hpp"

//pourra etre utiliser pour faire des tests

//A continuer
/*
ft::vector::vector(size_type n, const value_type& value, const allocator_type& = allocator_type()): m_alloc(alloc), m_capacity(n), m_start(m_alloc.allocate(n)), m_size(n)
{
  //Ici on passe une value type donc un element a notre conteneur de type value_type
  if (DEBUG == 1)
  {
    std::cout << "2 - Constructor with n, value and allocator called" << std::endl;
  }
  //Faire une boucle jusqu'a begin et end ?
  return ;
}

//revoir la partie input iterator
ft::vector::vector(const vector& x): m_alloc(x.m_alloc), m_capacity(x.m_capacity), m_start(m_alloc.allocate(m_capacity)), m_size(x.m_size)
{
  if (DEBUG == 1)
  {
    std::cout << "3 - Copy constructor with const reference called" << std::endl;
  }
  //iterator it = begin();
  return ;
}
*/

//Apres recherche = pas possible en std=cpp98 de le faire dans un fichier extern
