#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"

#include <vector>
#include <map>
#include <stack>
#include <list>
#include <iostream>
#include <utility>

#if STD
#define NS std
#else
#define NS ft
#endif

// Util pour tests vector
void printSize(NS::vector<int> const &vct)
{
    std::cout << "size: " << vct.size() << std::endl;
    std::cout << "capacity: " << vct.capacity() << std::endl;
    std::cout << "max_size: " << vct.max_size() << std::endl;
    NS::vector<int>::const_iterator it = vct.begin();
    NS::vector<int>::const_iterator ite = vct.end();
    std::cout << std::endl
              << "Content is:" << std::endl;
    for (; it != ite; ++it)
        std::cout << "- " << *it << std::endl;
}

void printStr(NS::vector<std::string> const &vct)
{
    NS::vector<std::string>::const_iterator it = vct.begin();
    NS::vector<std::string>::const_iterator ite = vct.end();
    for (; it != ite; ++it)
        std::cout << *it << std::endl;
}

void my_ft_constructor()
{
    // First round of test
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR CONSTRUCTORS : " << std::endl;
    NS::vector<int> first;
    NS::vector<int> second(4, 100);
    NS::vector<int> third(second.begin(), second.end());

    int myints[] = {16, 2, 77, 29};
    NS::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    for (NS::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << std::endl;

    // Second round of test
    // Appel du constructeur par defaut
    std::cout << "Default constructor testing : " << std::endl;
    ft::vector<int> ft_vec;
    std::vector<int> std_vec;

    // Appel du constructeur par defaut avec un allocateur pour test
    std::cout << "Default constructor with allocator : " << std::endl;
    std::allocator<int> my_alloc;
    ft::vector<int> ft_vec1(my_alloc);

    // Test deuxieme constructeur
    std::cout << "Copying constructor with allocator : " << std::endl;
    std::vector<int> std_vec2(5);
    ft::vector<int> ft_vec2(5);

    // affichage des deux vecteurs
    ft::vector<int>::iterator it = ft_vec2.begin();
    ft::vector<int>::iterator ite = ft_vec2.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }
    std::cout << "Testing fill constructor : " << std::endl;
    std::vector<int> std_vec3(5, 4);
    ft::vector<int> ft_vec3(5, 4);
    ft::vector<int>::iterator it1 = ft_vec3.begin();
    ft::vector<int>::iterator ite1 = ft_vec3.end();
    while (it1 != ite1)
    {
        std::cout << (*it1) << std::endl;
        it1++;
    }

    std::cout << "Testing range constructor" << std::endl;
    ft::vector<int> test(ft_vec3.begin(), ft_vec3.end());
    it = test.begin();
    ite = test.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }

    std::cout << "Testing copy constructor" << std::endl;
    ft::vector<int> copy(test);
    it = copy.begin();
    ite = copy.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }
    std::cout << "OK !" << std::endl;
    std::cout << std::endl;
}

