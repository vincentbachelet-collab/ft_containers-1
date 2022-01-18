#pragma once

#include <memory>
#include "node.hpp"
#include "utils.hpp"
//#include "iterator.hpp"
#include "map_iterator.hpp"
//#include "reverse_iterator.hpp"

#include "functional.hpp"


//Implementation documentation officielle
//TODO: ajouter tests value compare
/* 
namespace ft
{
    template <class Key, class T, class Compare, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map<Key,T,Compare,Allocator>::value_compare
    {
        friend class map;
        protected:
            Compare comp;
            value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
    };
}
*/


//Data collection that stores key value pairs, also often called dictionnary
//https://www.youtube.com/watch?v=aEgG4pidcKU
//https://www.youtube.com/watch?v=GiQnFdbdSbo
/* */
namespace ft
{
    //On met 4 arguments et pas deux car 2 d'entre deux sont presque toujours implicites
    template < class Key,
           class T,
           class Compare = std::less<Key>,
           class Allocator = std::allocator<ft::pair<const Key,T> >
           >
    class map
    {    
            public:
                typedef Key                                                   key_type;
                typedef T                                                     mapped_type;
                typedef ft::pair<const key_type,mapped_type>                  value_type;
                typedef Compare                                               key_compare;
                typedef node<value_type>                                      node_type;
                //Necessaire pour les constructeurs
                class value_compare {
                    friend class map;
                    protected:
                        Compare comp;
                        value_compare (Compare c) : comp(c) {}
                    public:
                        typedef bool result_type;
                        typedef value_type first_argument_type;
                        typedef value_type second_argument_type;
                        bool operator() (const value_type& x, const value_type& y) const {return comp(x.first, y.first);}
                };
                typedef Allocator                                                 allocator_type;
                typedef typename allocator_type::template rebind<node_type>::other node_allocator;
                typedef typename allocator_type::reference                    reference;
                typedef typename allocator_type::const_reference              const_reference;
                typedef typename allocator_type::pointer                      pointer;
                typedef typename allocator_type::const_pointer                const_pointer;
                typedef typename allocator_type::size_type                    size_type;
                typedef typename allocator_type::difference_type              difference_type;
                typedef map_iterator<value_type, node_type*>                  iterator;
                typedef map_iterator<const value_type, node_type*>            const_iterator;
                typedef ft::reverse_iterator<iterator>                        reverse_iterator;
                typedef ft::reverse_iterator<const_iterator>                  const_reverse_iterator;

            
            protected:
                node_allocator _allocator;
                key_compare _key_compare;
                size_type _size;
                node_type *_root;
            
            public:

            map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _allocator(alloc), _key_compare(comp), _size(0), _root(NULL) {}
            //range (2)
            template <class InputIterator>
            map (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _allocator(alloc), _key_compare(comp), _size(0), _root(NULL) {insert(first, last);}
            //copy (3)
            map (const map& x) : _allocator(x._alloc_type), _key_compare(x._key_compare), _size(0), _root(NULL) {*this = x;}
            virtual ~map () {clear_tree(_root);}
            map& operator= (const map& x) {
                clear_tree(_root);
                insert(x.begin(), x.end());
                return *this;
            }

            //Default constructor
            //map (key_compare const &src = key_compare(), const allocator_type &alloc = allocator_type()) : _allocator(alloc), _key_compare(comp), _size(0), _root(NULL) {}
            //Range constructor
            //template <class InputIterator>
            //map (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _key_compare(comp), _size(0), _root(NULL) {insert(first, last);}
            //map (InputIt first, InputIt last)
            //const key_compare &comp = key_compare(),
            //const allocator_type &alloc = allocator_type()) : _allocator(alloc), _key_compare(comp), _size(0), _root(NULL)
            //{
            //    insert(first, last);
            //}

            //Constructeur copy
            
            //map(const map &src) : _root(btree_type()), _size(0), _comp(src._comp), _allocator(src._allocator)
            //{
            //    insert(src.begin(), src.end());
           // }

            size_type   get_size(void)
            {
                return (this->_size);
            }

            void   set_size(size_type n)
            {
                this->_size = n;
            }

            node_type   *get_allocator(void)
            {
                return (this->_root);
            }

            //Fonction de destroy + deallocate recursif / On va supprimer jusqu'au node passe en parametre
            void    clear_tree(node_type *cur)
            {
                //SI j'ai bien au moins une feuille
                if (cur)
                {
                    clear_tree(cur->left);
                    clear_tree(cur->right);
                    //Destroy + deallocate
                    this->_allocator.destroy(cur);
                    this->_allocator.deallocate(cur, 1);
                    if (this->get_size() > 0)
                        this->set_size(this->get_size() + 1);
                    if (cur == this->_root)
                        this->_root = NULL;
                }
            }

            //Va permettre d'ajouter une feuille a l'arbre en mentionnant son parent (sans savoir ou on va le placer)
            node_type* add_node(value_type const &val, node_type *parent)
            {
                //On alloue et on construit le nouveau node
                node_type *temp = _allocator.allocate(1);
                this->_allocator.construct(temp, node_type(val, NULL, NULL, parent, false));
                this->_size++;
                return temp;
            }

            //Pour tester key compare on a besoin des iterateurs
            iterator begin()
            {
                if (this->_size == 0)
                    return (iterator(this->_root));
                node_type * temp = this->_root;
                while (temp && temp->left)
                    temp = temp->left;
                return iterator(temp);
            }

            const_iterator begin() const
            {
                if (this->_size == 0)
                    return (const_iterator(this->_root));
                node_type * temp = _root;
                while (temp && temp->left)
                    temp = temp->left;
                return (const_iterator(temp));
            }

            iterator end()
            {
                //if (!this->_root)
                //    initialize();
                if (this->_size == 0)
                    return (iterator(this->_root));
                node_type * temp = this->_root;
                while (temp && !temp->last)
                    temp = temp->right;
                return (iterator(temp));
            }

            const_iterator end() const
            {
                if (this->_size == 0)
                    return (const_iterator(_root));
                node_type * temp = this->_root;
                while(temp && !temp->last)
                    temp = temp->right;
                return (const_iterator(temp));
            }

            reverse_iterator rbegin()
            {
                return reverse_iterator(end()--);
            }

            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end()--);
            }

	        reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }

	        const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }

            node_type* insert_node_check_root(const value_type& val, node_type *current, node_type *parent = NULL)
            {
                if (!this->_root)//Si l'arbre est vide
                {
                    this->_root = add_node(val, NULL);
                    node_type *last = add_node(value_type(key_type(), mapped_type()), this->_root);
                    _size--;
                    _root->right = last;
                    last->last = true;
                    return _root;
                }
                if (this->_root->last)
                {
                    node_type *new_root = add_node(val, NULL);
                    _root->parent = new_root;
                    new_root->right = _root;
                    _root = new_root;
                    return _root;
                }
                return insert_node(val, current, parent);
            }

            //Tres important
            node_type* position_of_a_key(const key_type& key, node_type* current)
            {
                if (!current || current->last)
                    return NULL;
                if (_key_compare(key, current->value.first))
                    return position_of_a_key(key, current->left);
                else if (_key_compare(current->value.first, key))
                    return position_of_a_key(key, current->right);
                else
                    return current;
            }

            //Necessaire assez rapidement pour les tests
            mapped_type& operator[] (const key_type& k)
            {
                node_type *temp = position_of_a_key(k, _root);
                if (temp)
                    return temp->value.second;
                insert(value_type(k,mapped_type()));
                return position_of_a_key(k, _root)->value.second;
            }


            //Insert, trois versions 
            /* */
            pair<iterator,bool> insert (const value_type& val)
            {
                size_t backup = this->get_size();
                insert_node_check_root(val, _root);
                return (pair<iterator,bool>(position_of_a_key(val.first, _root), backup != _size));
            }


            iterator insert (iterator position, const value_type& val)
            {
                (void)position;
                insert_node_check_root(val, _root);
                return iterator(position_of_a_key(val.first, _root));
            }

            template <class InputIterator>
            void insert (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
            {
                for (;first != last; first++)
                    insert(*first);
            }
        };
}

/*
    protected:
        btree_type _root;
        size_type _size;
        key_compare _comp;
        allocator_type _allocator;

    public:
        map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _allocator(alloc), _comp(comp), _size(0), _root(btree_type())
        {
            if (DEBUG == 1)
                std::cout << "map default constructor called" << std::endl;
        }
        template <class InputIt>
        map(InputIt first, InputIt last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _root(btree_type()), _size(0), _comp(comp), _allocator(alloc)
        {
            if (DEBUG == 1)
                std::cout << "map range constructor called" << std::endl;
            insert(first, last);
        }

        map(const map &src) : _root(btree_type()), _size(0), _comp(src._comp), _allocator(src._allocator)
        {
            if (DEBUG)
                std::cout << "map copy constructor called" << std::endl;
            insert(src.begin(), src.end());
        }

        virtual ~map(void)
        {
            if (DEBUG == 1)
                std::cout << "map destructor called" << std::endl;
            clear();
        }

        map &operator=(const map &src)
        {
            if (DEBUG == 1)
                std::cout << "map assignation operator called" << std::endl;
            if (this != &src)
            {
                this->clear();
                this->_comp = src._comp;
                this->_alloctor = src._allocator;
                this->insert(src.begin(), src.end());
            }
            return (*this);
        }

        bool empty() const
        {
            if (this->_size)
            {
                if (DEBUG == 1)
                    std::cout << "the map is not empty" << std::endl;
                return (false);
            }
            if (DEBUG == 1)
                std::cout << "the map is empty" << std::endl;
            return (true);
        }

        size_type size() const
        {
            size_type s = this->_size;
            if (DEBUG == 1)
                std::cout << "the size is " << s << std::endl;
            return (s);
        }

        size_type max_size() const
        {
            return (pow(2, ENVIRONNEMENT) - 1.0) / (sizeof(value_type) + sizeof(ft::node<value_type>))));
        }

        mapped_type &operator[](const key_type &key)
        {
            mapped_type &mapped = insert(value_type(key).first->second);
            if (DEBUG == 1)
                std::cout << "operator[] invoked and the mapped_type is " << mapped << std::endl;
        }

        pair<iterator, bool> insert(const value_type &val)
        {
            btree_type *cursor = _root.left;
            btree_type *last = &_root;

            while (cursor && cursor->value->first != val.first)
            {
                last = cursor;
                if (key_compare()(val.first, cursor->value->first))
                    cursor = cursor->left;
                else
                    cursor = cursor->right;
            }
            if (!cursor)
            {
                btree_type *node;
                node = create_node(val.first, last, val.second);
                if (last == &_root)
                {
                    last->left = node;
                    last->right = node;
                }
                else if (key_compare()(val.first, last->value->first))
                {
                    last->left = node;
                }
                else
                {
                    last->right = node;
                }
                cursor = node;
                this->_size++;
                return (ft::pair<iterator, bool>(cursos, false)
            }
            return (ft::pair<iterator, bool>(cursos, true);
        }

        iterator insert(iterator position, const value_type &val)
        {
            iterator last = &_root;
            iterator tmp;

            if (position == end() && this->_size())
                position = iterator(position.getNode()->left);
            while (position != this->end() && tmp != position)
            {
                tmp = last;
                last = position;
                if (this->key_comp()(val.first, position->first))
                    position--;
                else if (this->key_comp()(position->first, val.first))
                    position++;
                else
                    return (position);
            }
            btree_type *node = create_node(val.first, val.second);
            if (position == last)
            {
                position.getNode()->left = node;
                position.getNode()->right = node;
            }
            else
            {
                if (position == this->end())
                    ft::swap(position, last);
                if (key_compare()(val.first, position->first))
                {
                    if (position.getNode()->left)
                        (--position).getNode()->right = node;
                    else
                        position.getNode()->left = node;
                }
                else
                {
                    if (position.getNode()->right)
                        (++position).getNode()->left = node;
                    else
                        position.getNode()->right = node;
                }
            }
            node->parent = position.getNode();
            this->_size++;
            return (iterator(node));
        }

        template <class InputIt>
        void insert(InputIt first, InputIt last)
        {
            iterator last_insert = this->begin();
            InputIt it = first;
            while (it < last)
            {
                last_insert = this->insert(last_insert, *it);
                it++;
            }
        }

        void erase(iterator position)
        {
            btree_type *to_erase = position.getNode();
            btree_type *parent = to_erase->parent;
            btree_type *pivot = 0;

            if (to_erase->left)
            {
                pivot = to_erase->left;
                if (to_erase->right)
                {
                    btree_type *cursor = pivot;
                    while (cursor->right)
                        cursor = cursor->right;
                    cursor->right = to_erase->right;
                    cursor->right->parent = cursor;
                }
            }
            else if (to_erase->right)
                pivot = to_erase->right;
            if (pivot)
                pivot->parent = parent;
            if (parent == &_root)
            {
                parent->left = pivot;
                parent->right = pivot;
            }
            else if (parent->left == to_erase)
                parent->left = pivot;
            else
                parent->right = pivot;
            this->delete_node(to_erase);
            _size--;
        }

        size_type erase(const key_type &key)
        {
            iterator it = this->find(key);
            if (it == end())
                return (false);
            this->erase(it);
            return (true);
        }

        void erase(iterator first, iterator last)
        {
            iterator next = first;
            for (iterator it = first; it != last; it = next)
            {
                next++;
                this->erase(it);
            }
        }

        void swap(map &other)
        {
            swap(this->_size, other._size);
            swap(this->_comp, other._comp);
            swap(this->_allocator, other._allocator);
            swap(this->_root.left, other._root.left);
            swap(this->_root.right, other._root.right);
            if (this->_root.left)
                this->_root.left->parent = &this->_root;
            if (other._root.left)
                other._root.left->parent = &other._root;
        }

        key_compare key_comp() const
        {
            return (this->_comp);
        }

        value_compare value_comp() const
        {
            return (value_compare(this->_comp));
        }

        iterator find(const key_type &key)
        {
            btree_type *cursor = this->_root.left;

            while (cursor)
            {
                if (key_compare()(k, cursor->value->first))
                    cursor = cursor->left;
                else if (key_compare()(cursor->value->first, key))
                    cursor = cursor->right;
                else
                    return (iterator(cursor));
            }
            return (end());
        }

        const_iterator find(const key_type &key) const
        {
            btree_type *cursor = this->_root.left;

            while (cursor)
            {
                if (key_compare()(k, cursor->value->first))
                    cursor = cursor->left;
                else if (key_compare()(cursor->value->first, key))
                    cursor = cursor->right;
                else
                    return (const_iterator(reinterpret_cast<const_btree_type *>(cursor)));
            }
            return (end());
        }

        size_type count(const key_type &key) const
        {
            if (this->find(key) != end())
                return (1);
            return (0);
        }

        iterator lower_bound(const key_type &key)
        {
            iterator it = this->begin();
            while (it != this->end() && this->key_comp()(it->first, k))
                it++;
            return (it);
        }

        const_iterator lower_bound(const key_type &k) const
        {
            const_iterator it = this->begin();

            while (it != this->end() && this->key_comp()(it->first, k))
                it++;
            return (it);
        }

        iterator upper_bound(const key_type &key)
        {
            iterator it = this->begin();

            while (it != this->end() && !this->key_comp()(key, it->first))
                it++;
            return (it);
        }

        pair<iterator, iterator> equal_range(const key_type &k)
        {
            iterator it = this->begin();

            while (it != this->end() && (this->key_comp()(it->first, k)))
                it++;
            if (it == this->end() || this->key_comp()(k, it->first))
                return (pair<iterator, iterator>(it, it));
            iterator upper = it;
            return (pair<iterator, iterator>(it, ++upper));
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            const_iterator it = this->begin();

            while (it != this->end() && (this->key_comp()(it->first, k)))
                it++;
            if (it == this->end() || this->key_comp()(k, it->first))
                return (pair<const_iterator, const_iterator>(it, it));
            const_iterator upper = it;
            return (pair<const_iterator, const_iterator>(it, ++upper));
        }

        iterator begin()
        {
            if (empty())
            {
                if (DEBUG == 1)
                    std::cout << "begin is invoked but the map is empty" << std::endl;
                return (end());
            }
            iterator it(this->_first);
            if (DEBUG == 1)
                std::cout << "begin is invoked, the value is " << *it << std::endl;
            return (it);
        }

        const_iterator begin() const
        {
            if (empty())
            {
                if (DEBUG == 1)
                    std::cout << "const begin is invoked but the map is empty" << std::endl;
                return (end());
            }
            const_iterator it(reinterpret_cast<const_btree_type *>(_first()));
            if (DEBUG)
                std::cout << "const begin is invoked, the value is " << *it << std::endl;
            return (it);
        }

        iterator end()
        {
            iterator it = iterator(this->_root);
            if (DEBUG == 1)
                std::cout << "end function called, and the value is " << *it << std::endl;
        }

        const_iterator end() const
        {
            if (this->empty())
            {
                if (DEBUG == 1)
                    std::cout << "end function called, the map is empty so an iterator will be constructed" << std::endl;
                return (const_iterator());
            }
            const_iterator it(reinterpret_cast<const_btree_type *>(_root._left->parent)));
            return (it);
        }

        reverse_iterator rbegin()
        {
            reverse_iterator it(this->_root);
            if (DEBUG == 1)
                std::cout << "rbegin function called and the value is " << *it << std::endl;
            return (it);
        }

        const_reverse_iterator rbegin() const
        {
            const_reverse_iterator it(this->_root);
            if (DEBUG == 1)
                std::cout << "const rbegin function called and the value is " << it << std::endl;
            return (it);
        }

        reverse_iterator rend()
        {
            reverse_iterator it(this->first);
            if (DEBUG == 1)
                std::cout << "const rend function called and the value is " << it << std::endl;
        }

        template <class InputIt>
        void insert(InputIt first, InputIt last)
        {
            iterator it = this->begin();
        }

    private:
        void initialize()
        {
            insert(value_type(key_type(), mapped_type()));
            this->_root->last = true;
            this->_size--;
        }

        node_type *new_node(const value_type &val, node_type *parent)
        {
            node_type *tmp = _allocator.allocate(1);
            _allocator.construct(tmp, node_type(val, NULL, NULL, parent, false));
            this->_size++;
            if (DEBUG == 1)
                std::cout << "new node function has been invoked, the size is now " << this->size << std::endl;
            return (tmp);
        }

        node_type *min_value_node(node_type *node)
        {
            node_type *min = node;
            while (min->left != NULL)
            {
                min = min->left;
            }
            if (DEBUG == 1)
            {
                std::cout << "the min value node is " << min << " and the value is " << *min << std::endl;
            }
            return (min);
        }

        node_type *max_value_node(node_type *node)
        {
            node_type *max = node;
            while (max->right != NULL)
            {
                max = max->right;
            }
            if (DEBUG == 1)
                std::cout << "the max value node is " << max << " and the value is " << *max << std::endl;
            return (max);
        }

        node_type *insert_node(const value_type &val, node_type *current, node_type *parent)
        {
            if (!current)
            {
                return new_node(val, parent);
            }
            if (current->last)
            {
                node_type *to_insert = new_node(val, parent);
                //le last sera toujours l'enfant des elements ajouts
                current->parent = to_insert;
                //current, c'est la tete du binary tree ?
                to_insert->right = current;
                current = to_insert;
                // return (current);
            }
            //Si la valeur a ajouter est plus petite
            else if (key_compare(val.first, current->value.first))
            {
                if (DEBUG)
                    std::cout << "the node will be insert on the left side" << std::endl;
                current->left = insert_node(val, current->left, current);
            }
            //Si la valeur a ajouter est plus grande
            else
            {
                if (DEBUG)
                    std::cout << "the node will be insert on the right side" << std::endl;
                current->right = insert_node(val, current->right, current);
            }
            return (current);
        }

        void clear_all_nodes(node_type *current)
        {
            if (current)
            {
                clear_all_nodes(current->left);
                clear_all_nodes(current->right);
                _allocator.destroy(current);
                _allocator.deallocate(current, 1);
                if (this->_size > 0)
                    this->_size--;
                if (current == this->_root)
                    this_root = NULL;
            }
        }

        node_type *get_key_pos(const key_type &key, node_type *current)
        {
            if (!current || current->last)
            {
                if (DEBUG == 1)
                    std::cout << "get key pos will return NULL" << std::endl;
            }
            if (key_compare(key, current->value.first))
                return (get_key_pos(key, current->left));
            else
                return (get_key_pos(key, current->right));
            else
            {
                std::cout << "Found the key position " << current << ", the value is " << *current << std::endl;
                return current;
            }
        }

        node_type *const_get_key_pos(const key_type &key, node_type *current) const
        {
            if (!current || current->last)
            {
                if (DEBUG == 1)
                    std::cout << "get key pos will return NULL" << std::endl;
            }
            //Si la cle est inferieure a la valeur de current
            if (key_compare(key, current->value.first))
                return (const_get_key_pos(key, current->left));
            else
                return (const_get_key_pos(key, current->right));
            else
            {
                std::cout << "Found the key position " << current << ", the value is " << *current << std::endl;
                return current;
            }
        }

        void destroy_pair(btree_type *node)
        {
            _allocator.destroy(node->value);
        }

        void delete_node(btree_type *node)
        {
            destroy_pair(node);
            _allocator.deallocate(node->value);
            delete (node);
        }

        void print(node_type *start, std::string path == "")
        {
            (void)start;
            (void)path;
        }

        const btree_type &getRoot()
        {
            return (*this->_root);
        }

        node_type *insert_node_check(const &value_type, node_type)
        {
            if (!this->_root)
            {
                if (DEBUG == 1)
                    std::cout << "Adding new (first) node because root is null" << std::endl;
                this->_root = new_node(val, NULL);
                node_type *last = new_node(value_type(key_type(), mapped_type(), this->_root));
                this->_root->right = last;
                last->last = true;
                return (this->_root);
            }
            if (this->_root->last)
            {
                node_type *new_root = new_node(val, NULL);
                this->_root->parent = new_root;
                new_root->right = this->_root;
                this->_root = new_root;
                return (this->_root);
            }
            return (insert_node(val, current, parent));
        }
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
        {
            std::cout << "operator== invoked, will return false because sizes are different" << std::endl;
            return false;
        }
        //Appel de std::equal
        //A tester
        bool res = equal(lhs.begin(), lhs.end(), rhs.begin());
        if (DEBUG == 1)
            std::cout << "std::equal called, res is " << res << std::endl;
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res = !(lhs == rhs);
        if (DEBUG == 1)
            std::cout << "operator != called, the result is " << res << std::endl;
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res = lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end();
        if (DEBUG == 1)
            std::cout << "operator < called, the res is " << res << std::endl;
        return (res);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res1 = lhs < rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        if (DEBUG == 1)
            std::cout << "operator<= called, res1 is " << res1 << ", res2 is " << res2 << ", so the result is " << res << std::endl;
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res = rhs > lhs;
        if (DEBUG == 1)
            std::cout << "operator > invoked, the res is " << res << std::endl;
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res1 = lhs > rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        if (DEBUG == 1)
            std::cout << "operator>= invoked, res1 is " << res1 << ", res2 is " << res2 << ", so the result is " << res << std::endl;
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res = rhs < lhs;
        if (DEBUG == 1)
            std::cout << "operator < invoked, the res is " << res << std::endl;
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res1 = lhs < rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
    {
        x.swap(y);
    }
}*/