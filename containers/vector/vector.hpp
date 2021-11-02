#ifndef VECTOR_HPP
# define VECTOR_HPP

/* Librairies a inclure - tester sur mac / linux */
# include <memory> //pour les allocators
# include <algorithm>
# include <iostream>
/*
# include <cstddef>
# include <tgmath.h>
*/

#ifndef DEBUG
# define DEBUG 1
#endif
/*
** Pour eviter les conflits entre la version std et la notre version
*/
namespace ft
{
	//Declaration de notre template de classe qui pourra contenir n'importe quel type
	template < class T, class Alloc = std::allocator<T> >
	//Voir pourquoi ici on ne respecte pas la convention de la majuscule
	class vector
	{
	//En reprenant le code source de vector, on va reprendre les typedef
	//On ajoute un petit commentaire pour bien comprendre de quoi il s'agit
	public:
		//Est-ce que ca doit fonctionne ?
		//vector(void); n existe pas
		vector(vector const &src);
		vector & operator=(vector const &src)
		virtual ~vector;


		/* TYPEDEFS - voir comment on peut faire des commentaires bien propres (meme taille etc) */

		/*
		** Le type qui a ete passe en parametre, celui avec lequel on va travailler en permanence
		*/
		typedef T                                           						value_type;

		/*
		** Notre eventuel deuxieme argument.
		** Les allocators gere l'allocation et la desallocation des containers
		** dynamic memory allocation
		*/
		typedef Allocator                                								allocator_type;

		/**
		 * ! Creuser dans quel cas on l'utilise
		** Allocator traits
		** provides an interface that allows to use as allocator just any class
		** that provides at least a public member type value_type and public member functions allocate and deallocate
		*/

		typedef typename allocator_type::reference       								reference;
		typedef typename allocator_type::const_reference    						const_reference;
		typedef typename allocator_type::pointer            						pointer;
		typedef typename allocator_type::const_pointer      						const_pointer;
		typedef	ft::normal_iterator<const_pointer, vector>							const_iterator;
		typedef ft::random_access_iterator<value_type>									iterator;
		//is an iterator adaptor that reverses the direction of a given iterator
		typedef	ft::reverse_iterator<iterator>													reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>										const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef	size_t																									size_type;

	private:
		alloctor_type		m_alloc;
		size_t					m_capacity;
		//pointer 			m_start;
		//size_type			m_size;
	}
}

#endif
