#pragma once 

/*
** The true map container is defined in header <map>
** https://en.cppreference.com/w/cpp/container/map
** 
*/

#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "./binary_three.hpp"
#include "./vector.hpp"

#include <functional>

#define DEBUG 0
#define ENVIRONNEMENT 64
//#include <iostream>

/*
** Faire une classe node ?
*/

/*
** std::less is defined in <functional>
** "function object for performing comparisons"
** Unless specialized, invokes operator < on type T. 
** TO DO: est-ce qu'il faut faire un ft less ?
*/
namespace ft
{
    /*
    ** Compare argument default to std::less 
    ** which invokes operator < on type T
    */
    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        /*
        ** https://en.cppreference.com/w/cpp/utility/functional/binary_function
        ** https://www.cplusplus.com/reference/functional/binary_function/
        ** define in header <functional>
        ** binary_function is a base class for creating function objects with two arguments.
        */
        /*
        ** binary_function does not define operator(); it is expected that derived classes will define this. 
        ** binary_function provides only three types - first_argument_type, second_argument_type and result_type
        ** defined by the template parameters.
        */

        /*
        ** pour expliquer les "binary function" l'exemple de compare est souvent repris.
        ** L'idee de d'overloader l operateur() pour creer une fonction qui prendra uniquement 2 parametres
        ** l'overload() n'est jamais defini dans la classe binary function, 
        ** libre au developpeur de l implementer comme il le souhaite.
        ** TODO: a tester + retrouver le code source
        */
        struct value_compare : public std::binary_function<value_type, value_type, bool>
        {
        protected:
            Compare _comp;
        public:
            value_compare(Compare comp): _comp(comp)
            {
                if (DEBUG)
                {
                    std::cout << "value compare default constructor invoked" << std::endl;
                }
            }
            value_compare(Compare comp): _comp(comp)
            {
                if (DEBUG)
                {
                    std::cout << "value compare parameter constructor invoked" << std::endl;
                }
            }
            /*
            ** Je ne comprend pas cette implementation
            */
            bool operator()(const value_type &first, const value_type &second) const
            {
                std::cout << "compare operator() invoked" << std::endl;
                return (this->_comp(first.first, second.first));
            }
            typedef bool result_type;
            typedef value_type  first_argument_type;
            typedef value_type second_argument_type;
        };

        typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef ft::map_iterator<value_type>			iterator;
		typedef ft::map_iterator<const value_type>		const_iterator;
		typedef ft::reverse_iterator< iterator >		reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
        //revoir pour le nom node ou btree
		typedef ft::node<value_type>					btree_type;
		typedef ft::node<const value_type>				const_btree_type;                  const_reverse_iterator;
    
    protected:
        /*
        ** Probleme syntaxique sur le node allocator ?
        ** et le size type
        */
        btree_type		_root;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_allocator;
    