void my_ite_n1(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR BEGIN AND ITERATORS :" << std::endl;
    int size = 5;
    NS::vector<int> vct(size);

    NS::vector<int>::iterator it = vct.begin();
    for (int i = 0; i < size; ++i)
        it[i] = i;
    std::cout << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

int my_vector_copy_construct(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR COPY CONSTRUCTOR:" << std::endl;
    NS::vector<int> vct(5);
    NS::vector<int>::iterator it = vct.begin(), ite = vct.end();

    std::cout << "len: " << (ite - it) << std::endl;
    for (; it != ite; ++it)
        *it = (ite - it);

    it = vct.begin();
    NS::vector<int> vct_range(it, --(--ite));
    for (int i = 0; it != ite; ++it)
        *it = ++i * 5;

    it = vct.begin();
    NS::vector<int> vct_copy(vct);
    for (int i = 0; it != ite; ++it)
        *it = ++i * 7;
    vct_copy.push_back(42);
    vct_copy.push_back(21);

    vct = vct_copy;
    vct_copy = vct_range;

    printSize(vct);
    printSize(vct_copy);
    printSize(vct_range);

    std::cout << "OK !" << std::endl;
    std::cout << std::endl;
    return (0);
}

int my_rite_arrow(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING REVERSE ITERATOR INCREMENT/DECREMENT OPERATORS :" << std::endl;
    const int size = 5;
    NS::vector<int> vct(size);
    NS::vector<int>::reverse_iterator it(vct.rbegin());
    NS::vector<int>::const_reverse_iterator ite(vct.rend());

    for (int i = 1; it != ite; ++i)
        *it++ = (i * 7);

    it = vct.rbegin();
    ite = vct.rbegin();

    std::cout << *(++ite) << std::endl;
    std::cout << *(ite++) << std::endl;
    std::cout << *ite++ << std::endl;
    std::cout << *++ite << std::endl;

    std::cout << *(++it) << std::endl;
    std::cout << *(it++) << std::endl;
    std::cout << *it++ << std::endl;
    std::cout << *++it << std::endl;

    std::cout << *(--ite) << std::endl;
    std::cout << *(ite--) << std::endl;
    std::cout << *--ite << std::endl;
    std::cout << *ite-- << std::endl;

    std::cout << *(--it) << std::endl;
    std::cout << *(it--) << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << *--it << std::endl;
    std::cout << "OK !" << std::endl;
    return (0);
}

// TODO: ajouter d autres tests avec les autres protos
void my_ft_insert()
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR INSERT : " << std::endl;
    NS::vector<int> vec(3, 100);
    NS::vector<int>::iterator it = vec.begin();
    it = vec.insert(it, 200);
    printSize(vec);

    vec.insert(it, 2, 300);
    printSize(vec);

    // "it" no longer valid, get a new one:
    it = vec.begin();

    NS::vector<int> vec2(2, 400);
    vec.insert(it + 2, vec2.begin(), vec2.end());
    printSize(vec);

    int arr[] = {501, 502, 503};
    vec.insert(vec.begin(), arr, arr + 3);
    printSize(vec);
    std::cout << "OK !" << std::endl;
}

void my_ft_swap()
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR SWAP NON MEMBER : " << std::endl;

    NS::vector<int> one(4, 6), two(6, 7);
    NS::swap(one, two);

    for (NS::vector<int>::iterator it = one.begin(); it != one.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << std::endl;

    std::cout << "Second round of tests :" << std::endl;
    NS::vector<int> foo(3, 10);
    NS::vector<int> bar(5, 20);

    foo.swap(bar);

    for (unsigned i = 0; i < foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << std::endl;

    for (unsigned i = 0; i < bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << std::endl;

    NS::vector<int> a1;
    a1.push_back(1);
    a1.push_back(2);
    a1.push_back(3);
    NS::vector<int> a2;
    a2.push_back(4);
    a2.push_back(5);
    a1.swap(a2);
    printSize(a1);
    printSize(a2);
    std::cout << "OK !" << std::endl;
    std::cout << std::endl;
}

void my_ft_reverse_iterator()
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR REVERSE ITERATOR : " << std::endl;
    // TODO: ajouter des tests
    NS::vector<int> myvector;

    for (int i = 0; i < 10; i++)
        myvector.push_back(i);

    NS::vector<int>::reverse_iterator rev = myvector.rbegin();
    rev++;
    rev--;

    NS::vector<int>::reverse_iterator rev2 = myvector.rend();
    rev2--;
    rev2++;
    // TODO: faire des tests avec tous les overloads
    std::cout << "OK !" << std::endl;
    std::cout << std::endl;
}

void my_ft_reserve()
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR RESERVE : " << std::endl;
    NS::vector<int>::size_type sz;
    NS::vector<int> foo;
    sz = foo.capacity();
    for (int i = 0; i < 100; ++i)
    {
        foo.push_back(i);
        if (sz != foo.capacity())
        {
            sz = foo.capacity();
            std::cout << sz << ' ';
        }
    }

    NS::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);
    for (int i = 0; i < 100; ++i)
    {
        bar.push_back(i);
        if (sz != bar.capacity())
        {
            sz = bar.capacity();
            std::cout << sz << ' ';
        }
    }
    std::cout << std::endl;
    std::cout << "OK !" << std::endl;
    std::cout << std::endl;
}

