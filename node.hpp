#pragma once

//AVL tree
//https://fr.wikipedia.org/wiki/Arbre_AVL
namespace ft
{
    template <typename T>
    class node
    {
    public:
        T value;
        node *left;
        node *right;
        node *parent;
        bool last;//util perso

        node(void) : value(NULL), left(NULL), right(NULL), parent(NULL), last(false) {}
        node(T v, node *l, node *r, node *p, bool e = false) : value(v), left(l), right(r), parent(p), last(e) {}
        virtual ~node() {}

        node(const T &src) : value(src.value), left(src.left), right(src.right), parent(src.parent), last(src.last) {}

        node &operator=(const node &src)
        {
            if (this != &src)
            {
                this->_value = src.value;
                this->_left = src.left;
                this->_right = src.right;
                this->_parent = src.parent;
            }
            return (*this);
        }
    };
}