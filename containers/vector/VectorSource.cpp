#include "VectorSource.hpp"

//Est-ce qu'il faut rajouter ft devant ?
ft::vector::vector(const allocator_type &alloc = allocator_type()): m_alloc(alloc), m_capacity(0), m_start(NULL), m_size(0)
{
  if (DEBUG == 1)
  {
    std::cout << "0 - Constructor with const allocator_type reference called" << std::endl;
  }
  return ;
}

/* A verifier */
ft::vector::vector(size_type n): m_alloc(allocator_type()), m_capacity(0), m_start(NULL), m_size(n)
{
  if (DEBUG == 1)
  {
    std::cout << "1 - Constructor with size_t n parameter called" << std::endl;
  }
  return ;
}

//A continuer
ft::vector::vector(size_type n, const value_type& value, const allocator_type& = allocator_type()): m_alloc(alloc), m_capacity(n), m_start(m_alloc.allocate(n)), m_size(n)
{
  /* Ici on passe une value type donc un element a notre conteneur de type value_type */
  if (DEBUG == 1)
  {
    std::cout << "2 - Constructor with n, value and allocator called" << std::endl;
  }
  //Faire une boucle jusqu'a begin et end ?
  return ;
}

/* revoir la partie input iterator */
ft::vector::vector(const vector& x): m_alloc(x.m_alloc), m_capacity(x.m_capacity), m_start(m_alloc.allocate(m_capacity)), m_size(x.m_size)
{
  if (DEBUG == 1)
  {
    std::cout << "3 - Copy constructor with const reference called" << std::endl;
  }
  //iterator it = begin();
  return ;
}
