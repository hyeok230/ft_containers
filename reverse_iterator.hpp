#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_base.hpp"

namespace ft
{
    template <class Iterator> 
    class reverse_iterator : public ft::iterator< typename ft::iterator_traits<Iterator>::iterator_category,
								                    typename ft::iterator_traits<Iterator>::value_type,
								                    typename ft::iterator_traits<Iterator>::difference_type,
								                    typename ft::iterator_traits<Iterator>::pointer,
								                    typename ft::iterator_traits<Iterator>::reference >
    {
        public:
            typedef Iterator                                                    iterator_type; 
            typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		    typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		    typedef typename ft::iterator_traits<Iterator>::reference			reference;

        protected:
            iterator_type		_current;
        
        public:
            // (1) default constructor
            // Constructs a reverse iterator that points to no object.
            // The internal base iterator is value-initialized.
            reverse_iterator() : _current() {}

            // (2) initalization constructor
            // Constructs a reverse iterator from some original iterator it. The behavior of the constructed object replicates the original, except that it iterates through its pointed elements in the reverse order.
            explicit reverse_iterator (iterator_type it) : _current(it) {}

            // (3) copy / type-cast constructor
            // Constructs a reverse iterator from some other reverse iterator. The constructed object keeps the same sense of iteration as rev_it.
            template <class Iter>  
            reverse_iterator (const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {}

            virtual ~reverse_iterator() {}

            // Returns a copy of the base iterator.
            iterator_type base() const { return _current; }

            reference operator*() const { Iterator tmp = _current; return *--tmp; }
            reverse_iterator& operator++() { --_current; return *this; }
		    reverse_iterator operator++(int) { reverse_iterator tmp(*this); --_current; return tmp; }
            reverse_iterator& operator--() { ++_current; return *this; }
		    reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++_current; return tmp; }
            reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n); }
            reverse_iterator& operator+=(difference_type n) { _current -= n; return *this; }
            reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); }
            reverse_iterator& operator-=(difference_type n) { _current += n; return *this; }
            pointer operator->() const { return &(operator*()); }
            reference operator[](difference_type n) const { return *(*this + n); }
    };

    template <typename Iterator1, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() != rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() > rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() >= rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() <= rhs.base(); }

    template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
											const reverse_iterator<Iterator> &rev_it)
	{ return reverse_iterator<Iterator>(rev_it.base() - n); }

    template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(
		const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return rhs.base() - lhs.base(); }
}



#endif