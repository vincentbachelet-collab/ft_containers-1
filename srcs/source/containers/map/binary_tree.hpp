#pragma once

/**
 * @brief : This binary three will be used in the map container
*/

//TODO: ajouter include

namespace ft
{
    template <typename T>
    class btree
    {
    public:
        typedef T value_type;
        btree() : _value(NULL), _left(NULL), _right(NULL), _parent(NULL)
        {
            if (DEBUG == 1)
                std::cout << "btree constructor called" << std::endl;
        }

        btree(value_type *ptr) : _value(ptr), _left(NULL), _right(NULL), _parent(NULL)
        {
            if (DEBUG == 1)
                std::cout << "btree pointer parameter constructor called" << std::endl;
        }

        btree(const node &src) : _value(src._value), _left(src.left), _right(src.right), _parent(src.parent)
        {
            if (DEBUG == 1)
                std::cout << "btree copy constructor called" << std::endl;
        }

        /**
        ** TODO: checker que tous les destructeurs sont bien virtual
        */
        virtual ~btree()
        {
            if (DEBUG == 1)
                std::cout << "btree destructor called" << std::endl;
        }

        value_type *getValueType() const
        {
            value_type *ret = this->_value;
            if (DEBUG == 1)
                std::cout << "the value type is " << *ret << std::endl;
            return (ret);
        }
        btree *getLeft() const
        {
            btree *left = this->_left;
            if (DEBUG == 1)
                std::cout << "the left btree is " << *left << std::endl;
            return (left);
        }

        btree *getRight() const
        {
            btree *right = this->_right;
            if (DEBUG == 1)
                std::cout << "the right bree is " << *left << std::endl;
            return (right);
        }

        btree *getParent() const
        {
            btree *parent = this->_parent;
            if (DEBUG == 1)
                std::cout << "The parent btree is" << *parent << std::endl;
            return (parent);
        }

    protected:
        typedef T value_type;
        value_type *_value;
        btree *_left;
        btree *_right;
        btree *_parent;
    };
}