#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

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
            typedef std::size_t														size_t;

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
                    this->_alloc.construct(this->end++, val);
            }

            // (3) range constructor
            // Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
            // enable_if는 위의 생성자와 구별하기 위해 작성
            template <class InputIterator>         
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            {
                
            }

            // (4) copy constructor
            // Constructs a container with a copy of each of the elements in x, in the same order.
            vector (const vector& x)
            {

            }

    };
    

}

#endif
