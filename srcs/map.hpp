#pragma once 

/*
** The true map container is defined in header <map>
** https://en.cppreference.com/w/cpp/container/map
** 
*/

#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "./binary_three.hpp"
#include "./vector.hpp"
#include "./node.hpp"

#include <functional>

#define DEBUG 0
#define ENVIRONNEMENT 64
//#include <iostream>

/*
** Faire une classe node ?
*/

/*
** std::less is defined in <functional>
** "function object for performing comparisons"
** Unless specialized, invokes operator < on type T. 
** TO DO: est-ce qu'il faut faire un ft less ?
*/
namespace ft
{
    /*
    ** Compare argument default to std::less 
    ** which invokes operator < on type T
    */
    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        /*
        ** https://en.cppreference.com/w/cpp/utility/functional/binary_function
        ** https://www.cplusplus.com/reference/functional/binary_function/
        ** define in header <functional>
        ** binary_function is a base class for creating function objects with two arguments.
        */
        /*
        ** binary_function does not define operator(); it is expected that derived classes will define this. 
        ** binary_function provides only three types - first_argument_type, second_argument_type and result_type
        ** defined by the template parameters.
        */

        /*
        ** pour expliquer les "binary function" l'exemple de compare est souvent repris.
        ** L'idee de d'overloader l operateur() pour creer une fonction qui prendra uniquement 2 parametres
        ** l'overload() n'est jamais defini dans la classe binary function, 
        ** libre au developpeur de l implementer comme il le souhaite.
        ** TODO: a tester + retrouver le code source
        */
        struct value_compare : public std::binary_function<value_type, value_type, bool>
        {
        protected:
            Compare _comp;
        public:
            value_compare(Compare comp): _comp(comp)
            {
                if (DEBUG)
                    std::cout << "value compare default constructor invoked" << std::endl;
            }
            value_compare(Compare comp): _comp(comp)
            {
                if (DEBUG)
                    std::cout << "value compare parameter constructor invoked" << std::endl;
            }
            /*
            ** Je ne comprend pas cette implementation
            */
            bool operator()(const value_type &first, const value_type &second) const
            {
                std::cout << "compare operator() invoked" << std::endl;
                return (this->_comp(first.first, second.first));
            }
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;
        };

        typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef ft::map_iterator<value_type>			iterator;
		typedef ft::map_iterator<const value_type>		const_iterator;
		typedef ft::reverse_iterator< iterator >		reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
		typedef ft::btree<value_type>					btree_type;
		typedef ft::btree<const value_type>				const_btree_type;               const_reverse_iterator;
    
    protected:
        btree_type		_root;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_allocator;
    
    public:
        /*
        ** https://en.cppreference.com/w/cpp/container/map/map 
        */
        /*
        ** Constructeur 1 - empty
        ** J'ai retire le mot cle explicit puisqu il ne fait pas partie du standard 98.
        */
        map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _allocator(alloc), _comp(comp), _size(0), _root(btree_type())
        {
            if (DEBUG)
                std::cout << "map default constructor called" << std::endl;
        }
        /*
        ** Constructeur 2 - range
        ** Constructs the container with the contents of the range [first, last]
        */
       template <class InputIt>
       map (InputIt first, InputIt last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _root(btree_type()), _size(0), _comp(comp), _allocator(alloc)
        {
            if (DEBUG)
                std::cout << "map range constructor called" << std::endl;
			insert(first, last);
		}

        //voir si dernier constructeur ?
        /*
        ** Constructeur par copie 
        */
        map(const map &src): _root(btree_type()), _size(0), _comp(src._comp), _allocator(src._allocator)
        {
            if (DEBUG)
                std::cout << "map copy constructor called" << std::endl;
            insert(src.begin(), src.end());
        }
        /*
        ** Destructeur
        */
        virtual ~map(void)
        {
            if (DEBUG)
                std::cout << "map destructor called" << std::endl;
            clear();
        }

        map &operator=(const map &src)
        {
            if (DEBUG)
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

        /*
        ** Capacity
        */
        bool empty() const
        {
            if (this->_size)
            {
                if (DEBUG)
                    std::cout << "the map is not empty" << std::endl;
                return (false);
            }
            if (DEBUG)
                std::cout << "the map is empty" << std::endl;
            return (true);
        }

        /*
        ** Size
        */
        size_type size() const
        {
            size_type s = this->_size;
            if (DEBUG)
                std::cout << "the size is " << s << std::endl;
            return (s);
        }
        /*
        ** max_size()
        ** https://en.cppreference.com/w/cpp/container/map/max_size
        ** Returns the maximum number of elements the container is able to hold 
        ** due to system or library implementation limitations, i.e. std::distance(begin(), end()) for the largest container.
        */
        size_type max_size() const
        {
            //voir dans quelle librairie se trouve pow
            return (pow(2, ENVIRONNEMENT) - 1.0) / (sizeof(value_type) + sizeof(ft::node<value_type>))));
        }

        /*
        ** Permet d'acceler a la valeur pointee par la cle.
        */
        mapped_type &operator[](const key_type &key)
        {
            mapped_type &mapped = insert(value_type(key).first->second);
            if (DEBUG)
            {
                std::cout << "operator[] invoked and the mapped_type is " << mapped << std::endl;
            }
        }

        /*
        ** Modifiers
        */
        
        /*
        ** https://www.cplusplus.com/reference/map/map/insert/
        ** Extends the container by inserting new elements, 
        ** effectively increasing the container size by the number of elements inserted.
        ** Because element keys in a map are unique, the insertion operation checks whether each inserted element has a 
        ** key equivalent to the one of an element already in the container, and if so, the element is not inserted, 
        ** returning an iterator to this existing element (if the function returns a value).
        */

       /*
       ** insert single element
       */
        pair<iterator, bool> insert(const value_type &val)
        {
            btree_type *cursor = _root.left;
            //last c'est bien le dernier element ajoute
            btree_type *last = &_root;

            //On va chercher a se positioner la ou va etre insere le node
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
                //la cle n existe pas deja
                btree_type  *node;
                node = create_node(val.first, last, val.second);
                if (last == &_root)
                {
                    //?si il n'y a pas d'element ?
                    last->left = node;
                    last->right = node;
                }
                else if (key_compare()(val.first, last->value->first))
                {
                    //si la valeur est plus petite que last
                    last->left = node;
                }
                else
                {
                    //si la valeur est plus grande que last
                    last->right = node;
                }
                cursor = node;
                this->_size++;
                //essayer avec make pair
                return (ft::pair<iterator, bool>(cursos, false)
            }
            //la cle existe deja mais avec la bonne valeur de is_found ca ne sera pas genant ?
            //voir comment retourner une paire vide ?
            return (ft::pair<iterator, bool>(cursos, true);
        }

        /*
        ** insert hint (2)
        ** faire des sous fonctions, faire des schemas
        **TODO: voir diff entre key_comp et key compare
        */
        iterator insert(iterator position, const value_type &val)
        {
            iterator last = &_root;
            iterator tmp;

            //si position est root ? et que la taille n est pas nulle?
            if (position == end() && this->_size())
            {
                position = iterator(position.getNode()->left);
            }
            //pas tres sure de cette partie
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
                //a revoir
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

        /*
        ** insert range (3)
        */
        template <class InputIt>
        void insert(InputIt first, InputIt last)
        {
            iterator last_insert = this->begin();
            InputIt it = first;
            while (it < last)
            {
                last_insert = this->insert(last_insert, *it);
                //faire messages de debug
                it++;
            }
        }

        /* a reprendre */
        void    erase(iterator position)
        {
            btree_type *to_erase = position.getNode();
			btree_type *parent = to_erase->parent;
			btree_type *pivot = 0;

			if (to_erase->left) {
				pivot = to_erase->left;
				if (to_erase->right){
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
			if (parent == &_root){
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

        size_type erase (const key_type &key)
        {
			iterator it = this->find(key);
			if (it == end())
				return (false);
			this->erase(it);
			return (true);
		}

        void erase (iterator first, iterator last)
        {
			iterator next = first;
			for (iterator it = first; it != last; it = next)
			{
				next++;
				this->erase(it);
			}
		}

        void swap (map &other)
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

        /*
        ** key compare
        */
        key_compare key_comp() const
        {
			return (this->_comp);
		}

        /*
        ** value compare
        */
        value_compare value_comp() const
        {
			return (value_compare(this->_comp));
		}

        /*
        ** find
        */
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
            return(end());
        }

        /*
        ** find const 
        */
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
            return(end());
        }

        /*
        ** count
        ** https://www.cplusplus.com/reference/map/map/count/
        */
        size_type count(const key_type &key) const
        {
            if (this->find(key) != end())
                return (1);
            return (0);
        }

        //TODO: ajouter le debug, tester

        /*
        ** lower bound 
        ** https://www.cplusplus.com/reference/map/map/lower_bound/
        */
        iterator lower_bound(const key_type &key)
        {
            iterator it = this->begin();
            while (it != this->end() && this->key_comp()(it->first, k))
                it++;
            return (it);
        }

        /*
        ** const lower bound
        */
        const_iterator lower_bound (const key_type& k) const
        {
			const_iterator it = this->begin();

			while (it != this->end() && this->key_comp()(it->first, k))
				it++;
			return (it);
		}

        /*
        ** Upperbound
        */
        iterator upper_bound (const key_type &key)
        {
			iterator it = this->begin();

			while (it != this->end() && !this->key_comp()(key, it->first))
				it++;
			return (it);
		}

        /*
        ** Equal range
        */
       pair<iterator,iterator>	equal_range (const key_type& k)
       {
			iterator it = this->begin();

			while (it != this->end() && (this->key_comp()(it->first, k)))
				it++;
			if (it == this->end() || this->key_comp()(k, it->first))
				return (pair<iterator, iterator>(it, it));
			iterator upper = it;
			return (pair<iterator, iterator>(it, ++upper));
		}

        /*
        ** const equal range
        */
        pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			const_iterator it = this->begin();

			while (it != this->end() && (this->key_comp()(it->first, k)))
				it++;
			if (it == this->end() || this->key_comp()(k, it->first))
				return (pair<const_iterator, const_iterator>(it, it));
			const_iterator upper = it;
			return (pair<const_iterator, const_iterator>(it, ++upper));
		}
        /*
        ** Iterateur
        */

        /*
        ** Begin
        ** besoin de empty, end pour faire begin pour faire insert pour faire le constructeur fill
        */
        iterator begin()
        {
            if (empty())
            {
                if (DEBUG)
                    std::cout << "begin is invoked but the map is empty" << std::endl;
                return(end());
            }
            iterator it(this->_first);
            if (DEBUG)
                std::cout << "begin is invoked, the value is " << *it << std::endl;
            return (it);
        }

        /*
        ** Const begin()
        ** TODO: checker le code source
        */
        const_iterator begin() const 
        {
            if (empty())
            {
                if (DEBUG)
                    std::cout << "const begin is invoked but the map is empty" << std::endl;
                return(end());
            }
            const_iterator it(reinterpret_cast<const_btree_type *>(_first()));
            if (DEBUG)
                std::cout << "const begin is invoked, the value is " << *it << std::endl;
            return (it);
        }

        /*
        ** End
        */
        iterator end()
        {
            iterator it = iterator(this->_root);
            if (DEBUG)
            {
                std::cout << "end function called, and the value is " << *it << std::endl;
            }
        }

        /*
        ** const_end
        */
        const_iterator end() const
        {
            if (this->empty())
            {
                if (DEBUG)
                    std::cout << "end function called, the map is empty so an iterator will be constructed" << std::endl;
                return(const_iterator());
            }
            const_iterator it(reinterpret_cast<const_btree_type *>(_root._left->parent)));
            return (it);
        }

        reverse_iterator rbegin()
        {
            reverse_iterator it(this->_root);
            if (DEBUG)
                std::cout << "rbegin function called and the value is " << *it << std::endl;
            return (it);
        }
        
        /*
        ** refaire des tests sur const et pas const
        */
        const_reverse_iterator rbegin() const
        {
            const_reverse_iterator it(this->_root);
            if (DEBUG)
                std::cout << "const rbegin function called and the value is " << it << std::endl;
            return (it);
        }

        reverse_iterator rend()
        {
            reverse_iterator it(this->first);
            if (DEBUG)
                std::cout << "const rend function called and the value is " << it << std::endl;
        }

        /*
        ** Besoin d'avoir begin pour pouvoir faire insert
        ** a reprendre
        */
        /*
        template<class InputIt>
        void insert(InputIt first, InputIt last)
        {
            iterator it = this->begin();
        }
        */
        //fonction de print?
    private:
        void initialize()
        {
            //Ajout d'un nouvel element 
            insert(value_type(key_type(), mapped_type()));
            //On indique qu'il s'agit d'une leaf ?
            this->_root->last = true;
            this->_size--;
        }

        node_type*  new_node(const value_type &val, node_type *parent)
        {
            node_type   *tmp = _allocator.allocate(1);
            //TODO: faire un schema du processus
            _allocator.construct(tmp, node_type(val, NULL, NULL, parent, false));
            this->_size++;
            if (DEBUG)
            {
                std::cout << "new node function has been invoked, the size is now " << this->size << std::endl;
            }
            //tmp->parent = parent ?
            return (tmp);
        }

        /*
        ** Va permettre de retourner l'adresse du node ayant la plus petite valeur
        */
        node_type   *min_value_node(node_type *node)
        {
            node_type *min = node;
            //Les plus petits sont toujours a gauche
            while (min->left != NULL)
            {
                min = min->left;
            }
            if (DEBUG)
            {
                std::cout << "the min value node is " << min << " and the value is " << *min << std::endl;
            }
            return (min);
        }

        /*
        ** Va permettre de retourner l'adresse du node ayant la plus grande valeur
        */
        node_type   *max_value_node(node_type *node)
        {
            node_type *max = node;
            while (max->right != NULL)
            {
                max = max->right;
            }
            if (DEBUG)
            {
                std::cout << "the max value node is " << max << " and the value is " << *max << std::endl;
            }
            return (max);
        }
        
        /*
        ** Insert node
        ** Pourquoi on ne prend pas root ?
        ** TODO: faire un schema
        */
        /*
        node_type   *insert_node(const value_type &val, node_type *current, node_type *parent)
        {
            if (!current)
            {
                return new_node(val, parent);
            }
            //a tester
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
        */

        /*
        ** Va permettre de detruire et desallouer tous les nodes du tree
        ** fonction recursive
        */
       /*
        void    clear_all_nodes(node_type *current)
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
        */
        
        /*
        ** Permet de recuperer l'adresse d'une cle recherchee
        ** Recursif
        */
        node_type   *get_key_pos(const key_type &key, node_type *current)
        {
            //|| ou && ?
            if (!current || current->last)
            {
                if (DEBUG)
                    std::cout << "get key pos will return NULL" << std::endl;
            }
            //Si la cle est inferieure a la valeur de current
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

        /*
        ** Voir quand on en aurait besoin particulirement ?
        */
         node_type   *const_get_key_pos(const key_type &key, node_type *current) const 
        {
            //|| ou && ?
            if (!current || current->last)
            {
                if (DEBUG)
                {
                    std::cout << "get key pos will return NULL" << std::endl;
                }
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

        void    destroy_pair(btree_type *node)
        {
            _allocator.destroy(node->value);
        }

        void    delete_node(btree_type *node)
        {
            destroy_pair(node);
            _allocator.deallocate(node->value);
            delete(node);
        }

        void print(node_type *start, std::string path=="")
        {
            (void)start;
            (void)path;
            //A reprendre
        }

        const btree_type &getRoot()
        {
            return (*this->_root);
        }

        /*
        ** Voir pourquoi on a besoin de plusieurs types d'insert
        ** Pourquoi on ne checkerait pas root tout le temps ?
        */
        /*
        node_type   *insert_node_check(const &value_type, node_type)
        {
            if (!this->_root)
            {
                if (DEBUG)
                {
                    std::cout << "Adding new (first) node because root is null" << std::endl;
                }
                this->_root = new_node(val, NULL);
                node_type *last = new_node(value_type(key_type(), mapped_type(), this->_root));
                //this->size--; //?
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
            // gestion de tous les autres cas
            return (insert_node(val, current, parent));
        }
        */

    };
    /*
    ** Non member function overloads
    */
   template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
		if (lhs.size() != rhs.size())
        {
            std::cout << "operator== invoked, will return false because sizes are different" << std::endl;
            return false;
        }
        //Appel de std::equal
        //A tester
        bool res = equal(lhs.begin(), lhs.end(), rhs.begin());
        if (DEBUG)
        {
            std::cout << "std::equal called, res is " << res << std::endl;
        }
		return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
    {
        bool res = !(lhs == rhs);
        if (DEBUG)
        {
            std::cout << "operator != called, the result is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res = lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end();
        if (DEBUG)
        {
            std::cout << "operator < called, the res is " << res << std::endl;
        }
        return (res);
	}
    template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
    {
        bool res1 = lhs < rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        if (DEBUG)
        {
            std::cout << "operator<= called, res1 is " << res1 << ", res2 is " << res2 << ", so the result is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
    {
        bool res = rhs > lhs;
        if (DEBUG)
        {
            std::cout << "operator > invoked, the res is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res1 = lhs > rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        if (DEBUG)
        {
            std::cout << "operator>= invoked, res1 is " << res1 << ", res2 is " << res2 << ", so the result is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
    {
        bool res = rhs < lhs;
        if (DEBUG)
        {
            std::cout << "operator < invoked, the res is " << res << std::endl;
        }
        return (res);
    }

    template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        bool res1 = lhs < rhs;
        bool res2 = lhs == rhs;
        bool res = res1 || res2;
        if (DEBUG)
        {
            std::cout << "operator<= invoked, res1 is " << res1 << ", res2 is " << res2 << ", so the result is " << res << std::endl;
        }
        return (res);
    }

    /*
    ** Non member function swap
    */
    template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
    {
        if (DEBUG)
        {
            std::cout << "swap non member function invoked" << std::endl;
        }
        x.swap(y);
    }
}