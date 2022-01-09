#pragma once

//TODO: rajouter le include

namespace ft
{
    /*
    ** https://en.cppreference.com/w/cpp/utility/pair
    */
    //types of the elements in the pair
    template <class T1, class T2>
    class pair
    {
        /* voir s'il faut mieux de mettre en prive */
    public:
        typedef T1 first_type;
        typedef T2 second_type;

    private:
        first_type first;
        second_type second;

        /* Classe canonique */
    public:
        //TO DO: ajouter des fonctions de debug
        pair() {}

        template <typename U, typename V>
        pair(const pair<U, V> &ref) : first(ref.first), second(ref.second)
        {
            if (DEBUG == 1)
                std::cout << "Pair second constructor called" << std::endl;
        }

        pair(const first_type &a, const second_type &b) : first(a), second(b)
        {
            if (DEBUG == 1)
                std::cout << "Pair third constructor called" << std::endl;
        }

        virtual ~pair()
        {
            if (DEBUG == 1)
                std::cout << "Pair destructor called" << std::endl;
        }

        pair &operator=(const pair &src)
        {
            this->first = src.first;
            this->second = src.second;
            return (*this);
        }
    };

    template <typename T1, typename T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <typename T1, typename T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (!(lhs == rhs));
    }

    template <typename T1, typename T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template <typename T1, typename T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs > rhs);
    }

    template <typename T1, typename T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs <= rhs);
    }

    template <typename T1, typename T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs >= rhs);
    }
}