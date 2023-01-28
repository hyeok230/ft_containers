#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <typename T, typename Allocator = std::allocator<T> >
    class vector
    {
        private:
            typedef vector<T, Allocator> vector_type;
        public:
            typedef T                                                               value_type;
            typedef Allocator                                                       allocator_type;
            typedef typename allocator_type::reference                              reference;
            typedef typename allocator_type::const_reference                        const_reference;
            typedef typename allocator_type::pointer                                pointer;
            typedef typename allocator_type::const_pointer                          const_pointer;
            typedef ft::random_access_iterator<pointer, vector_type>				iterator;
            typedef ft::random_access_iterator<const_pointer, vector_type>			const_iterator;
            typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
            // 	a signed integral type, identical to: iterator_traits<iterator>::difference_type
            typedef std::ptrdiff_t													difference_type;
            // an unsigned integral type that can represent any non-negative value of difference_type
            typedef std::size_t														size_type;



        protected:
            allocator_type  _alloc;
            pointer         _start;
            pointer         _end;
            pointer         _end_capacity;

        public:
            // (1) empty container constructor (default constructor)
            // Constructs an empty container, with no elements.
            explicit vector (const allocator_type& alloc = allocator_type()): _alloc(alloc), _start(0), _end(0), _end_capacity(0) {}
            
            // (2) fill constructor
            // Constructs a container with n elements. Each element is a copy of val.
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _start(0), _end(0), _end_capacity(0)
            {
                this->_start = this->_alloc.allocate(n);
                this->_end = this->_start;
                this->_end_capacity = this->_start + n;
                while (n--)
                    this->_alloc.construct(this->_end++, val);
            }

            // (3) range constructor
            // Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
            // enable_if는 위의 생성자의 n이 size_type이기 때문에 int인자의 경우 캐스팅이 일어나야하기 때문에 아래의 생성자가 불러짐 이를 막기 위해 (자세한 내용은 README)
            template <class InputIterator>         
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0): _alloc(alloc)
            {
                if (&(*first) > &(*last))
                    throw std::length_error("vector");
                size_type n = ft::difference(first, last);
                this->_start = this->_alloc.allocate(n);
                this->_end = this->_start;
                this->_end_capacity = this->_start + n;
                while (n--)
                    this->_alloc.construct(this->_end++, *first++);
            }

            // (4) copy constructor
            // Constructs a container with a copy of each of the elements in x, in the same order.
            vector (const vector& x): _alloc(x._alloc)
            {
                size_type n = x.size();
                this->_start = this->_alloc.allocate(n);
                this->_end = this->_start;
                this->_end_capacity = this->_start + n;
                pointer x_start = x._start;
                while (n--)
                    this->_alloc.construct(this->_end++, *x_start++);
            }

            // This destroys all container elements, and deallocates all the storage capacity allocated 
            // by the vector using its allocator.
            ~vector()
            {
                this->clear();
                this->_alloc.deallocate(this->_start, this->capacity());
                this->_end_capacity = this->_start;
            }

            // Copies all the elements from x into the container.
            // The container preserves its current allocator, which is used to allocate storage in case of reallocation.
            // Any elements held in the container before the call are either assigned to or destroyed.
            vector& operator= (const vector& x)
            {
                if (*this == x)
                    return *this;
                this->clear();
                this->_alloc.deallocate(this->_start, this->capacity());
                size_type n = x.size();
                this->_start = this->_alloc.allocate(n);
                this->_end = this->_start;
                this->_end_capacity = this->_start + n;
                pointer x_start = x._start;
                while (n--)
                    this->_alloc.construct(this->_end++, *x_start++);
                return *this;
            }
            
            // ============================================Iterators============================================

            // Returns an iterator pointing to the first element in the vector.
            iterator begin() { return iterator(this->_start); }
            const_iterator begin() const { return const_iterator(this->_start); }

            // Returns an iterator referring to the past-the-end element in the vector container.
            iterator end() { return iterator(this->_end); }
            const_iterator end() const { return const_iterator(this->_end); }

            // Returns a reverse iterator pointing to the last element in the vector
            reverse_iterator rbegin() { return reverse_iterator(this->end()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

            // Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
            reverse_iterator rend() { return reverse_iterator(this->begin()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

            // =============================================Capacity=============================================

            // Returns the number of elements in the vector.
            size_type size() const { return (size_type(this->end() - this->begin())); }

            // Returns the maximum number of elements that the vector can hold.
            size_type max_size() const { return (this->_alloc.max_size()); }

            // Resizes the container so that it contains n elements.
            void resize (size_type n, value_type val = value_type())
            {
                if (n > this->max_size())
                    throw std::out_of_range("vector::resize");
                if (n < this->size())
                    this->erase(this->begin() + n, this->end());
                else 
                    this->insert(this->end(), n - this->size(), val);
            }

            // Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
            size_type capacity() const { return size_type(this->_end_capacity - this->_start); }

            // Returns whether the vector is empty (i.e. whether its size is 0).
            bool empty() const { return this->begin() == this->end(); }

            // Requests that the vector capacity be at least enough to contain n elements.
            void reserve (size_type n)
            {
                if (n > this->max_size())
                    throw std::out_of_range("vector::reserve");
                if (n > this->size())
                {
                    pointer pre_start = this->_start;
                    pointer pre_end = this->_end;
                    size_type pre_capacity = this->capacity();

                    this->_start = this->_alloc.allocate(n);
                    this->_end = this->_start;
                    this->_end_capacity = this->_start + n;

                    for (pointer it = pre_start; it != pre_end; it++)
                        this->_alloc.construct(this->_end++, *it);
                    for (pointer it = pre_start; it != pre_end; it++)
                        this->_alloc.destroy(it);
                    this->_alloc.deallocate(pre_start, pre_capacity);
                }
            }

            // ===========================================Element access===========================================
            
            // Returns a reference to the element at position n in the vector container.
            reference operator[] (size_type n) { return *(this->begin() + n); }
            const_reference operator[] (size_type n) const { return *(this->begin() + n); }

            // Returns a reference to the element at position n in the vector.
            // The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not.
            reference at (size_type n)
            {
                if (n >= this->size())
                    throw std::out_of_range("ft::vector");
                return (*this)[n];
            }
            const_reference at (size_type n) const
            {
                if (n >= this->size())
                    throw std::out_of_range("ft::vector");
                return (*this)[n];
            }

            // Returns a reference to the first element in the vector.
            reference front() { return *begin(); }
            const_reference front() const { return *begin(); }

            // Returns a reference to the last element in the vector.
            reference back() { return *(end()- 1); }
            const_reference back() const { return *(end()- 1); }

            // ===========================================Modifiers===========================================

            // Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
            template <class InputIterator>  
            void assign (InputIterator first, InputIterator last, 
                            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
            {
                size_type n = ft::difference(first, last);
                this->clear();
                if (n > this->capacity())
                {
                    this->_alloc.deallocate(this->_start, this->capacity());
                    this->_start = this->_alloc.allocate(n);
                    this->_end = this->_start;
                    this->_end_capacity = this->_start + n;
                }
                while (n--)
                    this->_alloc.construct(this->_end++, *first++);
            }

            void assign (size_type n, const value_type& val)
            {
                this->clear();
                if (n > this->capacity())
                {
                    this->_alloc.deallocate(this->_start, this->capacity());
                    this->_start = this->_alloc.allocate(n);
                    this->_end = this->_start;
                    this->_end_capacity = this->_start + n;
                }
                while (n--)
                    this->_alloc.construct(this->_end++, val);
            }

            // Adds a new element at the end of the vector, after its current last element. 
            // The content of val is copied (or moved) to the new element.
            void push_back (const value_type& val)
            {
                if (this->_end == this->_end_capacity)
                    this->empty() ? this->reserve(1) : this->reserve(this->capacity() * 2);
                this->_alloc.construct(this->_end++, val);
            }
            
            // Removes the last element in the vector, effectively reducing the container size by one.
            void pop_back()
            {
                if (!this->empty())
                    this->_alloc.destroy(--this->_end);
            }

            // The vector is extended by inserting new elements before the element at the specified position, 
            // effectively increasing the container size by the number of elements inserted.

            // single element (1)
            iterator insert (iterator position, const value_type& val)
            {
                size_type n = position - this->begin();
                this->insert(position, 1, val);
                return this->begin() + n;
            }

            // fill (2)
            void insert (iterator position, size_type n, const value_type& val)
            {
                size_type pos = position - this->begin();
                if (this->max_size() - this->size() < n)
                    throw std::length_error ("vector::insert");
				if (this->begin() > position || position > this->end())
                    throw std::out_of_range("vector::insert");
                if (n > 0)
                {
                    if (this->capacity() >= this->size() + n)
                    {
                        for (size_type i = 0; i < this->size() - pos; i++)
                        {
                            this->_alloc.construct(this->_end + (n - 1) - i, *(this->_end - i - 1));
                            this->_alloc.destroy(this->_end - i - 1);
                        }
                        this->_end += n;
                        for (size_type i = 0; i < n; i++)
					        this->_alloc.construct(this->_start + pos + i, val);
                    }
                    else 
                    {
                        // size_type next_capacity = this->size() + n;
                        size_type next_capacity;
                        if (n + this->size() > this->capacity() * 2)
                            next_capacity =  this->size() + n;
                        else
                            next_capacity = this->capacity() * 2;

                        pointer pre_start = this->_start;
                        size_type pre_size = this->size();
                        size_type pre_capacity = this->capacity();

                        this->_start = this->_alloc.allocate(next_capacity);
                        this->_end = this->_start;
                        this->_end_capacity = this->_start + next_capacity;

                        for (size_type i = 0; i < pos; i++)
                        {
                            this->_alloc.construct(this->_end++, *(pre_start + i));
				            this->_alloc.destroy(pre_start + i);
                        }
                        for (size_type i = 0; i < n; i++)
                        {
                            this->_alloc.construct(this->_end++, val);
                        }
                        for (size_type i = 0; i < pre_size - pos; i++)
			            {
                            this->_alloc.construct(this->_end++, *(pre_start + pos + i));
				            this->_alloc.destroy(pre_start + pos + i);
                        }
                        this->_alloc.deallocate(pre_start, pre_capacity);
                    }
                }
            }

            // range (3)
            template <class InputIterator>    
            void insert (iterator position, InputIterator first, InputIterator last,
                            typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                size_type pos = position - this->begin();
                size_type n = ft::difference(first, last);

                if (this->begin() > position || position > this->end() || &(*first) > &(*last))
                    throw std::out_of_range("vector::insert");
                if (max_size() - this->size() < n)
                    throw std::length_error ("vector::insert");
                if (n > 0)
                {
                    if (this->capacity() >= this->size() + n)
                    {
                        for (size_type i = 0; i < this->size() - pos; i++)
                        {
                            this->_alloc.construct(this->_end + (n - 1) - i, *(this->_end - i - 1));
                            this->_alloc.destroy(this->_end - i - 1);
                        }
                        this->_end += n;
                        for (size_type i = 0; i < n; i++, first++)
					        this->_alloc.construct(this->_start + pos + i, *first);
                    }
                    else
                    {
                        // size_type next_capacity = this->size() + n;
                        size_type next_capacity;
                        if (n + this->size() > this->capacity() * 2)
                            next_capacity =  this->size() + n;
                        else
                            next_capacity = this->capacity() * 2;

                        pointer pre_start = this->_start;
                        size_type pre_size = this->size();
                        size_type pre_capacity = this->capacity();

                        this->_start = this->_alloc.allocate(next_capacity);
                        this->_end = this->_start;
                        this->_end_capacity = this->_start + next_capacity;
                        try
                        {
                            for (size_type i = 0; i < pos; i++)
                            {
                                this->_alloc.construct(this->_end++, *(pre_start + i));
                                this->_alloc.destroy(pre_start + i);
                            }
                            for (size_type i = 0; i < n; i++, *first++)
                            {
                                this->_alloc.construct(this->_end++, *first);
                            }
                            for (size_type i = 0; i < pre_size - pos; i++)
                            {
                                this->_alloc.construct(this->_end++, *(pre_start + pos + i));
                                this->_alloc.destroy(pre_start + pos + i);
                            }
                        }
                        catch(...)
                        {
                            this->clear();
                            this->_end_capacity = this->_start;
                            throw;
                        }         
                        this->_alloc.deallocate(pre_start, pre_capacity);
                    }
                }
            }

            // Removes from the vector either a single element (position) or a range of elements ([first,last)). 
            iterator erase (iterator position)
            {
                pointer pos = &(*position);
                if (position + 1 != this->end())
                {
                    for (pointer p = pos; p + 1 != this->_end; p++)
                    {
                        this->_alloc.destroy(p);
                        this->_alloc.construct(p, *(p + 1));
                    }
                }
                this->_end--;
                this->_alloc.destroy(this->_end);
                return (iterator(pos));
            }
            
            iterator erase (iterator first, iterator last)
            {
                pointer p_first = &(*first);
                for (; &(*first) != &(*last); first++)
                    this->_alloc.destroy(&(*first));
                for (int i = 0; i < this->_end - &(*last); i++)
                {
                    this->_alloc.construct(p_first + i, *(&(*last) + i));
                    this->_alloc.destroy(&(*last) + i);
                }
                this->_end -= (&(*last) - p_first);
                return iterator(p_first);
            }

            // Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
            void swap (vector& x)
            {
                if (&x == this)
                    return ;
                
                ft::swap(this->_start, x._start);
                ft::swap(this->_end, x._end);
                ft::swap(this->_end_capacity, x._end_capacity);
            }


        // Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
        void clear()
        {
            while (this->_start != this->_end)
				this->_alloc.destroy(--this->_end);
        }

        // ===========================================Allocator===========================================

        // Returns a copy of the allocator object associated with the vector.
        allocator_type get_allocator() const
		{
			return this->_alloc;
		}
    };

    // ===========================================Non-member function overloads===========================================

    // Performs the appropriate comparison operation between the vector containers lhs and rhs.

    // The equality comparison (operator==) is performed by first comparing sizes, and if they match, 
    // the elements are compared sequentially using operator==, stopping at the first mismatch (as if using algorithm equal).

    // The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare, 
    // which compares the elements sequentially using operator< in a reciprocal manner (i.e., checking both a<b and b<a) and stopping at the first occurrence.
    template <class T, class Alloc>  
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

    template <class T, class Alloc>  
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return !(lhs == rhs); }

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return !(rhs < lhs); }

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return rhs < lhs; }

    template <class T, class Alloc>  
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    { return !(lhs < rhs); }

    // The contents of container x are exchanged with those of y. 
    // Both container objects must be of the same type (same template parameters), although sizes may differ.
    template <class T, class Alloc>  
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    { x.swap(y); }
}

#endif
