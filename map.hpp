#ifndef MAP_HPP
#define MAP_HPP

#include "rb_tree.hpp"

namespace ft
{
    template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
            typedef Key                                                                 key_type;
            typedef T                                                                   mapped_type;
            typedef ft::pair<const key_type, mapped_type>                               value_type;
            typedef Compare                                                             key_compare;
            typedef Alloc                                                               allocator_type;
            typedef typename allocator_type::reference                                  reference;
            typedef typename allocator_type::const_reference                            const_reference;
            typedef typename allocator_type::pointer                                    pointer;
            typedef typename allocator_type::const_pointer                              const_pointer;
            typedef typename std::ptrdiff_t                                             difference_type;
            typedef typename std::size_t                                                size_type;
            class value_compare : public std::binary_function<value_type, value_type, bool>
            {
                friend class		map;
            
                protected :
                    key_compare			comp;
                    value_compare(key_compare c) : comp(c) {}
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator()(const value_type& x, const value_type& y) const
                    { return comp(x.first, y.first); }
            };
            typedef typename ft::rb_tree<value_type, value_compare, allocator_type>     tree_type;
            typedef typename tree_type::iterator                                        iterator;
			typedef typename tree_type::const_iterator                                  const_iterator;
			typedef typename tree_type::reverse_iterator		                        reverse_iterator;
		    typedef typename tree_type::const_reverse_iterator	                        const_reverse_iterator;	
        private:
            tree_type		_tree;
        public:
            // (1) empty container constructor (default constructor)
            // Constructs an empty container, with no elements.
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc) {}

            // (2) range constructor
            // Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range.
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc)
            {
                this->insert(first, last);
            }

            // (3) copy constructor
            // Constructs a container with a copy of each of the elements in x.
            map (const map& x): _tree(x._tree) {}

            ~map() {}

            map& operator= (const map& x)
            {
                if (this != &x)
                    _tree = x._tree;
                return (*this);
            }

            // ============================================Iterators============================================
            iterator begin() { return (_tree.begin()); }
            const_iterator begin() const { return (_tree.begin()); }
            iterator end() { return (_tree.end()); }
            const_iterator end() const { return (_tree.end()); }
            reverse_iterator rbegin() { return (_tree.rbegin()); }
            const_reverse_iterator rbegin() const { return (_tree.rbegin()); }
            reverse_iterator rend() { return (_tree.rend()); }
            const_reverse_iterator rend() const { return (_tree.rend()); }

            // =============================================Capacity=============================================
            bool empty() const { return (_tree.empty()); }
            size_type size() const { return (_tree.size()); }
            size_type max_size() const { return (_tree.max_size()); }

            // ===========================================Element access===========================================
            mapped_type& operator[](const key_type& k) 
            { return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second; }

            // =============================================Modifiers=============================================
            ft::pair<iterator, bool> insert(const value_type& x) { return (_tree.insert(x)); }
            iterator insert(iterator position, const value_type& x) { return (_tree.insert(position, x)); }
            template <typename InputIterator>
            void insert(InputIterator first, InputIterator last) { return (_tree.insert(first, last)); }
            void erase(iterator position) { return (_tree.erase(position)); }
            size_type erase(const key_type& x) { return (_tree.erase(ft::make_pair(x, mapped_type()))); }
            void erase(iterator first, iterator last) { _tree.erase(first, last); }
            void swap(map& x) { _tree.swap(x._tree); }
            void clear() { _tree.clear(); }

            // =============================================Observers=============================================
            key_compare key_comp() const { return (key_compare()); }
            value_compare value_comp() const { return (_tree.value_comp()); }

            // =============================================Operations=============================================
            iterator find(const key_type& x)
            { return (_tree.find(ft::make_pair(x, mapped_type()))); }
            const_iterator find(const key_type& x) const
            { return (_tree.find(ft::make_pair(x, mapped_type()))); }

            size_type count(const key_type& x) const
            { return (_tree.count(ft::make_pair(x, mapped_type()))); }
            
            iterator lower_bound(const key_type& x)
            { return (_tree.lower_bound(ft::make_pair(x, mapped_type()))); }
            const_iterator lower_bound(const key_type& x) const
            { return (_tree.lower_bound(ft::make_pair(x, mapped_type()))); }
            iterator upper_bound(const key_type& x)
            { return (_tree.upper_bound(ft::make_pair(x, mapped_type()))); }
            const_iterator upper_bound(const key_type& x) const
            { return (_tree.upper_bound(ft::make_pair(x, mapped_type()))); }
            
            ft::pair<iterator,iterator> equal_range(const key_type& x) 
            { return (_tree.equal_range(ft::make_pair(x, mapped_type()))); }
            ft::pair<const_iterator,const_iterator> equal_range(const key_type& x) const 
            { return (_tree.equal_range(ft::make_pair(x, mapped_type()))); }

            // =============================================Allocator=============================================
            allocator_type get_allocator() const { return _tree.get_allocator(); }
    };

    template <class Key_, class T_, class Compare_, class Alloc>
	bool operator==(const ft::map<Key_,T_,Compare_,Alloc>& x, const ft::map<Key_,T_,Compare_,Alloc>& y)
	{
		if (x.size() != y.size())
			return (false);
		return (ft::equal(x.begin(), x.end(), y.begin()));
	}
    template <class Key_, class T_, class Compare_, class Alloc>
	bool operator!=(const map<Key_,T_,Compare_,Alloc>& x, const map<Key_,T_,Compare_,Alloc>& y) { return (!(x == y)); }

	template <class Key_, class T_, class Compare_, class Alloc>
	bool operator< (const map<Key_,T_,Compare_,Alloc>& x, const map<Key_,T_,Compare_,Alloc>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <class Key_, class T_, class Compare_, class Alloc>
	bool operator> (const map<Key_,T_,Compare_,Alloc>& x, const map<Key_,T_,Compare_,Alloc>& y) { return (y < x); }

	template <class Key_, class T_, class Compare_, class Alloc>
	bool operator>=(const map<Key_,T_,Compare_,Alloc>& x, const map<Key_,T_,Compare_,Alloc>& y) { return !(x < y); }

	template <class Key_, class T_, class Compare_, class Alloc>
	bool operator<=(const map<Key_,T_,Compare_,Alloc>& x, const map<Key_,T_,Compare_,Alloc>& y) { return !(y < x); }

    template <class Key_, class T_, class Compare_, class Alloc>
    void swap(ft::map<Key_, T_, Compare_, Alloc>& x, ft::map<Key_, T_, Compare_, Alloc>& y) { x.swap(y); }
}

#endif