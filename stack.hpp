#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft 
{
    template<typename T, typename Container = ft::vector<T> >
    class stack
    {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;

            // C++11
		    // T&
		    // typedef typename container_type::reference			reference;
		    // const T&
		    // typedef typename container_type::const_reference	const_reference;
        protected:
            container_type      c;
        public:
            explicit stack (const container_type& ctnr = container_type()): c(ctnr) {}
            
            virtual ~stack() {}
            
            bool empty() const
            {
                return this->c.empty();
            }

            size_type size() const
            {
                return this->c.size();
            }

            value_type& top()
            {
                return this->c.back();
            }

            const value_type& top() const
            {
                return this->c.back();
            }

            void push (const value_type& val)
            {
                return this->c.push_back(val);
            }

            void pop()
            {
                this->c.pop_back();
            }

            template <typename Tp, typename C>
            friend bool operator==(const stack<Tp, C>& lhs, const stack<Tp, C>& rhs);
            template <typename Tp, typename C>
		    friend bool operator<(const stack<Tp, C>& lhs, const stack<Tp, C>& rhs);
    };

    template <typename T, typename Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template <typename T, typename Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <typename T, typename Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif