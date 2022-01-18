#pragma once


namespace ft
{
    template <typename T>
    class node
    {
    public:
        V value;
	    node *left;
	    node *right;
	    node *parent;
        bool last;

        node(void) : value(NULL), left(NULL), right(NULL), parent(NULL), last(NULL) {}
        node(V v, node *l, node *r, node *p, bool e = false) : value(v), left(l), right(r), parent(p), last(e) {}
	    virtual ~node() {}

        node(const T &src) : value(data.value), left(data.left), right(data.right), parent(data.parent), last(data.last)  {}

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