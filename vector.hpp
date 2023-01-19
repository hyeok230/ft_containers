#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "type_traits.hpp"

namespace ft
{
    template <typename T, typename Allocator = std::allocator<T> >
    class vector
    {
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
            // 위 두개 타입 바꿀 수 있는지 확인하기


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
                this->_end = this->start;
                this->_end_capacity = this->_start + n;
                pointer x_start = this->_start;
                while (n--)
                    this->_alloc.construct(this->_end++, *x_start++);
            }

            // This destroys all container elements, and deallocates all the storage capacity allocated 
            // by the vector using its allocator.
            ~vector()
            {
                this->clear();
                this->_alloc.deallocate(this->_start, this->capacity());
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

    };
    

}

#endif
