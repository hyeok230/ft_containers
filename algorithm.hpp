#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "iterator_base.hpp"

namespace ft
{
    template <typename InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type difference(InputIterator first, InputIterator last)
    {
        typedef typename ft::iterator_traits<InputIterator>::difference_type    size_type;
        size_type n = 0;
        for (; first != last; first++)
            n++;
        return n;
    }   

    template <typename T>
    void swap(T& a, T& b)
    {
        T c = a;
        a = b;
        b = c;
    }    

    template <typename InputIterator1, typename InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

    template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }
    
        return (first1 == last1) && (first2 != last2);
    }
}
 
#endif