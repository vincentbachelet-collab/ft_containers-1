#pragma once

//todo: deplacer dans les includes ?

void iterator_traits(void);

template <class BidirIt>
void std_reverse(BidirIt first, BidirIt last)
{
    typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    for (--n; n > 0; n -= 2)
    {
        typename std::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}

template <class BidirIt>
void ft_reverse(BidirIt first, BidirIt last)
{
    typename ft::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    for (--n; n > 0; n -= 2)
    {
        typename ft::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}