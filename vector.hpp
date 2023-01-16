#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
    template <typename T, typename Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef T                                           value_type;
            typedef Allocator                                   allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            
    };
    

}

#endif