    public:
        /*
        ** https://en.cppreference.com/w/cpp/container/map/map 
        */
        /*
        ** Constructeur 1 - empty
        ** J'ai retire le mot cle explicit puisqu il ne fait pas partie du standard 98.
        */
        map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _alloc(alloc), _key_cmp(comp), _size(0), _root(NULL)
        {
            if (DEBUG)
            {
                std::cout << "map default constructor called" << std::endl;
            }
        }
        /*
        ** Constructeur 2 - range
        ** Constructs the container with the contents of the range [first, last]
        */
       template <class InputIt>
       map (InputIt first, InputIt last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _root(btree_type()), _size(0), _comp(comp), _allocator(alloc)
        {
            if (DEBUG)
            {
                std::cout << "map range constructor called" << std::endl;
            }
			insert(first, last);
		}
        /*
        ** Capacity
        */
        bool empty() const
        {
            if (this->_size)
            {
                if (DEBUG)
                {
                    std::cout << "the map is not empty" << std::endl;
                }
                return (false);
            }
            if (DEBUG)
            {
                std::cout << "the map is empty" << std::endl;
            }
            return (true);
        }

        /*
        ** Size
        */
        size_type size() const
        {
            size_type s = this->_size;
            if (DEBUG)
            {
                std::cout << "the size is " << s << std::endl;
            }
            return (s);
        }
        /*
        ** max_size()
        ** https://en.cppreference.com/w/cpp/container/map/max_size
        ** Returns the maximum number of elements the container is able to hold 
        ** due to system or library implementation limitations, i.e. std::distance(begin(), end()) for the largest container.
        */
        size_type max_size() const
        {
            //voir dans quelle librairie se trouve pow
            return (pow(2, ENVIRONNEMENT) - 1.0) / (sizeof(value_type) + sizeof(ft::node<value_type>))));
        }

        /*
        ** Modifiers
        */
        
        /*
        ** https://www.cplusplus.com/reference/map/map/insert/
        ** Extends the container by inserting new elements, 
        ** effectively increasing the container size by the number of elements inserted.
        ** Because element keys in a map are unique, the insertion operation checks whether each inserted element has a 
        ** key equivalent to the one of an element already in the container, and if so, the element is not inserted, 
        ** returning an iterator to this existing element (if the function returns a value).
        */
        pair<iterator, bool> insert(const value_type &src)
        {
            size_type save = this->_size;
            insert_node_check_root(val, this->_root);
            //reprendre
        }

        /*
        ** Iterateur
        */
        /*
        ** Begin
        ** besoin de empty, end pour faire begin pour faire insert pour faire le constructeur fill
        */
        iterator begin()
        {
            if (empty())
            {
                if (DEBUG)
                {
                    std::cout << "begin is invoked but the map is empty" << std::endl;
                }
                return(end());
            }
            iterator it = this->_first;
            if (DEBUG)
            {
                std::cout << "begin is invoked, the value is " << *it << std::endl;
            }
            return (it);
        }

        /*
        ** Const begin()
        */
        const_iterator begin() const 
        {
            if (empty())
            {
                if (DEBUG)
                {
                    std::cout << "const begin is invoked but the map is empty" << std::endl;
                }
                return(end());
            }
            const_iterator it = const_iterator(reinterpret_cast<const_btree_type *>(_first()));
            if (DEBUG)
            {
                std::cout << "const begin is invoked, the value is " << *it << std::endl;
            }
            return (it);
        }

        /*
        ** End
        */
        iterator end()
        {
            /*
            //Pas super opti
            iterator it = iterator(_root);
            if (DEBUG)
            {
                std::cout << "end function invoked, the value is " << *it << std::endl;
            }
            return (it);
            */
           if (!this->_root)
           {
               initialize();
           }
           //reprendre
        }

        /*
        ** const_end
        */
        const_iterator end() const
        {
            /*
            if (this->empty())
            {
                if (DEBUG)
                {
                    std::cout << "end function called, the map is empty so an iterator will be constructed" << std::endl;
                }
                return(const_iterator());
            }
            const_iterator it = const_iterator(reinterpret_cast<const_btree_type *>(_root.left->parent)));
            */
        }

        /*
        ** Besoin d'avoir begin pour pouvoir faire insert
        */
        template<class InputIt>
        void insert(InputIt first, InputIt last)
        {
            iterator it = this->begin();
        }
    private:
        void initialize()
        {
            //Ajout d'un nouvel element 
            insert(value_type(key_type(), mapped_type()));
            //On indique qu'il s'agit d'une leaf ?
            this->_root->last = true;
            this->_size--;
        }
    };
    /*
    ** Non member function overloads
    */
   template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
		if (lhs.size() != rhs.size())
        {
            std::cout << "operator== invoked, will return false because sizes are different" << std::endl;
            return false;
        }
        //Appel de std::equal
        //A tester
        bool res = equal(lhs.begin(), lhs.end(), rhs.begin());
        if (DEBUG)
        {
            std::cout << "std::equal called, res is " << res << std::endl;
        }
		return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
    {
        bool res = !(lhs == rhs);
        if (DEBUG)
        {
            std::cout << "operator != called, the result is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res = lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end();
        if (DEBUG)
        {
            std::cout << "operator < called, the res is " << res << std::endl;
        }
        return (res);
	}
    template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
    {
        bool res1 = lhs < rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        if (DEBUG)
        {
            std::cout << "operator<= called, res1 is " << res1 << ", res2 is " << res2 << ", so the result is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
    {
        bool res = rhs > lhs;
        if (DEBUG)
        {
            std::cout << "operator > invoked, the res is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res1 = lhs > rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        if (DEBUG)
        {
            std::cout << "operator>= invoked, res1 is " << res1 << ", res2 is " << res2 << ", so the result is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
    {
        bool res = rhs < lhs;
        if (DEBUG)
        {
            std::cout << "operator < invoked, the res is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res1 = lhs < rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        if (DEBUG)
        {
            std::cout << "operator<= invoked, res1 is " << res1 << ", res2 is " << res2 << ", so the result is " << res << std::endl;
        }
        return (res);
    }

    /*
    ** Non member function swap
    */
    template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
    {
        if (DEBUG)
        {
            std::cout << "swap non member function invoked" << std::endl;
        }
        x.swap(y);
    }
}