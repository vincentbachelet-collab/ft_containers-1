#pragma once 

//#include "../../../includes/includes.hpp"

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

        /*
        ** Top 
        ** http://www.cplusplus.com/reference/stack/stack/top/
        ** returns a reference to the top element (last inserted) in the stack
        ** Effectively calls back of the underlying container object.
        */
        value_type &top()
        {
           value_type top = this->_container.back();
           if (DEBUG)
           {
               std::cout << "Top function called" << std::endl;
               std::cout << "the top is " << top << std::endl;
           }
           return (top);
       }

       /*
       ** Top const
       */
        const value_type &top() const 
        {
            value_type top = this->_container.back();
           if (DEBUG)
           {
               std::cout << "Top const function called" << std::endl;
               std::cout << "the top is " << top << std::endl;
           }
           return (top);
        }

        /*
        ** Push - Insert element
        ** https://www.cplusplus.com/reference/stack/stack/push/
        ** Inserts a new element at the top of the stack, above its current top element. 
        ** The content of this new element is initialized to a copy of val.
        ** Effectively calls push_back of the underlying container
        */
        void push(const value_type &val)
        {
            value_type &ref = this->_container.push_back(val);
            if (DEBUG)
            {
                std::cout << "map push function called" << std::endl;
                std::cout << "the ref returned is " << ref << std::endl;
            }
            return (ref);
        }

        /*
        ** Pop
        ** https://www.cplusplus.com/reference/stack/stack/pop/
        ** Removes the top element, reducing its size by one.
        ** This calls the remove destructor's element
        ** Effectively calls the pop_back function of the underlying container
        */
        void pop()
        {
            if (DEBUG)
            {
                std::cout << "map pop function called" << std::endl;
                std::cout << this->top() << "will be popped" << std::endl;
            }
            this->_container.pop_back();
        }
   };

    /*
    ** Non member function overloads 
    ** Relational operators
    ** https://www.cplusplus.com/reference/stack/stack/operators/
    ** Performs the appropriate comparison operation between lhs and rhs.
    ** Each of these operator overloads calls the same operator on the underlying container objects.
    */
    template <class T, class Container>
    bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        bool ret = lhs._container == rhs._container;
        if (DEBUG)
        {
            std::cout << "map operator == called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        bool ret = lhs._container != rhs._container;
        if (DEBUG)
        {
            std::cout << "map operator != called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        bool ret = lhs._container < rhs._container;
        if (DEBUG)
        {
            std::cout << "map operator < called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        bool ret = lhs._container <= rhs._container;
        if (DEBUG)
        {
            std::cout << "map operator <= called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        bool ret = lhs._container > rhs._container;
        if (DEBUG)
        {
            std::cout << "map operator > called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        bool ret = lhs._container >= rhs._container;
        if (DEBUG)
        {
            std::cout << "map operator >= called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }
}