#pragma once 

#define DEBUG 0
/*
** This binary three will be used in the map container
*/

#include "utils.hpp"

namespace ft
{
    template<typename T>
    class node
    {
    public:

        typedef T   value_type;
        /*
        ** Forme canonique necessaire
        */
       node(): _value(NULL), _left(NULL), _right(NULL), _parent(NULL)
       {
           if (DEBUG)
            {
                std::cout << "node constructor called" << std::endl;
            }
       }
       node(value_type *ptr): _value(ptr), _left(NULL), _right(NULL), _parent(NULL)
       {
           if (DEBUG)
           {
               std::cout << "node pointer parameter constructor called" << std::endl;
           }
       }
       node(const node &src): _value(src._value), _left(src.left), _right(src.right), _parent(src.parent)
       {
           if (DEBUG)
           {
               std::cout << "node copy constructor called" << std::endl;
           }
       }

        /*
        ** TODO: checker que tous les destructeurs sont bien virtual
        */
        virtual ~node()
        {
            if (DEBUG)
            {
                std::cout << "node destructor called" << std::endl;
            }
        }

       /*
       ** Accessors (ajouts persos)
       */
        value_type *getValueType() const
        {
            value_type *ret = this->_value;
            //A tester
            if (DEBUG)
            {
                std::cout << "the value type is " << *ret << std::endl;
            }
            return (ret);
        }
        node *getLeft() const 
        {
            node *left = this->_left;
            if (DEBUG)
            {
                std::cout << "the left node is " << *left << std::endl; 
            }
            return (left);
        }

        node *getRight() const
        {
            node *right = this->_right;
            if (DEBUG)
            {
                std::cout << "the right node is " << *left << std::endl; 
            }
            return (right);
        }

        node    *getParent() const
        {
            node *parent = this->_parent;
            if (DEBUG)
            {
                std::cout << "The parent node is" << *parent << std::endl;
            }
            return (parent);
        }
        /*
        ** Faire les setters?
        */
    protected:
        typedef T   value_type;
        value_type  *_value;
        node        *_left;
        node        *_right;
        node        *_parent;
    };
}