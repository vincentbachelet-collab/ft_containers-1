# ft_containers 

- Status : validated 
- Grade : 100%

## Suggestions for you
- I implemented few getters and setters (like many people did) but realised the subject mentionned that we should not add more  functions, so please don't. **Use friend for non member overloads (only)**.
- Make your **destructor virtual**. A lot of people did not do it but remember it could create leaks when working with polymorphism (devired class inheriting from base class). If you want to respect a strictly canonical class you **should not forget virtual**.
- I implemented a simple **binary tree**. You could work with a **Red/Black** tree as well.  Student explanations are sometimes unclear, make sure they understood the different rules that their tree is supposed to respect.
- You **can't use  new**, even for your nodes (=elements of the tree). You should use the **allocate** and **construct** function. 
- Some students are reimplemented some classes for no apparent reason like **std::less**. Make sure that have a **solid reason for that**. (They probably just did it because somebody else did).
- Unlike me, don't forget the **main from the subject**.  Use **valgrind to check if there is no memory leaks**. You can also add some while loop to check a crazy amount of inserting to check the **speed/performances**.
- **Reclone the testers** when correcting other students. They could have commented some tester functions to pass it. For instance, **the output of maxsize could be different from std but it's ok.**
Please find below my notes (sorry it is in french). 

# Notes 

  

C++ STL est une librairie de C++ (standard template library). ****Generic programming****

  

→ Quickly, efficiently and in a generic way.

  

→ we can use “out of the box” containers.

  

→ prerequis idealement (connaissance de C++ et utilisation des templates).

  

Un container STL (standard template library) est une “collection” d’objets de même types. Implemente en templates, ils permettent une grande flexibilite dans les types supportes par les elements.  C’est le container qui gere le storage et qui met a disposition des fonctions pour acceder a ses elements (directement ou via des iterateurs).

  

Le container “owns” les elements, ce qui implique qu’il soit en charge de la creation (allocation + construction) et la destruction.

  

[Intra Projects ft_containers Edit.pdf](ft_containers%20782b5ef52b27409e8feac96a40ef854a/Intra_Projects_ft_containers_Edit.pdf)

  

****Tutoriels principaux :****

  

