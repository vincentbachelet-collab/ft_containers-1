#pragma once 

//#include "./map.hpp"
#include <iterator>
#include <iostream>
#include <algorithm>
#include <string>

//revoir la faute d orthographe a tree
#include "./binary_three.hpp"

#define DEBUG 0

/*
** Dans une map on va iterer sur first et second
** puisqu'il s'agit de key value pairs.
*/
namespace ft
{
    /*
    ** https://thispointer.com/how-to-iterate-over-a-map-in-c/
    */
    //TODO: revoir le code source
   template<typename T>
   class map_iterator
   {
    public:
        typedef T											value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef map_iterator								iterator;
        /* Voir si je peux les appeler node ou si ca doit etre btree */
		typedef ft::node<T>								    node;
		typedef ft::node<const T>						    const_node;
    private:
        node *_node;
    public:
        /*
        ** Constructeurs
        */
        map_iterator(): _node(0)
        {
            if (DEBUG)
            {
                std::cout << "map iterator default constructor invoked" << std::endl;
            }
        }
        /*
        ** Constreur par pointeur
        */
        map_iterator(node *ptr): _node(ptr)
        {
            if (DEBUG)
            {
                std::cout << "map_iterator pointer constructor invoked" << std::endl;
            }
        }
        /*
        ** Constructeur par reference
        */
       map_iterator(node &ref): _node(&ref)
       {
           if (DEBUG)
           {
               std::cout << "map_iterator reference constructor invoked" << std::endl;
           }
       }
       /*
       ** Constructeur par copie
       */
      map_iterator(const iterator &src)
      {
          this->_node = src._node;
          if (DEBUG)
          {
              std::cout << "map_iterator copy constructor invoked" << std::endl;
          }
      }
      /*
      ** destructeur (virtual ?)
      */
      ~map_iterator()
      {
          std::cout << "map_iterator destructor invoked" << std::endl;
      }

      /*
      ** Operateur d'assignation
      ** TODO: faire des setters
      */
     iterator &operator=(const iterator &src)
     {
         this->_node = src._node;
         if (DEBUG)
         {
             std::cout << "map_iterator assignation operator invoked" << std::endl
         }
         return (*this);
     }

     /*
     ** Operateur de cast ?
     ** TODO: verifier si necessaire dans la doc
     */
     operator map_iterator<const T>()
     {
         if (DEBUG)
         {
             std::cout << "map_iterator cast operator invoked" << std::endl;
         }
         return (map_iterator<const T>(reinterpret_cast<const_node *>(this->_node)))
     }

    /*
    ** Operateur de derefencement / access pointed to
    */
     reference  operator*() const
     {
         reference ref = *(this->_node->value);
         if (DEBUG)
         {
             std::cout << "map_iterator operator* invoked" << std::endl;
             std::cout << "the ref is " << ref << std::endl;
         }
         return (ref);
     }

    /*
    ** Operateur d'acces au pointeur 
    ** TODO: revoir nom exacte
    */
     pointer  operator->() const
     {
         pointer ref = (this->_node->value);
         if (DEBUG)
         {
             std::cout << "map_iterator operator* invoked" << std::endl;
             std::cout << "the ref is " << ref << std::endl;
         }
         return (ref);
     }

     /*
     ** Operateur d'incrementation de l iterateur
     ** post incrementation
     ** A tester
     */
    iterator &operator++()
    {
        if (DEBUG)
        {
            std::cout << "map_iterator operator++ invoked" << std::endl;
        }
        this->increment();
        return (*this);
    }
    /*
    ** Operateur pre incrementation
    */
   iterator operator++(int)
   {
       if (DEBUG)
       {
           std::cout << "map_iterator operator-- invoked" << std::endl;
       }
       iterator it = (*this);
       ++(*this);
       return (it);
   }

   /*
   ** Operateur post decrementation
   */
     iterator &operator--()
    {
        if (DEBUG)
        {
            std::cout << "map_iterator operator-- invoked" << std::endl;
        }
        this->decrement();
        return (*this);
    }
    /*
    ** Operateur pre decrementation
    */
    iterator operator--(int)
   {
       if (DEBUG)
       {
           std::cout << "map_iterator operator-- invoked" << std::endl;
       }
       iterator it = (*this);
       --(*this);
       return (it);
   }
   /*
   ** Accessor
   */
    node get_node()
    {
        node n = this->_node;
        if (DEBUG)
        {
            std::cout << "this->node is equal to " << node << " and its value is " << *node << std::endl;
        }
        return (n);
    }

    node get_node() const 
    {
        node n = this->_node;
        if (DEBUG)
        {
            std::cout << "this->node is equal to " << node << " and its value is " << *node << std::endl;
        }
        return (n);
    }
    /*
    ** Operateur de comparaison (membre)
    */
    bool operator==(const map_iterator<it2, node> &rhs)
    {
        bool res = this->_node == rhs.get_node();
        if (DEBUG)
        {
            std::cout << "map_iterator member operator== invoked" << std::endl;
            std::cout << "the result is " << res << std::endl;
        }
        return (res);
    }

    bool operator!=(const map_iterator<it2, node> &rhs)
    {
        bool res = this->_node != rhs.get_node();
        if (DEBUG)
        {
            std::cout << "map_iterator member operator!= invoked" << std::endl;
            std::cout << "the result is " << res << std::endl;
        }
        return (res);
    }
    /*
    /*
    ** Tutoriel sur les deplacements sans un arbre binaire
    */
    protected:
        void increment()
        {
            if (DEBUG)
            {
                std::cout << "increment function called" << std::endl;
            }
            if (this->_node->right)
            {
                if (DEBUG)
                {
                    std::cout << "this->_node->right is not null" << std::endl;
                }
                this->_node = this->node->right;
                while (this->_node->_left)
                {
                    this->_node = this->_node->left;
                }
            }
            else
            {
                if (DEBUG)
                {
                    std::cout << "this->_node->right is null" << std::endl;
                }
                node tmp = this->_node;
                this->_node = this->_node->parent;
                while (this->_node->left != tmp)
                {
                    tmp = this->_node;
                    this->_node = this->_node->parent;
                }
            }
        }

        void decrement()
        {
            if (DEBUG)
            {
                std::cout << "decrement function called" << std::endl;
            }
            if (this->_node->left)
            {
                if (DEBUG)
                {
                    std::cout << "this->_node->left is not null" << std::endl;
                }
                this->_node = this->_node->left;
                while (this->_node->right)
                {
                    this->_node = this->_node->right;
                }
            }
            else
            {
                std::cout << "this->_node->left is null" << std::endl;
                node tmp = this->_node;
                this->_node = this->_node->parent;
                while (this->_node->right != tmp)
                {
                    tmp = this->_node;
                    this->_node = this->_node->parent;
                }
            }
        }
   };
   /*
   ** Operateur de comparaisons
   **TODO: trouver la doc ou le code source
   ** A tester
   */
    template<typename map_iterator>
    bool operator==(const map_iterator &one, const map_iterator &two)
    {
        bool res = one._node == two._node;
        if (DEBUG)
        {
            std::cout << "non member operator== invoked" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (res);
    }

    template<typename map_iterator>
    bool operator!=(const map_iterator &one, const map_iterator &two)
    {
        bool res = one._node != two._node;
        if (DEBUG)
        {
            std::cout << "non member operator!= invoked" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (res);
    }
}