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
        container_type _vector;

    public:


        stack(const container_type &container = container_type()) : _vector(container) {}
        virtual ~stack() {}

        bool empty() const
        {
            bool ret = this->_vector.empty();
            return (ret);
        }

        size_type size() const
        {
            size_type size = this->_vector.size();
            return (size);
        }

        value_type &top()
        {
            value_type &top = this->_vector.back();
            return (top);
        }

        value_type &top() const
        {
            value_type &top = this->_vector.back();
            return (top);
        }

        void push(value_type const &val)
        {
            this->_vector.push_back(val);
        }

        void pop()
        {
            this->_vector.pop_back();
        }

        template <typename Type, typename Cont>
		friend bool operator==(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator!=(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator<(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator<=(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator>(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator>=(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._vector == rhs._vector ;
        return (ret);
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._vector != rhs._vector;
        return (ret);
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._vector  < rhs._vector ;
        return (ret);
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._vector  <= rhs._vector ;
        return (ret);
    }

    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._vector > rhs._vector ;
        return (ret);
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        bool ret = lhs._vector >= rhs._vector;
        return (ret);
    }
}