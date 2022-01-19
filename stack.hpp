#pragma once

#include "vector.hpp"

namespace ft
{
    //Super tutoriel: https://www.youtube.com/watch?v=GBST5uQ_yos
    //https://www.cplusplus.com/reference/stack/stack/
    //Stack are type of container adaptor, specially designed to operated in a LIFO context.
    template <class T, class Container = vector<T> >
    class stack
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef typename container_type::size_type size_type;

    protected:
        container_type _under_container;

    public:
        container_type get_under_container() const
        {
            return (this->_under_container);
        }

        stack(const container_type &container = container_type()) : _under_container(container) {}
        virtual ~stack() {}

        bool empty() const
        {
            bool ret = this->_under_container.empty();
            return (ret);
        }

        size_type size() const
        {
            size_type size = this->_under_container.size();
            return (size);
        }

        value_type &top()
        {
            value_type &top = this->_under_container.back();
            return (top);
        }

        value_type &top() const
        {
            value_type &top = this->_under_container.back();
            return (top);
        }

        void push(value_type const &val)
        {
            this->_under_container.push_back(val);
        }

        void pop()
        {
            this->_under_container.pop_back();
        }
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs.get_under_container() == rhs.get_under_container();
        return (ret);
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs.get_under_container() != rhs.get_under_container();
        return (ret);
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs.get_under_container() < rhs.get_under_container();
        return (ret);
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs.get_under_container() <= rhs.get_under_container();
        return (ret);
    }

    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs.get_under_container() > rhs.get_under_container();
        return (ret);
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs.get_under_container() >= rhs.get_under_container();
        return (ret);
    }
}