#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>

#include "iterator_test.hpp"
#include "algorithm_test.hpp"
#include "type_traits_test.hpp"

#define DEBUG 1

namespace ft
{
  template<class T, class Allocator = std::allocator<T> >
  class vector
  {
  private:
      allocator_type	m_alloc;
      size_type		    m_capacity;
      pointer			    m_start;
      size_type		    m_size;
  public:

      /*
      ** Fonction allocate :
      ** Attempts to allocate a block of storage with a size
      ** large enough to contain n elements of member type value_type.
      */
      typedef T                                           value_type;
      typedef Allocator                                   allocator_type;
      typedef typename allocator_type::reference          reference;
      typedef typename allocator_type::const_reference    const_reference;

      /* Iterateurs */
      //https://www.geeksforgeeks.org/iterators-c-stl/
      //https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.2/class____gnu__cxx_1_1____normal__iterator.html
      /*
      typedef ft::normal_iterator<pointer, vector>               iterator;
      typedef ft::normal_iterator<std::__const_pointer, vector>  const_iterator;
      */
      typedef typename allocator_type::size_type                 size_type;
      typedef typename allocator_type::difference_type           difference_type;
      typedef typename allocator_type::pointer                   pointer;
      typedef typename allocator_type::const_pointer             const_pointer;
      /*
      typedef std::reverse_iterator<iterator>                    reverse_iterator;
      typedef std::reverse_iterator<const_iterator>              const_reverse_iterator;
      */
      /* Aide pour moi, faire des getters et des setters */
      allocator_type getAlloc(void) const
      {
        return (this->m_alloc);
      }

      size_type getSize(void) const
      {
        return (this->m_capacity);
      }

      pointer getStart(void) const
      {
        return (this->m_start);
      }

      size_type getType(void) const
      {
        return (this->m_size);
      }
      /* Partie canonique */

      /*
      ** Explicite signifie que le constructeur ne peut pas etre utilise
      ** pour des conversions implicites ou des copy initialization.
      */
      //vector(const allocator_type &alloc);
      //explicit vector(const allocator_type &alloc);
      //TO DO: voir s'il faut forcement que ce soit explicit ou pas, on ne peut pas avoir les deux
      vector(const allocator_type &alloc): m_alloc(alloc), m_capacity(0), m_start(NULL), m_size(0)//const allocator_type &alloc = allocator_type()
      {
        if (DEBUG == 1)
        {
          std::cout << "0 - Constructor with const allocator_type reference called" << std::endl;
        }
        return ;
      }

      //explicit vector(size_type n);
      vector(size_type n): m_alloc(allocator_type()), m_capacity(0), m_start(NULL), m_size(n)
      {
        if (DEBUG == 1)
        {
          std::cout << "1 - Constructor with size_t n parameter called" << std::endl;
        }
        return ;
      }

      //vector(size_type n, const value_type& value, const allocator_type& = allocator_type());
      vector(size_type n, const value_type& value, const allocator_type& alloc = allocator_type()): m_alloc(alloc), m_capacity(n), m_start(m_alloc.allocate(n)), m_size(n)
      {
        //Ici on passe une value type donc un element a notre conteneur de type value_type
        if (DEBUG == 1)
        {
          std::cout << "2 - Constructor with n, value and allocator called" << std::endl;
        }
        //TODO: Faire une boucle jusqu'a begin et end ?
        return ;
      }
      /*
      template <class InputIterator>
          vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type());
      */
      /*
      vector(const vector& x);
      vector(vector&& x)
      vector(initializer_list<value_type> il);
      vector(initializer_list<value_type> il, const allocator_type& a);
      ~vector();

      vector& operator=(const vector& x);
      vector& operator=(vector&& x);
      vector& operator=(initializer_list<value_type> il);
      */

      /* Input iterators */
      /*
      template <class InputIterator>
          void assign(InputIterator first, InputIterator last);
      */
      /* Prototypes des fonctions
      void                  assign(size_type n, const value_type& u);
      void                  assign(initializer_list<value_type> il);
      allocator_type        get_allocator() const;
      iterator               begin();
      const_iterator         begin()   const;
      iterator               end();
      const_iterator         end()     const;
      reverse_iterator       rbegin();
      const_reverse_iterator rbegin()  const;
      reverse_iterator       rend();
      const_reverse_iterator rend()    const;
      size_type              size() const;
      size_type              max_size() const;
      size_type              capacity() const;
      bool                   empty() const;
      void                   reserve(size_type n);
      reference       operator[](size_type n);
      const_reference operator[](size_type n) const;
      reference               at(size_type n);
      const_reference         at(size_type n) const;
      reference               front();
      const_reference         front() const;
      reference               back();
      const_reference         back() const;
      void                    push_back(const value_type& x);
      //void                  push_back(value_type&& x);
      void	                  pop_back();
      iterator                insert(const_iterator position, const value_type& x);
      //iterator insert(const_iterator position, value_type&& x);
      iterator                insert(const_iterator position, size_type n, const value_type& x);
      template <class InputIterator>
          iterator            insert(const_iterator position, InputIterator first, InputIterator last);
      iterator                insert(const_iterator position, initializer_list<value_type> il);
      iterator                erase(const_iterator position);
      iterator                erase(const_iterator first, const_iterator last);
      void                    clear();
      void                    resize(size_type sz);
      void                    resize(size_type sz, const value_type& c);
      void                    swap(vector&);
      void	                  reserve(size_type n);
      */
      //bool        __invariants() const;
  };
}
