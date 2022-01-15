#pragma once

//TODO: rajouter include

namespace ft
{
    template <typename T>
    class map_iterator
    {
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef map_iterator iterator;
        typedef ft::node<T> node;
        typedef ft::node<const T> const_node;

    private:
        node *_node;

    public:
        map_iterator() : _node(0)
        {
            if (DEBUG == 1)
                std::cout << "map iterator default constructor invoked" << std::endl;
        }

        map_iterator(node *ptr) : _node(ptr)
        {
            if (DEBUG == 1)
                std::cout << "map_iterator pointer constructor invoked" << std::endl;
        }

        map_iterator(node &ref) : _node(&ref)
        {
            if (DEBUG == 1)
                std::cout << "map_iterator reference constructor invoked" << std::endl;
        }

        map_iterator(const iterator &src)
        {
            this->_node = src._node;
            if (DEBUG == 1)
                std::cout << "map_iterator copy constructor invoked" << std::endl;
        }

        ~map_iterator()
        {
            if (DEBUG == 1)
                std::cout << "map_iterator destructor invoked" << std::endl;
        }

        iterator &operator=(const iterator &src)
        {
            this->_node = src._node;
            if (DEBUG == 1)
                std::cout << "map_iterator assignation operator invoked" << std::endl;
            return (*this);
        }

        operator map_iterator<const T>()
        {
            if (DEBUG == 1)
                std::cout << "map_iterator cast operator invoked" << std::endl;
            return (map_iterator<const T>(reinterpret_cast<const_node *>(this->_node)))
        }

        reference operator*() const
        {
            reference ref = *(this->_node->value);
            if (DEBUG == 1)
            {
                std::cout << "map_iterator operator* invoked" << std::endl;
                std::cout << "the ref is " << ref << std::endl;
            }
            return (ref);
        }

        pointer operator->() const
        {
            pointer ref = (this->_node->value);
            if (DEBUG == 1)
            {
                std::cout << "map_iterator operator* invoked" << std::endl;
                std::cout << "the ref is " << ref << std::endl;
            }
            return (ref);
        }

        iterator &operator++()
        {
            if (DEBUG == 1)
                std::cout << "map_iterator operator++ invoked" << std::endl;
            this->increment();
            return (*this);
        }

        iterator operator++(int)
        {
            if (DEBUG == 1)
                std::cout << "map_iterator operator-- invoked" << std::endl;
            iterator it = (*this);
            ++(*this);
            return (it);
        }

        iterator &operator--()
        {
            if (DEBUG == 1)
                std::cout << "map_iterator operator-- invoked" << std::endl;
            this->decrement();
            return (*this);
        }

        iterator operator--(int)
        {
            if (DEBUG == 1)
                std::cout << "map_iterator operator-- invoked" << std::endl;
            iterator it = (*this);
            --(*this);
            return (it);
        }

        node get_node()
        {
            node n = this->_node;
            if (DEBUG == 1)
                std::cout << "this->node is equal to " << node << " and its value is " << *node << std::endl;
            return (n);
        }

        node get_node() const
        {
            node n = this->_node;
            if (DEBUG == 1)
                std::cout << "this->node is equal to " << node << " and its value is " << *node << std::endl;
            return (n);
        }

        bool operator==(const map_iterator<it2, node> &rhs)
        {
            bool res = this->_node == rhs.get_node();
            if (DEBUG == 1)
            {
                std::cout << "map_iterator member operator== invoked" << std::endl;
                std::cout << "the result is " << res << std::endl;
            }
            return (res);
        }

        bool operator!=(const map_iterator<it2, node> &rhs)
        {
            bool res = this->_node != rhs.get_node();
            if (DEBUG == 1)
            {
                std::cout << "map_iterator member operator!= invoked" << std::endl;
                std::cout << "the result is " << res << std::endl;
            }
            return (res);
        }

    protected:
        void increment()
        {
            if (DEBUG == 1)
                std::cout << "increment function called" << std::endl;
            if (this->_node->right)
            {
                if (DEBUG == 1)
                    std::cout << "this->_node->right is not null" << std::endl;
                this->_node = this->node->right;
                while (this->_node->_left)
                {
                    this->_node = this->_node->left;
                }
            }
            else
            {
                if (DEBUG == 1)
                    std::cout << "this->_node->right is null" << std::endl;
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
            if (DEBUG == 1)
                std::cout << "decrement function called" << std::endl;
            if (this->_node->left)
            {
                if (DEBUG == 1)
                    std::cout << "this->_node->left is not null" << std::endl;
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

    template <typename map_iterator>
    bool operator==(const map_iterator &one, const map_iterator &two)
    {
        bool res = one._node == two._node;
        if (DEBUG == 1)
        {
            std::cout << "non member operator== invoked" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (res);
    }

    template <typename map_iterator>
    bool operator!=(const map_iterator &one, const map_iterator &two)
    {
        bool res = one._node != two._node;
        if (DEBUG == 1)
        {
            std::cout << "non member operator!= invoked" << std::endl;
            std::cout << "the res is " << res << std::endl;
        }
        return (res);
    }
}