void my_ft_erase()
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR ERASE : " << std::endl;
    NS::vector<int> myvector;
    for (int i = 1; i <= 10; i++)
        myvector.push_back(i);

    myvector.erase(myvector.begin() + 5);
    myvector.erase(myvector.begin(), myvector.begin() + 3);
    for (unsigned i = 0; i < myvector.size(); ++i)
        std::cout << ' ' << myvector[i];

    std::cout << std::endl;
    std::cout << "Second round of tests : " << std::endl;
    // inspire de cpp reference
    NS::vector<int> myvector2;
    for (int i = 1; i <= 10; i++)
        myvector2.push_back(i);
    myvector2.erase(myvector2.begin() + 5);
    myvector2.erase(myvector2.begin(), myvector2.begin() + 3);
    for (unsigned i = 0; i < myvector2.size(); ++i)
        std::cout << ' ' << myvector2[i];
    std::cout << std::endl;

    // reference c plus plus
    NS::vector<int> cnt;
    cnt.push_back(4);
    cnt.push_back(-1);
    cnt.push_back(10);
    cnt.push_back(2);

    NS::vector<int>::iterator it = cnt.begin();
    cnt.erase(it);
    it = cnt.begin();
    NS::vector<int>::iterator ite = cnt.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    std::cout << "OK !" << std::endl;
    std::cout << std::endl;
}

void my_vector_assign(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR  ASSIGN : " << std::endl;
    // test main de la reference c plus plus
    NS::vector<int> first;
    NS::vector<int> second;
    NS::vector<int> third;

    first.assign(7, 100);
    NS::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1);
    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3);

    std::cout << "Size of first: " << int(first.size()) << std::endl;
    std::cout << "Size of second: " << int(second.size()) << std::endl;
    std::cout << "Size of third: " << int(third.size()) << std::endl;

    // cpp reference
    NS::vector<char> characters(10);
    characters.assign(5, 'a');
    NS::vector<char>::iterator it1 = characters.begin();
    NS::vector<char>::iterator ite1 = characters.end();
    while (it1 != ite1)
    {
        std::cout << (*it1);
        it1++;
    }
    std::cout << std::endl;
    it1 = characters.begin();
    ite1 = characters.end();
    characters.assign(6, 'b');
    while (it1 != ite1)
    {
        std::cout << (*it1);
        it1++;
    }
    std::cout << std::endl;
    std::cout << "OK !";
    std::cout << std::endl;
    return;
}

void my_vector_at(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR  AT: " << std::endl;
    NS::vector<int> vec(3, 5);
    try
    {
        int &ref = vec.at(1);
        std::cout << ref << std::endl;
    }
    catch (std::out_of_range)
    {
        std::cout << "Out of range error" << std::endl;
    }
    catch (...)
    {
        std::cout << "Error" << std::endl;
    }
    // Tests reference c plus plus
    NS::vector<int> myvector(10);
    for (unsigned i = 0; i < myvector.size(); i++)
        myvector.at(i) = i;
    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector.at(i);
    std::cout << std::endl;

    // Tests reference cpp
    NS::vector<int> data(6, 6);
    data.at(1) = 88;
    std::cout << "Element at index 2 has value " << data.at(2) << std::endl;
    std::cout << "data size = " << data.size() << std::endl;
    try
    {
        data.at(5) = 666;
    }
    catch (std::out_of_range const &exc)
    {
        std::cout << exc.what() << std::endl;
    }
    NS::vector<int>::iterator it = data.begin();
    NS::vector<int>::iterator ite = data.end();
    while (it != ite)
    {
        std::cout << (*it);
        it++;
    }
    std::cout << std::endl;
    NS::vector<int> vct(7);
    for (unsigned long int i = 0; i < vct.size(); ++i)
    {
        vct.at(i) = (vct.size() - i) * 3;
        std::cout << "vct.at(): " << vct.at(i) << " | ";
        std::cout << "vct[]: " << vct[i] << std::endl;
    }
    std::cout << "OK !" << std::endl;
    return;
}

