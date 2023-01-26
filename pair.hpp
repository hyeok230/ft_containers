#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1  first_type;
        typedef T2  second_type;

        T1 first;
        T2 second;
        
        // (1) default constructor
        // Constructs a pair object with its elements value-initialized.
        pair(): first(), second() {}

        // (2) copy / move constructor (and implicit conversion)
        // The object is initialized with the contents of the pr pair object.
        // The corresponding member of pr is passed to the constructor of each of its members.
        template<class U, class V> 
        pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}

        // (3) initialization constructor
        // Member first is constructed with a and member second with b.
        pair (const first_type& a, const second_type& b): first(a), second(b) {}

        pair& operator= (const pair& pr)
        {
            if (this == &other)
                return *this;
            first = other.first;
            second = other.second;
            return *this;
        }
    };
    // relational operators (pair)
    template <class T1, class T2>  bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first == rhs.first && lhs.second == rhs.second; }
    template <class T1, class T2>  bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs = rhs); }
    template <class T1, class T2>  bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }
    template <class T1, class T2>  bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs < lhs); }
    template <class T1, class T2>  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs < lhs; }
    template <class T1, class T2>  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs < rhs); }

    template <typename T1, typename T2>
	inline ft::pair<T1, T2> make_pair(T1 first, T2 second)
	{ return ft::pair<T1, T2>(first, second); }
}

#endif