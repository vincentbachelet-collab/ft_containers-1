#pragma once

#include <memory>
#include "node.hpp"
//#include "utils.hpp"
#include "iterator.hpp"

class map_iterator;

// Data collection that stores key value pairs, also often called dictionnary
// https://www.youtube.com/watch?v=aEgG4pidcKU
// https://www.youtube.com/watch?v=GiQnFdbdSbo
namespace ft
{
    template <class Key,
              class T,
              class Compare = std::less<Key>, //Less est ïmplementation-defined strict total order over pointers (comparateur plus strict que <)
              class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef node<value_type> node_type;

        // https://en.cppreference.com/w/cpp/utility/functional/binary_function
        class Binary_function
        {
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
        };
        // https://www.cplusplus.com/reference/map/map/value_comp/
        // in C++98, it is required to inherit binary_function<value_type,value_type,bool
        class value_compare : public Binary_function
        {
        public:
            Compare comp;
            value_compare(Compare c) : comp(c) {}
            bool operator()(const value_type &x, const value_type &y) const { return comp(x.first, y.first); }
        };

        typedef Allocator allocator_type;
        typedef typename allocator_type::template rebind<node_type>::other node_allocator;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef map_iterator<value_type, node_type *> iterator;
        typedef map_iterator<const value_type, node_type *> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    protected:
        node_allocator _allocator;
        key_compare _key_compare;
        size_type _size;
        node_type *_root;

    public:
        map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _allocator(alloc), _key_compare(comp), _size(0), _root(NULL) {}
        template <class InputIterator>
        map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _allocator(alloc), _key_compare(comp), _size(0), _root(NULL) { insert(first, last); }
        map(const map &x) : _allocator(x._allocator), _key_compare(x._key_compare), _size(0), _root(NULL) { *this = x; }
        virtual ~map() { clear_tree(this->_root); }
        map &operator=(const map &src)
        {
            //if (this != &src)
            clear_tree(this->_root);
            insert(src.begin(), src.end());
            return *this;
        }

        // https://www.cplusplus.com/reference/map/map/key_comp/
        key_compare key_comp() const
        {
            return (this->_key_compare);
        }

        // https://www.cplusplus.com/reference/map/map/value_comp/
        //Returns a comparison object that can be used to compare two elements to get wether the key of the first one goes before the second
        value_compare value_comp() const
        {
            return (value_compare(key_compare()));
            //return (value_compare(key_compare()));
        }

        size_type get_size(void)
        {
            return (this->_size);
        }

        void set_size(size_type n)
        {
            this->_size = n;
        }

        allocator_type get_allocator(void) const
        {
            return (this->_allocator);
        }

        void clear(void)
        {
            set_size(0);
        }

        //Returns the number of matches if found. - Devrait etre const
        size_type count(const key_type &k)
        {
            iterator temp = this->find(k);
            if (temp != this->end())
                return 1;
            return 0;
        }

        size_type count(const key_type &k) const
        {
            const_iterator temp = this->find(k);
            if (temp != this->end())
                return 1;
            return 0;
        }

        void swap(map &x)
        {
            if (x == *this)
                return;

            node_allocator temp_alloc_type = this->_allocator;
            key_compare temp_key_compare = this->_key_compare;
            size_type temp_size = this->_size;
            node_type *temp_root = this->_root;

            this->_allocator = x._allocator;
            this->_key_compare = x._key_compare;
            this->_size = x._size;
            this->_root = x._root;

            x._allocator = temp_alloc_type;
            x._key_compare = temp_key_compare;
            x._size = temp_size;
            x._root = temp_root;
        }

        pair<iterator, iterator> equal_range(const key_type &k)
        {
            return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }

        // Fonction de destroy + deallocate recursif / On va supprimer jusqu'au node passe en parametre
        void clear_tree(node_type *cur)
        {
            if (cur)
            {
                clear_tree(cur->left);
                clear_tree(cur->right);
                // Destroy + deallocate
                this->_allocator.destroy(cur);
                this->_allocator.deallocate(cur, 1);
                if (this->get_size() > 0)
                    this->set_size(this->get_size() - 1);
                if (cur == this->_root)
                    this->_root = NULL;
            }
        }

        // Va permettre d'ajouter une feuille a l'arbre en mentionnant son parent (sans savoir ou on va le placer)
        node_type *add_node(value_type const &val, node_type *parent)
        {
            // On alloue et on construit le nouveau node
            node_type *temp = _allocator.allocate(1);
            this->_allocator.construct(temp, node_type(val, NULL, NULL, parent, false));
            this->_size++;
            return (temp);
        }

        // Pour tester key compare on a besoin des iterateurs
        iterator begin()
        {
            if (this->_size == 0)
                return (this->_root);
            node_type *temp = this->_root;
            while (temp && temp->left)
                temp = temp->left;
            return (temp);
        }

        const_iterator begin() const
        {
            if (this->_size == 0)
                return (const_iterator(this->_root));
            node_type *temp = _root;
            while (temp && temp->left)
                temp = temp->left;
            return (const_iterator(temp));
        }

        void initialize()
        {
            insert(value_type(key_type(), mapped_type()));
            this->_root->last = true;
            this->_size--;
        }

        iterator end()
        {
            //Necessaire sinon ne passe pas tous les tests !
            if (!this->_root)
                initialize();
            if (this->_size == 0)
                return (this->_root);
            node_type *temp = this->_root;
            while (temp && !temp->last)
                temp = temp->right;
            return (temp);
        }

        const_iterator end() const
        {
            if (this->_size == 0)
                return (const_iterator(_root));
            node_type *temp = this->_root;
            while (temp && !temp->last)
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

        iterator find(const key_type &k)
        {
            node_type *temp = recursive_find_key(k, this->_root);
            if (temp)
                return (iterator(temp));
            return (this->end());
        }
        const_iterator find(const key_type &k) const
        {
            //node_type *temp = const_position_of_a_key(k, this->_root);
            node_type *temp = recursive_find_key(k, this->_root);
            if (temp)
                return const_iterator(temp);
            return (const_iterator(this->end()));
        }

        //Erase
        void erase(iterator position)
        {
            erase(position->first);
        }

        size_type erase(key_type const &k)
        {
            size_type backup = this->_size;
            this->_root = delete_node(this->_root, k);
            return (backup - this->_size);
        }

        void erase(iterator first, iterator last)
        {
            map<key_type, mapped_type> temp(first, last);
            iterator it = temp.begin();
            iterator ite = temp.end();
            for (; it != ite; it++)
                this->_root = delete_node(this->_root, it->first);
        }

        node_type *insert_node(const value_type &val, node_type *current, node_type *parent)
        {
            if (!current)
                return add_node(val, parent);
            if (current->last)
            {
                node_type *to_insert = add_node(val, parent);
                current->parent = to_insert;
                to_insert->right = current;
                current = to_insert;
                return current;
            }
            if (_key_compare(val.first, current->value.first))
                current->left = insert_node(val, current->left, current);
            else if (_key_compare(current->value.first, val.first))
                current->right = insert_node(val, current->right, current);
            return current;
        }

        iterator lower_bound(const key_type &k)
        {
            iterator ite = this->end();
            iterator it = this->begin();
            while (it != ite)
            {
                if (!_key_compare(it->first, k))
                    return (it);
                it++;
            }
            return (ite);
        }

        const_iterator lower_bound(const key_type &k) const
        {
            const_iterator ite = this->end();
            const_iterator it = this->begin();

            while (it != ite)
            {
                if (!_key_compare(it->first, k))
                    return (it);
                it++;
            }
            return (ite);
        }

        iterator upper_bound(const key_type &k)
        {
            iterator it = this->begin();
            iterator ite = this->end();
            while (it != ite)
            {
                if (_key_compare(k, it->first))
                    return (it);
                it++;
            }
            return (ite);
        }

        const_iterator upper_bound(const key_type &k) const
        {
            const_iterator it = this->begin();
            const_iterator ite = this->end();
            while (it != ite)
            {
                if (_key_compare(k, it->first))
                    return (it);
                it++;
            }
            return (ite);
        }

        //Utils
        node_type *min_value_node(node_type *node)
        {
            node_type *current = node;
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        node_type *max_value_node(node_type *node)
        {
            node_type *current = node;
            while (current->right != NULL)
                current = current->right;
            return current;
        }

        //Le current est toujours _root, on va chercher le bon node grace a la key
        node_type *delete_node(node_type *current, const key_type &key)
        {
            if (!current || current->last)
                return current;
            if (this->_key_compare(key, current->value.first)) //si la cle correspond a l enfant plus petit
                current->left = delete_node(current->left, key);
            else if (this->_key_compare(current->value.first, key)) //si la cle correspond a l enfant plus grand
                current->right = delete_node(current->right, key);
            else
            {
                //Si le node n a pas deux enfants
                if (!current->left || !current->right)
                {
                    node_type *temp = current->left ? current->left : current->right;
                    if (!current->left && !current->right)
                    {
                        temp = current;
                        this->_allocator.destroy(temp);
                        this->_allocator.deallocate(temp, 1);
                        current = NULL;
                        this->_size--;
                    }
                    else
                    {
                        temp->parent = current->parent;
                        node_type *temp2 = current;
                        current = temp;
                        this->_allocator.destroy(temp2);
                        this->_allocator.deallocate(temp2, 1);
                        this->_size--;
                    }
                }
                //Necessaires pour le erase2 et tricky erase
                else
                {
                    node_type *temp = min_value_node(current->right);
                    if (temp != current->right)
                    {
                        temp->right = current->right;
                        current->right->parent = temp;
                    }
                    temp->left = current->left;
                    current->left->parent = temp;
                    temp->parent->left = NULL;
                    temp->parent = current->parent;
                    if (this->_root == current)
                        this->_root = temp;
                    this->_allocator.destroy(current);
                    this->_allocator.deallocate(current, 1);
                    this->_size--;
                    current = temp;
                }
            }
            return current;
        }

        node_type *insert_node_from_root(const value_type &val, node_type *current, node_type *parent = NULL)
        {
            if (!this->_root) // Si l'arbre est vide (root pas alloue et construit)
            {
                this->_root = add_node(val, NULL);
                node_type *last = add_node(value_type(key_type(), mapped_type()), this->_root);
                this->_size--;
                this->_root->right = last;
                last->last = true;
                return (this->_root);
            }
            if (this->_root->last) //Si root est le seul element
            {
                node_type *new_root = add_node(val, NULL);
                this->_root->parent = new_root;
                new_root->right = this->_root;
                this->_root = new_root;
                return (this->_root);
            }
            //Si ne correspond pas aux deux cas precedents
            return insert_node(val, current, parent);
        }

        // Fonction recusive qui va chercher une key
        node_type *recursive_find_key(const key_type &key, node_type *current) const
        {
            if (!current || current->last)
                return NULL;
            if (this->_key_compare(key, current->value.first))
                return recursive_find_key(key, current->left);
            else if (this->_key_compare(current->value.first, key))
                return recursive_find_key(key, current->right);
            else
                return current;
        }

        //If k matches the key of an element in the container, the function returns a reference to its mapped value.
        //If k does not match the key of any element in the container, the function inserts a new element with that key and returns a reference to its mapped value
        mapped_type &operator[](const key_type &k)
        {
            node_type *temp = recursive_find_key(k, this->_root);
            if (temp)
                return temp->value.second;
            insert(value_type(k, mapped_type()));
            return (recursive_find_key(k, this->_root)->value.second);
        }

        // Insert, trois versions
        //https://www.cplusplus.com/reference/map/map/insert/
        //Insert single element
        pair<iterator, bool> insert(const value_type &val)
        {
            size_t backup = this->get_size();
            insert_node_from_root(val, this->_root);
            return (pair<iterator, bool>(recursive_find_key(val.first, this->_root), backup != this->_size));
        }

        //insert with hint
        iterator insert(iterator position, const value_type &val)
        {
            (void)position;
            insert_node_from_root(val, this->_root);
            return iterator(recursive_find_key(val.first, this->_root));
        }

        //insert range
        template <class InputIterator>
        void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
        {
            while (first != last)
            {
                insert(*first);
                first++;
            }
        }

        bool empty() const
        {
            return (this->_size == 0);
        }
        size_type size() const
        {
            return (this->_size);
        }
        size_type max_size() const
        {
            return (this->_allocator.max_size());
        }
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        return equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (lhs < rhs || lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return rhs < lhs;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (lhs > rhs || lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
    {
        x.swap(y);
    }
}