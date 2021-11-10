#pragma once 

#include <cstddef>//ptrdiff_t
#include <iterator>//On a en besoin pour random_access_iterator_tag

/*
** Documentation 
** https://en.cppreference.com/w/cpp/iterator/iterator
*/
namespace ft
{
    template<typename T>
    class vector_iterator
    {
    public:
        typedef T											value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef std::random_access_iterator_tag				iterator_category;
		//typedef vector_iterator							iterator;
		//typedef vector_iterator<const T>					const_iterator;
    protected:
        value_type *_p;
    public:
        vector_iterator() : _p(NULL) {}
		vector_iterator(value_type &x) : _p(&x) {}
		vector_iterator(value_type *x) : _p(x) {}
		vector_iterator(const iterator &x) {_p = x._p; return *this;}
		virtual ~vector_iterator(void) {}

        vector_iterator & operator=(vector_iterator const &rhs)
        {
            _p = rhs._p;
            return (*this);
        }

        value_type  *get_ptr(void) const
        {
            return (this->_p);
        }

        /*
        ** revoir cet operateur 
        ** A tester
        */
        operator vector_iterator<value_type const>(void) const
        {
            return (vector_iterator<value_type const>(_p))
        }

        /*
        ** Surcharge des operateurs 
        ** https://docs.microsoft.com/fr-fr/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170
        */

       /*
       ** post-incrementation
       */
       vector_iterator &operator++()
       {
           this->_p++;
           return (*this);
       }

       /*
       ** pre-incrementation
       ** revoir pourquoi il faut mettre int en argument
       */
      vector_iterator operator++(int)
      {
        vector_iterator it = *this;
        (this->p)++;
        return (it);
      }

      /*
      ** post decrementation
      */
      vector_iterator &operator--()
      {
          this->_p--;
          return (*this);
      }

    /*
    ** pre decrementation
    */
    vector_iterator operator--(int)
    {
        vector_iterator it = *this;
        (*this)--;
        return it;
    }

    value_type &operator[](int index)
    {
        return *(this->_p + index);
    }

    value_type *operator->()
    {
        return (get_ptr());
    }

    /*
    ** Operateur derefencement
    */
    value_type &operator*()
    {
        return (*this->_p;)
    }

    bool operator==(const vector_iterator &other) const 
    {
        return (this->_p == other._p);
    }

    bool operator!=(const vector_iterator &other) const
    {
        return (this->_p != other._p);
    }

    bool operator<(const vector_iterator &other) const 
    {
        return (this->_p < other._p);
    }

    bool operator<=(const vector_iterator &other) const 
    {
        return (this->_p <= other._p);
    }

    bool operator>(const vector_iterator &other) const 
    {
        return (this->_p > other._p);
    }

    bool operator>=(const vector_iterator &other) const 
    {
        return (this->_p >= other._p);
    }

    //friend ?
    /*
    vector_iterator<T> operator+(difference_type n, const vector_iterator &rhs)
    {
        return (n + rhs._p);
    }*/

    vector_iterator<T> operator+(difference_type n) const 
    {
        return (this->_p + n);
    }

    vector_iterator<T> operator-(difference_type n) const 
    {
        return (this->_p - n);
    }

    difference_type operator-(const vector_iterator &rhs) const 
    {
        return (this->_p - rhs._p);
    }

    vector_iterator<T> operator+=(difference_type n) const 
    {
        return (this->_p += n);
    }

    vector_iterator<T> operator+-=(difference_type n) const 
    {
        return (this->_p -= n);
    }

    //overload du << ici ?
    //friend ?
    };

    template<typename it1, typename it2>
    bool operator==(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        return (a.get_ptr() == b.get_ptr());
    }

    template<typename it1, typename it2>
    bool operator!=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        return (a.get_ptr() != b.get_ptr());
    }

    template<typename it1, typename it2>
    bool operator<(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        return (a.get_ptr() < b.get_ptr());
    } 

    template<typename it1, typename it2>
    bool operator<=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        return (a.get_ptr() <= b.get_ptr());
    }   

    template<typename it1, typename it2>
    bool operator>(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        return (a.get_ptr() > b.get_ptr());
    }

    template<typename it1, typename it2>
    bool operator>=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        return (a.get_ptr() >= b.get_ptr());
    }  
}