void my_vector_at_const(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR AT CONST : " << std::endl;

    // Tests reference cpp
    NS::vector<int> data(6, 6);
    data.at(1) = 88;
    std::cout << "Element at index 2 has value " << data.at(2) << std::endl;
    std::cout << "data size = " << data.size() << std::endl;
    try
    {
        data.at(5) = 666;
    }
    catch (std::out_of_range const &exc)
    {
        std::cout << exc.what() << std::endl;
    }
    std::cout << "data: " << std::endl;
    NS::vector<int>::iterator it = data.begin();
    NS::vector<int>::iterator ite = data.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void my_vector_size(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR SIZE: " << std::endl;
    ft::vector<int> myints;
    std::cout << "0. size: " << myints.size() << std::endl;

    for (int i = 0; i < 10; i++)
        myints.push_back(i);
    std::cout << "1. size: " << myints.size() << std::endl;

    myints.insert(myints.end(), 10, 100);
    std::cout << "2. size: " << myints.size() << std::endl;

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void my_vector_push_back(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTED VECTOR VECTOR PUSH BACK" << std::endl;
    NS::vector<int> vec;
    int i = 0;
    while (i < 100)
    {
        vec.push_back(i);
        i++;
    }
    NS::vector<int>::iterator it = vec.begin();
    NS::vector<int>::iterator ite = vec.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    NS::vector<int> myvector;
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);
    while (!myvector.empty())
    {
        myvector.pop_back();
    }
    printSize(myvector);

    NS::vector<int> numbers;
    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);
    printSize(numbers);
    std::cout << "OK !" << std::endl;
    return;
}

void my_capacity(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR CAPACITY : " << std::endl;
    // cpp reference
    int sz = 200;
    NS::vector<int> v1;

    unsigned long cap = v1.capacity();
    std::cout << "initial capacity=" << cap << std::endl;

    for (int n = 0; n < sz; ++n)
    {
        v1.push_back(n);
        if (cap != v1.capacity())
        {
            cap = v1.capacity();
            std::cout << "new capacity=" << cap << std::endl;
        }
    }
    std::cout << "final size=" << v1.size() << std::endl;
    std::cout << "final capacity=" << v1.capacity() << std::endl;

    NS::vector<int> myvector;
    for (int i = 0; i < 100; i++)
        myvector.push_back(i);
    std::cout << "size: " << (int)myvector.size() << std::endl;
    std::cout << "capacity: " << (int)myvector.capacity() << std::endl;
    std::cout << "max_size: " << (int)myvector.max_size() << std::endl;
    std::cout << "OK !" << std::endl;
}

