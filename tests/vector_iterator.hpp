#pragma once
#include <cstdlib>
#include <memory>

namespace ft {

    template<class TTRANCHE>
    class iterator {
        private:
            TTRANCHE *_p;
        public:
            typedef size_t size_type;
            typedef TTRANCHE value_type;
            typedef typename ft::iterator_traits<TTRANCHE>::difference_type difference_type;

            iterator(TTRANCHE *p) : _p(p)
            {
            }

            iterator& operator++()
            {
               _p++;
               return *this;
            }

            iterator& operator--()
            {
               _p--;
               return *this;
            }

            TTRANCHE& operator*()
            {
                return *_p;
            }
    };
}