- [https://internalpointers.com/post/writing-custom-iterators-modern-cpp](https://internalpointers.com/post/writing-custom-iterators-modern-cpp)

- [https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/)

- [https://fr.wikipedia.org/wiki/Arbre_bicolore](https://fr.wikipedia.org/wiki/Arbre_bicolore)

- [https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/](https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/)

- [https://internalpointers.com/post/writing-custom-iterators-modern-cpp](https://internalpointers.com/post/writing-custom-iterators-modern-cpp)

  

****Autres tutoriels :****

  

- types traits : [https://www.youtube.com/watch?v=tiAVWcjIF6o](https://www.youtube.com/watch?v=tiAVWcjIF6o)

- iterators : [https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html](https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html)

- iterators : [https://thinkable-saga-6a8.notion.site/ft_containers-4efe98af3bee4a52834d1ac72a838ceb](https://www.notion.so/ft_containers-4efe98af3bee4a52834d1ac72a838ceb)

- enable_if : [https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html](https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html)

- [https://thinkable-saga-6a8.notion.site/ft_containers-4efe98af3bee4a52834d1ac72a838ceb](https://www.notion.so/ft_containers-4efe98af3bee4a52834d1ac72a838ceb)

- allocator : [https://www.youtube.com/watch?v=sLlGEUO_EGE](https://www.youtube.com/watch?v=sLlGEUO_EGE)

- allocator : [https://en.cppreference.com/w/cpp/memory/allocator](https://en.cppreference.com/w/cpp/memory/allocator)

- allocator : [https://fr.acervolima.com/std-allocator-en-c-avec-des-exemples/](https://fr.acervolima.com/std-allocator-en-c-avec-des-exemples/)

- vector : [https://www.youtube.com/watch?v=HcESuwmlHEY&t=73s](https://www.youtube.com/watch?v=HcESuwmlHEY&t=73s)

- vector : [https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/](https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/)

- custom allocators : [https://www.youtube.com/watch?v=pP15kDeXJU0](https://www.youtube.com/watch?v=pP15kDeXJU0)

- custom allocators : [https://www.youtube.com/watch?v=v-qePUHf8iU](https://www.youtube.com/watch?v=v-qePUHf8iU)

  

# La notion d’allocator

  

### std::allocator

  

[https://www.youtube.com/watch?v=kSWfushlvB8](https://www.youtube.com/watch?v=kSWfushlvB8)

  

→ L’OS principal utilise lorsque la STL a été cree avait des “problèmes” au niveau de pointeurs qui ne faisaient pas la meme taille, l’allocateur devait donc être une réponse a ces problèmes pour que les containers soient plus flexibles.

  

→ L’allocator permet de faire les étapes de construction/allocation et destruction/desallocation en deux temps.

  

→ L’allocateur permet d’abstraire la gestion de la memoire (le container ne gère rien, “don’t need to know about these”) pour que l’interface du container soit plus simple.

  

→ L’écriture de son propre allocateur doit respecter des règles, et permettraient de gérer les performances et l allocation heap/stack “a sa guise”.

  

Les allocateurs sont des objets charges "d'encapsuler la gestion de la mémoire".

  

> Ils permettent de séparer l'allocation et de la construction. Pareil pour la déconstruction et la désallocation. L'allocateur va par exemple permettre de contrôler quel constructeur sera appelé, ce qui ne sera pas le cas de new.

>

  

On peut définir des allocators customs pour par exemple n'allouer qu'occasionnellement.

  

→ permet d'optimiser le programme (?)

  

→ les containers de la STL ont tous été implante avec des allocators, il faut donc faire de même et ne pas utiliser new.

  

→ new sera de toute façon appelée par la fonction allocate();

  

# Vector

  

→ Recommandé de commencer par ce container.

  

→ ****Dynamic (size) arrays.****

  

Fonctions membres de vecteur pour gérer ****la capacité et l'allocation.****

  

```cpp

reserve()

resize()

```

  

****Attention**** : durant mes recherches j'ai trouve beaucoup d'infos sur les rvalues et les lvalues ainsi que les moves statement, ces notions sont particulièrement interessantes et permettent d optimiser le code mais malheureusement elles ne font pas partie du standard 98.

  

****Constructeurs****

  

[https://en.cppreference.com/w/cpp/container/vector/vector](https://en.cppreference.com/w/cpp/container/vector/vector)

  

il existe de nombreux constructeurs mais nous devons en implementer uniquement 4 : default, fill, range et copy.

  

Dans le ****range constructor on utilise un enable if et des is_integral pour verifier que ce qui est passé en paramètre du constructeur sont des itérateurs et pas des “integrals”.****

  

### Allocator

  

```cpp

#include <memory>

#include <iostream>

#include <string>

int main()

{

{

// default allocator for ints

std::allocator<int> alloc;

// demonstrating the few directly usable members

static_assert(std::is_same_v<int, decltype(alloc)::value_type>);

int* p = alloc.allocate(1);  // space for one int

alloc.deallocate(p, 1);  // and it is gone

// Even those can be used through traits though, so no need

using traits_t = std::allocator_traits<decltype(alloc)>; // The matching trait

p = traits_t::allocate(alloc, 1);

traits_t::construct(alloc, p, 7); // construct the int

std::cout << *p << '\n';

traits_t::deallocate(alloc, p, 1);  // deallocate space for one int

}

{

// default allocator for strings

std::allocator<std::string> alloc;

// matching traits

using traits_t = std::allocator_traits<decltype(alloc)>;

// Rebinding the allocator using the trait for strings gets the same type

traits_t::rebind_alloc<std::string> alloc_ = alloc;

std::string* p = traits_t::allocate(alloc, 2); // space for 2 strings

traits_t::construct(alloc, p, "foo");

traits_t::construct(alloc, p + 1, "bar");

std::cout << p[0] << ' ' << p[1] << '\n';

traits_t::destroy(alloc, p + 1);

traits_t::destroy(alloc, p);

traits_t::deallocate(alloc, p, 2);

}

}

```

  

Revision des fonctions :

  

```cpp

void assign(size_type count, const T& value);

```

  

****assign**** : va permettre d’ajouter count copies de valeurs value. Si il y a deja du contenu il va etre écrasé. Nous devions implementer deux versions : ****1. fill, 2. range. Les autres versions ne dates pas de c++98.****

  

```cpp

allocator_type get_allocator() const;

```

  

****get_allocator**** : getter de notre attribut membre allocator, par defaut on utilise toujours le std::allocator (objet chargé d’encapsuler la mémoire).

  

```cpp

reference at( size_type pos );

```

  

****at (et at const):****  retourne une reference vers l’element recherche a la position pos.

  

```cpp

reference operator[]( size_type pos );

```

  

****operator[]**** → surcharge de l’operateur [] qui nous permet d’acceder a l’element un peu comme avec un tableau. Retourne une référence sur l’element a la position pos.

  

****front**** → permet d’accéder au premier élément. Retourne une référence et pas un itérateur.

  

****back**** → permet d’accéder au dernier élément. Retourne une référence et pas un itérateur.

  

****begin, end**** → retourne des iterateurs sur le debut et la fin

  

****rbegin, rend**** → retourne des reverse iterateurs sur le debut et la fin (vont aller dans le sens inverse).

  

****empty**** → retourne un bool qui permet de savoir si le container est vide ou pas.

  

****size**** → retourne le nombre d’éléments qui se trouvent dans le container

  

****max_size**** → retourne le nombre maximum que le container pour contenir

  

```cpp

void reserve( size_type new_cap );

```

  

****reserve**** → agrandie la capacité pour qu’elle soit supérieure ou égale a new cap. Si new_cap est inférieure, il ne se passe rien .

  

****capacity**** → getter de la capacity

  

****clear**** → clears the contents (efface tous les elements du container). Dans la pratique moi j’ai juste set la size a 0. Ne change pas la capacité mais rend les references etc invalides.

  

****insert**** → ajouter des éléments (trois versions, fill range et avec des iterateurs) quand on a la version avec un iterateur, on inserte avant cet iterateur.

  

****erase**** → Va permettre d effacer des elements a une position precise dans perdre le reste.

  

****push_back**** → ajouter un element a la fin

  

****pop_back**** → enleve le dernier enlement

  

```cpp

void resize( size_type count );

```

  

****resize**** → retaille le container pour qu’il contienne count elements. Si le container est plus grand, il va etre reduit au nombre demande, si le container est plus petit, on va ajouter des elements (soient avec une valeur par defaut, soit avec une valeur passee en parametres).

  

****swap**** → swap les contenus

  

## Utils

  

## Iterators “patron de conception comportemental”

  

→ Un iterateur permet de parcourir les éléments d’un conteneur.

  

> An iterator is an object that behaves like a pointer, (does content extraction and member access). The most important job of an iterator is to operate operator * _and operator → reload_

_>_

  

> An iterator is an object that points to an element inside a container. Like a pointer, an iterator can be used to access the element it points to and can be moved through the content of the container. Each container in the C++ Standard Library provides its own iterator, as well as some methods to retrieve it. Using iterators is quite easy: obtain an instance from a container, move it around where needed and then get the pointed element.

>

  

### iterators_traits

  

Traits class defining properties of iterators.

  

Les iterators traits sont utilisés par les algorithmes sandard pour determiner des proprietes aux iterateurs qui leur sont passés.

  

Pour chaque type d'itérateur il faut définir une "corresponding specialisation iterator traits" class templatée .

  

→ sont en quelques sortes les propriétés des iterateurs. Si on ne respecte pas les iterator traits, les iterateurs que l onc cree ne pourront pas etre utilisés par les algorithmes.

  

→ permet d’avoir une “interface uniforme”

  

```jsx

template <class Iterator> class iterator_traits;

template <class T> class iterator_traits<T*>;

template <class T> class iterator_traits<const T*>;

```

  

****is_integral →**** facon originale de verifier si on a affaire a un data type habituel ou si on a affaire a un iterateur.

  

****enable_if**** → va permettre d’utilise un typede type si c’est un membre public, sinon, on fera comme s’il n’avait pas ete noté.

  

[https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html](https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html)

  

****lexicographical_compare**** : presque jamais utilise, va retourne 1 si la premiere range est inferieur e (en termes d’ascii) a la deuxième.

  

****std::pair → nécessaire pour map, va nous permettre de creer une pair (first, second) / key,value****

  

****Std::pair et std::make pair****



# Stack (LIFO)

  

- Stack est le container le plus court mais il utilise vector comme underlying container donc on ne peut pas le faire sans avoir fini vector.

  

→ voir tutoriel de la youtubeuse CodingBeauty

  

→ documentation : [https://en.cppreference.com/w/cpp/container/stack](https://en.cppreference.com/w/cpp/container/stack)

  

> The `std::stack` class is a container ****adapter**** that gives the programmer the functionality of a stack - specifically, a LIFO (last-in, first-out) data structure.

>

  

> The class template ****acts as a wrapper to the underlying container (deque)**** - only a specific set of functions is provided. The stack pushes and pops the element from the back of the underlying container, known as the top of the stack.

>

  

Stack is a type of data collection which uses LIFO technique.

  

**(LIFO) → last in, first out. (last come first served)**

  

The last element you added is going to be the first you take out

  

Main functions : empty(), size(), top(), push(), pop()

  

```cpp

//Tutoriel suivi au debut du projet - STACK

#include <iostream>

#include <stack>

  

void printstackelements(Stack<int> stack)

{

//while the stack is greather than 0

//is going to ask for the top element

//pop it out

while (!stack.empty())

{

	std::cout << stack.top << std::endl;

	stack.pop();

}


int main(void)

{

stack<int> numbersStack;

if (numbersStack.empty())

{

std::cout << "stack is empty" << std::endl;

}

std::cout << "Stack size is " << numbersStack.size() << std::endl;

  

numbersStack.push(1);//adds an element at the top of the stack

numbersStack.push(2);

numbersStack.push(3);

printstackelements(numbersStack);

//numbersStack.pop();//will remove top element of the stack

//system("pause>0");

return (0);

}

```

  

# Map

  

→ Map est le plus dur des containers a implémenter. Pour cela vous allez devoir definir son iterateur et implementer d’une manière ou d’une arbre un arbre qui soit équilibré.

  

→ Il y a pas mal de fonctions en commun avec vecteur, mais il y a egalement des supplementaires.

  

→ Les nouvelles sont relatives au ****lookup**** :

  

- ****count :**** permet de vérifier si la cle est trouvee ou non, on va voir combien d’elements matchent key. On va retourner 0 ou 1 (jamais autre chose).

- ****find :**** va retourner un iterator (si la cle est trouve, on retrouve l iterateur correspondant a sa position, sinon, on a retourne end).

- ****equal_range :**** *_not less_* than `key` and another pointing to the first element *_greater_* than `key`. Permet de retourner une range entre les deux extremites qu’on cherche.

  

Les deux sont utilises pour equal_range :

  

- ****lower_bound :**** Returns an iterator pointing to the first element that is *_not less_* than (i.e. greater or equal to) `key`.

- ****upper_bound :****Iterator pointing to the first element that is *_greater_* than `key`.

  

****Observers :****

  

- ****key_comp**** : returns the function that compares keys. Returns the function object that compares the keys, which is a copy of this container's [constructor](https://en.cppreference.com/w/cpp/container/map/map) argument `comp`. (est vrai si le premier est inferieur au deuxieme).

- ****value_comp**** : returns the function that compares keys in objects of type value_type. Returns a function object that compares objects of type std::map::value_type (key-value pairs) by using [key_comp](https://en.cppreference.com/w/cpp/container/map/key_comp) to compare the first components of the pairs.

  

Stores elements in key/value pairs.

  

Each element is called pair. The best example are (language) dictionnaries.

  

Tutoriel de ****Code Beauty****:

  

[https://www.youtube.com/watch?v=aEgG4pidcKU](https://www.youtube.com/watch?v=aEgG4pidcKU)

  

On va utiliser un arbre binaire pour stocker les elements de façon “relativement” optimisée.

  

La clé porte toujours un data type simple (par exemple int), tandis que la value va être plus complexe (par exemple une liste de strings, structure, une autre map, etc ).

  

Les maps stockent des values triées et identifiables (unique).

  

**Propriétés** : “Associative” = referenced by their key, “Ordered” = follow a strict order at all times, all inserted elements are given a position in this order, “allocator aware”, “unique keys” = no two element in the container can have equivalent keys , “map” = each element associate a key to a mapped value

  

```cpp

//exemple

map<string, strign> myDictionary;

myDictionary.insert(pair<string, string>("apple", "der Apfel");

myDictionary.insert(pair<string, string>("banana", "die Banane");

```

  

→ Les donnees vont etre ajoutes par ordre ascending alphabetiquement (lexicographical compare).

  

→ Seulement les cles doivent etre uniques

  

→ Pour acceder aux valeurs on fait :

  

```cpp

//Access and change

myDictionary["apple"] = "Der Apfel";

```

  

**Autre exemple**

  

```cpp

#include <list>

  

map<string>, list<string>> pokedex;

list<string> pikachuAttacks {"thunder shock", "tail whip", "quick attack"};

  

pokedex.insert(pair<string, list<string>>("Pikachu", pikacuAttacks);

```

  

→ voir tutoriel video "Cppnuts"

  

→key/value combination / key value pair / dictionnary example

  

→the key must be unique, but not value

  

- Map est le container le plus long. La plupart des étudiants ont choisi d'implementer un Red Black Tree mais celui-ci n'est obligatoire que dans la version bonus du sujet. Implementer un arbre binaire simple devrait fonctionner meme si l'arbre serait déséquilibré si les valeurs sont uniquement dans le meme ordre (croissant / décroissant).

  

Une map a clé et une valeur donc on ne peut pas itérer dessus comme on a l'habitude de faire habituellement.

 

****→ Rebind****

 
[https://stackoverflow.com/questions/14148756/what-does-template-rebind-do](https://stackoverflow.com/questions/14148756/what-does-template-rebind-do)



Le rebind est nécessaire pour allouer nos nodes (sachant qu on utilise une list).

 

