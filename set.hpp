#ifndef SET_HPP
#define SET_HPP

#include "rb_tree.hpp"

namespace ft
{
    template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set
    {
        public:    
            typedef Key                                                                 key_type;
            typedef Key                                                                 value_type;
            typedef Compare                                                             key_compare;
            typedef Compare                                                             value_compare;
            typedef Allocator                                                           allocator_type;
            typedef typename allocator_type::reference                                  reference;
            typedef typename allocator_type::const_reference                            const_reference;
            typedef typename allocator_type::pointer                                    pointer;
            typedef typename allocator_type::const_pointer                              const_pointer;
            typedef typename ft::rb_tree<key_type, key_compare, allocator_type>         tree_type;
            typedef typename tree_type::iterator                                        iterator;
            typedef typename tree_type::const_iterator                                  const_iterator;
            typedef typename tree_type::reverse_iterator                                 reverse_iterator;
            typedef typename tree_type::const_reverse_iterator	                        const_reverse_iterator;
            typedef typename std::ptrdiff_t                                             difference_type;
            typedef typename std::size_t                                                size_type;
        private:
            tree_type   _tree;
        public:
            explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc) {}
            template <class InputIterator>  
            set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc)
            { this->insert(first, last); }
            set (const set& x): _tree(x._tree) {}
            ~set() {}
            set& operator=(const set& x)
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

            // =============================================Modifiers=============================================
            ft::pair<iterator, bool> insert(const value_type& x) { return (_tree.insert(x)); }
            iterator insert(iterator position, const value_type& x)
            {
                (void)position;
                return (_tree.insert(x).first);
            }
            template <typename InputIterator>
            void insert(InputIterator first, InputIterator last) { _tree.insert(first, last); }
            void erase(iterator position){ _tree.erase(*position); }
            size_type erase(const key_type& x) { return (_tree.erase(x)); }
            void erase(iterator first, iterator last)
            { 
                while (first != last)
                    _tree.erase(*(first++));
            }
            void swap(set& x) { _tree.swap(x._tree); }
            void clear() { _tree.clear(); }

            // =============================================Observers=============================================
            key_compare key_comp() const { return (key_compare()); }
            value_compare value_comp() const { return (_tree.value_comp()); }

            // =============================================Operations=============================================
            iterator find(const key_type& x) { return (_tree.find(x)); }
            const_iterator find(const key_type& x) const { return (_tree.find(x)); }
            size_type count(const key_type& x) const { return (_tree.count(x)); }
            iterator lower_bound(const key_type& x) { return (_tree.lower_bound(x)); }
            const_iterator lower_bound(const key_type& x) const { return (_tree.lower_bound(x)); }
            iterator upper_bound(const key_type& x) { return (_tree.upper_bound(x)); }
            const_iterator upper_bound(const key_type& x) const { return (_tree.upper_bound(x)); }
            ft::pair<iterator,iterator> equal_range(const key_type& x) { return (_tree.equal_range(x)); }
            ft::pair<const_iterator,const_iterator> equal_range(const key_type& x) const { return (_tree.equal_range(x)); }

            // =============================================Allocator=============================================
            allocator_type get_allocator() const { return _tree.get_allocator(); }
    };

    template <class Key_, class Compare_, class Alloc>
	bool operator==(const set<Key_,Compare_,Alloc>& x, const ft::set<Key_,Compare_,Alloc>& y)
	{
		if (x.size() != y.size())
			return false;
		return ft::equal(x.begin(), x.end(), y.begin());
	}
    template <class Key_, class Compare_, class Alloc>
	bool operator!=(const set<Key_,Compare_,Alloc>& x, const set<Key_,Compare_,Alloc>& y) 
    { return !(x == y); }

	template <class Key_, class Compare_, class Alloc>
	bool operator< (const set<Key_,Compare_,Alloc>& x, const set<Key_,Compare_,Alloc>& y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key_, class Compare_, class Alloc>
	bool operator> (const set<Key_,Compare_,Alloc>& x, const set<Key_,Compare_,Alloc>& y) 
    { return y < x; }

	template <class Key_, class Compare_, class Alloc>
	bool operator>=(const set<Key_,Compare_,Alloc>& x, const set<Key_,Compare_,Alloc>& y)
    { return !(x < y); }

	template <class Key_, class Compare_, class Alloc>
	bool operator<=(const set<Key_,Compare_,Alloc>& x, const set<Key_,Compare_,Alloc>& y) 
    { return !(y < x); }

    template <class Key_, class Compare_, class Alloc>
    void swap(ft::set<Key_,  Compare_, Alloc>& x, ft::set<Key_,  Compare_, Alloc>& y) 
    { x.swap(y); }
}

#endif