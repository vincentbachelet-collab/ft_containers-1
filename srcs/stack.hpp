#pragma once 

#include <deque>
#include <iostream>
#include "./vector.hpp"

#define DEBUG 0

namespace ft
{
    /*
    ** documentation officielle
    ** defined in header stack
    ** https://en.cppreference.com/w/cpp/container/stack
    ** les deque, contrairement aux vectors, ne sont pas stockés
    ** de maniere contigue.
    ** Dans le sujet il nous est explictement interdit
    ** d'utiliser les containers de la sdl.
    ** Notre implementation de stack est donc largemment differente de la vraie.
    */
   template<class T,class Container = ft::vector<T> > 
   class stack
   {
    /*
    ** Attention il faut bien regarder la doc de cpluplus.com
    ** car en regarant l'autre on peut penser que le standard 98
    ** contient plus d'attributs membres.
    */
    public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef std::size_t	size_type;
    
    //TO DO: verifier si c'est bien protected
    protected:
        container_type _container;
    
    public:
        /*
        ** Classe canonique, constructeur
        */
        stack(const container_type &container = container_type()): _container(container)
        {
            if (DEBUG)
            {
                std::cout << "Stack default constructor called" << std::endl;
            }
        }
        /*
        ** destructeur
        */
       virtual ~stack()
       {
            if (DEBUG)
            {
                std::cout << "stack destructor called" << std::endl;
            }
       }

       /*
       ** Fonctions membres
       */

      /*
      ** Empty : test wether container is empty or not 
      */
        bool empty() const
        {
            bool ret = this->_container.empty();
            if (DEBUG)
            {
                std::cout << "empty function called" << std::endl;
                std::cout << "the result is " << ret << std::endl;
            }
            return (ret);
        }

        /*
        ** Size
        ** Will call the size function on container member attribute
        */
       size_type size() const
       {
           size_type size = this->_container.size();
           if (DEBUG)
           {
               std::cout << "Size function called" << std::endl;
               std::cout << "The size is " << size << std::endl;
           }
           return (size);
       }
   };
}