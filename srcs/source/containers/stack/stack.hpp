#pragma once

//TODO: ajouter include

/*
namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef std::size_t size_type;

    protected:
        container_type _container;

    public:
        stack(const container_type &container = container_type()) : _container(container)
        {
            if (DEBUG == 1)
                std::cout << "Stack default constructor called" << std::endl;
        }
        virtual ~stack()
        {
            if (DEBUG == 1)
                std::cout << "stack destructor called" << std::endl;
        }

        bool empty() const
        {
            bool ret = this->_container.empty();
            if (DEBUG == 1)
            {
                std::cout << "empty function called" << std::endl;
                std::cout << "the result is " << ret << std::endl;
            }
            return (ret);
        }

        size_type size() const
        {
            size_type size = this->_container.size();
            if (DEBUG == 1)
            {
                std::cout << "Size function called" << std::endl;
                std::cout << "The size is " << size << std::endl;
            }
            return (size);
        }

        value_type &top()
        {
            value_type top = this->_container.back();
            if (DEBUG == 1)
            {
                std::cout << "Top function called" << std::endl;
                std::cout << "the top is " << top << std::endl;
            }
            return (top);
        }

        const value_type &top() const
        {
            value_type top = this->_container.back();
            if (DEBUG == 1)
            {
                std::cout << "Top const function called" << std::endl;
                std::cout << "the top is " << top << std::endl;
            }
            return (top);
        }

        void push(const value_type &val)
        {
            value_type &ref = this->_container.push_back(val);
            if (DEBUG == 1)
            {
                std::cout << "map push function called" << std::endl;
                std::cout << "the ref returned is " << ref << std::endl;
            }
            return (ref);
        }

        void pop()
        {
            if (DEBUG == 1)
            {
                std::cout << "map pop function called" << std::endl;
                std::cout << this->top() << "will be popped" << std::endl;
            }
            this->_container.pop_back();
        }
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._container == rhs._container;
        if (DEBUG == 1)
        {
            std::cout << "map operator == called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._container != rhs._container;
        if (DEBUG == 1)
        {
            std::cout << "map operator != called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._container < rhs._container;
        if (DEBUG == 1)
        {
            std::cout << "map operator < called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._container <= rhs._container;
        if (DEBUG == 1)
        {
            std::cout << "map operator <= called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._container > rhs._container;
        if (DEBUG == 1)
        {
            std::cout << "map operator > called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._container >= rhs._container;
        if (DEBUG == 1)
        {
            std::cout << "map operator >= called" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (ret);
    }
}
*/