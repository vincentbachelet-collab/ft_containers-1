#pragma once

#includes "../../../includes/includes.hpp"

namespace ft
{
    template<typename T>
    class node
    {
    /*
    ** Ajouter getters et setters ?
    */
    protected:
        T       *_data;
        node    *_previous;
        node    *_next;
    public:
        node(void): _data(0), _previous(NULL), _next(NULL)
        {
            if (DEBUG)
            {
                std::cout << "node default constructor called" << std::endl;
            }
        }
        node(const T &data): _data(&data), _previous(NULL), _next(NULL)
        {
            if (DEBUG)
            {
                std::cout << "node copy constructor called" << std::endl;
            }
        }
        node(T &src, node *previous, node *next): _data(&src), previous(previous), next(next)
        {
            if (DEBUG)
            {
                std::cout << "node custom constructor called" << std::endl;
            }
        }
        /*
        ** Destructeur
        */
        virtual node(void)
        {
            if (DEBUG)
            {
                std::cout << "node destructor called" << std::endl;
            }
        }

        node &operator=(const node &src)
        {
            //Protection si this == &src 
            if (this != &src)
            {
                this->_data = src.data;
                this->_previous = src.previous;
                this->_next = src.next;
            }
            return (*this);
        }

        /*
        ** Operateur pour caster en const
        */
       operator node<const T>()
       {
           if (DEBUG)
               std::cout << "node const cast invoked" << std::endl;
           return node<const T>(reinterpret_cast<const T*>(data),
                                reinterpret_cast<ft::node<const T*>(previous),
                                reinterpret_cast<ft::node<const T*>(next));
       }
    };
}