void my_empty(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR EMPTY() : " << std::endl;
    // Test cplusplus reference
    NS::vector<int> myvector;
    int sum(0);

    for (int i = 1; i <= 10; i++)
        myvector.push_back(i);

    while (!myvector.empty())
    {
        sum += myvector.back();
        myvector.pop_back();
    }
    std::cout << "total: " << sum << std::endl;
    // cpp reference
    std::cout << std::boolalpha;
    std::vector<int> numbers;
    std::cout << "Initially, numbers.empty(): " << numbers.empty() << std::endl;

    numbers.push_back(42);
    std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void my_clear(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR CLEAR : " << std::endl;
    // c plus plus reference
    NS::vector<int> myvector;
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    std::cout << std::endl;

    myvector.clear();
    myvector.push_back(1101);
    myvector.push_back(2202);

    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    std::cout << "OK !" << std::endl;
    // cpp reference
    return;
}

void my_max_size(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR MAX SIZE() : " << std::endl;
    // c plus plus reference
    NS::vector<int> myvector;
    for (int i = 0; i < 100; i++)
        myvector.push_back(i);

    std::cout << "size: " << myvector.size() << std::endl;
    std::cout << "capacity: " << myvector.capacity() << std::endl;
    std::cout << "max_size: " << myvector.max_size() << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void my_vector_pop_back(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR POP BACK :" << std::endl;
    NS::vector<std::string> words;
    words.push_back("I");
    words.push_back("love");
    words.push_back("chocolate !");
    printStr(words);
    while (!words.empty())
    {
        words.pop_back();
        printStr(words);
    }
    std::cout << "OK !" << std::endl;
    return;
}

void my_resize(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR RESIZE : " << std::endl;
    NS::vector<int> myvector;
    for (int i = 1; i < 10; i++)
        myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8, 100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (unsigned long i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    std::cout << "OK !" << std::endl;
    return;
}

void my_front(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR FRONT : " << std::endl;
    std::vector<int> myvector;
    myvector.push_back(78);
    myvector.push_back(16);
    myvector.front() -= myvector.back();
    std::cout << "myvector.front() is now " << myvector.front() << std::endl;

    NS::vector<char> letters;
    letters.push_back('a');
    letters.push_back('e');
    letters.push_back('i');
    letters.push_back('o');
    letters.push_back('u');
    if (!letters.empty())
    {
        std::cout << "The first character is '" << letters.front() << std::endl;
    }
    std::cout << "OK !" << std::endl;
}

void my_back(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR BACK : " << std::endl;
    std::vector<int> myvector;

    // cplusplus reference
    myvector.push_back(10);

    while (myvector.back() != 0)
    {
        myvector.push_back(myvector.back() - 1);
    }
    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    std::cout << std::endl;

    // cpp reference
    std::vector<char> letters;
    letters.push_back('a');
    letters.push_back('b');
    letters.push_back('c');
    letters.push_back('d');

    if (!letters.empty())
    {
        std::cout << "The last character is '" << letters.back() << std::endl;
    }
    std::cout << "OK !" << std::endl;
    return;
}

void my_operator_bracket(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR OPERATOR[] : " << std::endl;
    // cplusplus reference
    NS::vector<int> myvector(10);
    NS::vector<int>::size_type sz = myvector.size();
    for (unsigned i = 0; i < sz; i++)
        myvector[i] = i;

    for (unsigned i = 0; i < sz / 2; i++)
    {
        int temp;
        temp = myvector[sz - 1 - i];
        myvector[sz - 1 - i] = myvector[i];
        myvector[i] = temp;
    }
    for (unsigned i = 0; i < sz; i++)
        std::cout << ' ' << myvector[i];
    std::cout << "OK !" << std::endl;
    return;
}

void my_get_allocator(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR GET ALLOCATOR : " << std::endl;
    // cplusplus reference
    NS::vector<int> myvector;
    int *p;
    unsigned int i;

    // allocate an array with space for 5 elements using vector's allocator:
    p = myvector.get_allocator().allocate(5);

    // construct values in-place on the array:
    for (i = 0; i < 5; i++)
        myvector.get_allocator().construct(&p[i], i);

    for (i = 0; i < 5; i++)
        std::cout << ' ' << p[i];
    std::cout << std::endl;

    // destroy and deallocate:
    for (i = 0; i < 5; i++)
        myvector.get_allocator().destroy(&p[i]);
    myvector.get_allocator().deallocate(p, 5);
    std::cout << "OK !" << std::endl;
    return;
}

void my_operator_assignation(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR ASSIGNATION : " << std::endl;
    // c plus plus
    NS::vector<int> foo(3, 0);
    NS::vector<int> bar(5, 0);

    bar = foo;

    std::cout << "Size of foo: " << int(foo.size()) << std::endl;
    std::cout << "Size of bar: " << int(bar.size()) << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

// https://docs.microsoft.com/fr-fr/cpp/standard-library/reverse-iterator-class?view=msvc-170
void my_reverse_operator_overloads(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING REVERSE OPERATOR OVERLOADS : " << std::endl;
    NS::vector<int> vec(5, 2);
    vec.push_back(17);

    NS::vector<int>::reverse_iterator rev = vec.rbegin();
    NS::vector<int>::reverse_iterator reve = vec.rend();
    std::cout << (rev == reve) << std::endl;
    std::cout << (rev != reve) << std::endl;
    std::cout << (rev > reve) << std::endl;
    std::cout << (rev < reve) << std::endl;
    std::cout << (rev >= reve) << std::endl;
    std::cout << (rev <= reve) << std::endl;

    // Arithmetique
    NS::vector<int>::reverse_iterator rev1 = rev + 1;
    NS::vector<int>::reverse_iterator rev2 = rev - 1;

    (void)rev1;
    (void)rev2;
    std::cout << "OK !" << std::endl;
    return;
}

void my_integral_constant(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING UTILS MY INTEGRAL CONSTANT : " << std::endl;
    std::cout << NS::is_integral<char>::value << std::endl;
    std::cout << NS::is_integral<int>::value << std::endl;
    std::cout << NS::is_integral<NS::vector<int>::iterator>::value << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void my_iterator_traits(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING UTILS ITERATOR TRAITS : " << std::endl;
    // Test de c plus plus reference
    typedef NS::iterator_traits<int *> traits;
    if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator" << std::endl;
    // Ajouts tests perso
    if (typeid(traits::iterator_category) == typeid(std::input_iterator_tag))
        std::cout << "int* is an input_iterator_tag" << std::endl;
    if (typeid(traits::iterator_category) == typeid(std::output_iterator_tag))
        std::cout << "int* is a output_iterator_tag" << std::endl;
    if (typeid(traits::iterator_category) == typeid(std::forward_iterator_tag))
        std::cout << "int* is a forward_iterator_tag" << std::endl;
    if (typeid(traits::iterator_category) == typeid(std::bidirectional_iterator_tag))
        std::cout << "int* is a bidirectional_iterator_tag" << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

// Test enable if
template <class T>
typename NS::enable_if<NS::is_integral<T>::value, bool>::type
is_odd(T i) { return bool(i % 2); }

void my_enable_if(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING UTILS MY ENABLE IF : " << std::endl;
    short int i = 1; // code does not compile if type of i is not integral
    std::cout << std::boolalpha;
    std::cout << "i is odd: " << is_odd(i) << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

// Utils pour tester lexicographical compare
bool mycomp(char c1, char c2)
{
    return std::tolower(c1) < std::tolower(c2);
}

void my_lexico(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING UTILS LEXICOGRAPHICAL COMPARE : " << std::endl;

    char foo[] = "Apple";
    char bar[] = "apartment";

    std::cout << std::boolalpha;
    std::cout << "Comparing foo and bar lexicographically (foo<bar): " << std::endl;

    std::cout << "Using default comparison (operator<): ";
    std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9);
    std::cout << std::endl;

    std::cout << "Using mycomp as comparison object: ";
    std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp);
    std::cout << "OK !" << std::endl;
    return;
}

void my_vector_iterator(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTOR ITERATORS : " << std::endl;
    // Declaration
    NS::vector<std::string> words;
    words.push_back("je");
    words.push_back("teste");
    words.push_back("les");
    words.push_back("iterateurs");

    NS::vector<std::string>::iterator it = words.begin();
    NS::vector<std::string>::iterator ite = words.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    it = words.begin();
    // Overloads
    ite--;
    std::cout << (it == ite) << std::endl;
    std::cout << (it != ite) << std::endl;
    std::cout << (it > ite) << std::endl;
    std::cout << (it >= ite) << std::endl;
    std::cout << (it < ite) << std::endl;
    std::cout << (it <= ite) << std::endl;
    it = it + 2;
    it = it - 2;
    it += 2;
    it -= 2;
    ite--;
    std::ptrdiff_t diff = ite - it;
    (void)diff;
    std::cout << "OK !" << std::endl;
    return;
}

// STACK
void my_stack_empty(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING STACK EMPTY :" << std::endl;
    NS::stack<int> mystack;
    if (mystack.empty())
        std::cout << "The stack is empty." << std::endl;
    else
        std::cout << "The stack is not empty." << std::endl;
    mystack.push(42);
    std::cout << "After adding elements, container.empty(): " << mystack.empty() << " " << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void my_stack_size(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING STACK SIZE :" << std::endl;

    // c plus plus reference
    NS::stack<int> myints;
    std::cout << "0. size: " << myints.size() << std::endl;

    for (int i = 0; i < 5; i++)
        myints.push(i);
    std::cout << "1. size: " << myints.size() << std::endl;

    myints.pop();
    std::cout << "2. size: " << myints.size() << std::endl;

    // cpp reference
    NS::stack<int> container;
    std::cout << "Initially, container.size(): " << container.size() << std::endl;
    for (int i = 0; i < 7; ++i)
        container.push(i);
    std::cout << "After adding elements, container.size(): " << container.size() << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

// Utils pour tester top
void reportStackSize(const std::stack<int> &s)
{
    std::cout << s.size() << " elements on stack" << std::endl;
}

void reportStackTop(const std::stack<int> &s)
{
    // Leaves element on stack
    std::cout << "Top element: " << s.top() << std::endl;
}

void my_stack_top(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING STACK TOP :" << std::endl;
    // c plus plus reference
    NS::stack<int> mystack;

    mystack.push(10);
    mystack.push(20);

    mystack.top() -= 5;
    std::cout << "mystack.top() is now " << mystack.top() << std::endl;

    // cpp reference
    std::stack<int> s;
    s.push(2);
    s.push(6);
    s.push(51);

    reportStackSize(s);
    reportStackTop(s);

    reportStackSize(s);
    s.pop();

    reportStackSize(s);
    reportStackTop(s);
    std::cout << "OK !" << std::endl;
    return;
}

void my_stack_push(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING STACK PUSH :" << std::endl;
    // c plus plus reference
    NS::stack<int> mystack;

    for (int i = 0; i < 5; ++i)
        mystack.push(i);
    std::cout << "Popping out elements...";
    while (!mystack.empty())
    {
        std::cout << ' ' << mystack.top();
        mystack.pop();
    }
    std::cout << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void my_stack_pop(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING STACK POP :" << std::endl;
    NS::stack<int> mystack;

    for (int i = 0; i < 5; ++i)
        mystack.push(i);
    std::cout << "Popping out elements...";
    while (!mystack.empty())
    {
        std::cout << ' ' << mystack.top();
        mystack.pop();
    }
    std::cout << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void my_make_pair(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING UTILS MAKE PAIR :" << std::endl;

    NS::pair<int, int> foo;
    NS::pair<int, int> bar;

    foo = NS::make_pair(10, 20);
    bar = NS::make_pair(10.5, 'A');
    std::cout << "foo: " << foo.first << ", " << foo.second << std::endl;
    std::cout << "bar: " << bar.first << ", " << bar.second << std::endl;
    std::cout << "OK !" << std::endl;
    return;
}

void printMap(NS::map<int, std::string> mymap)
{
#if NS == std
    NS::map<int, std::string>::iterator it = mymap.begin();
#else
    ft::map<int, mkstd::string>::map_iterator it = mymap.begin();
#endif
    (void)it;
#if NS == std
    NS::map<int, std::string>::iterator ite = mymap.end();
#else
    ft::map<int, std::string>::map_iterator ite = mymap.end();
#endif
    (void)ite;
    while (it != ite)
    {
        std::cout << "key : " << (*it).first << ", value : " << (*it).second << std::endl;
        it++;
    }
    return;
}

void my_key_comp(void)
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING MAP KEY COMP:" << std::endl;
    NS::map<char, int> mymap;
    NS::map<char, int>::key_compare mycomp = mymap.key_comp();

    mymap['a'] = 100;
    mymap['b'] = 200;
    mymap['c'] = 300;

    char highest = mymap.rbegin()->first;
    NS::map<char, int>::iterator it = mymap.begin();
    while (mycomp((*it++).first, highest))
    {
        std::cout << it->first << " => " << it->second << std::endl;
    }
    std::cout << "OK !" << std::endl;
}

// TODO: tester le make pair aussi
void my_map_value_compare(void)
{
    // NS::map<int, std::string> mymap;
    // TODO: a reutiliser
    /*
    NS::map<int, std::string> mymap;

    // Le insert va permettre de trier la map
    mymap.insert(NS::make_pair(1, "coucou"));
    mymap.insert(NS::make_pair(58, "blabla"));
    mymap.insert(NS::make_pair(-1, "blublu"));
    printMap(mymap);

#if NS == std
    NS::map<int, std::string>::iterator ite = mymap.end();
#else
    ft::map<int, std::string>::map_iterator ite = mymap.end();
#endif
    (void)ite;
    */

    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING MAP KEY COMP:" << std::endl;
    NS::map<char, int> mymap;

    mymap['x'] = 1001;
    mymap['y'] = 2002;
    mymap['z'] = 3003;

    NS::pair<char, int> highest = *mymap.rbegin();
    NS::map<char, int>::iterator it = mymap.begin();

    (void)it;
    (void)highest;
    //
    while (mymap.value_comp()(*it++, highest))
    {
        std::cout << it->first << " => " << it->second << std::endl;
    }
    std::cout << "OK !" << std::endl;
    return;
}

int main(void)
{
    // TODO: ajouter les tests qui sont ecrits dans le main du sujet
    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING UTILS :" << std::endl;
    my_map_value_compare();
    my_key_comp();
    // TODO: tester tous les utils
    /*
    my_vector_iterator();
    my_lexico();
    my_iterator_traits();
    my_enable_if();
    my_integral_constant();
    my_make_pair();
    my_reverse_operator_overloads();

    std::cout << "-----------------------------" << std::endl;
    std::cout << "TESTING VECTORS :" << std::endl;
    my_ft_constructor();
    my_vector_copy_construct();
    my_operator_assignation();
    my_vector_assign();
    my_get_allocator();

    //Element access
    my_vector_at();
    my_vector_at_const();
    my_operator_bracket();
    my_front();
    my_back();

    //Iterators (inspirés du testeur mli)
    my_ite_n1();
    my_ft_reverse_iterator();
    my_rite_arrow();
    my_ft_reserve();

    //Capacity
    my_empty();
    my_vector_size();
    my_max_size();
    my_capacity();

    //Modifiers
    my_clear();
    my_ft_insert();
    my_ft_erase();
    my_vector_push_back();
    my_vector_pop_back();
    my_resize();
    my_ft_swap();


    std::cout << "--- END OF VECTOR TESTS ---" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    //Tests stack
    std::cout << "TESTING STACK :" << std::endl;
    my_stack_empty();
    my_stack_size();
    my_stack_push();
    my_stack_pop();
    my_stack_top();
    std::cout << "--- END OF STACK TESTS ---" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    //Tests map
    std::cout << "TESTING MAP :" << std::endl;
    std::cout << "--- END OF MAP TESTS ---" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    */
    return (0);
}