#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <memory>
#include <functional>
#include <cstddef>
#include "reverse_iterator.hpp"
#include "iterator_base.hpp"
#include "algorithm.hpp"
#include "pair.hpp"

namespace ft
{
    enum color { black = 0, red = 1};

    // ============================================tree node============================================
    template <typename T>
	class rb_tree_node
	{
        public:
            typedef T                                   data_type;
            typedef color                               color_type;
            typedef rb_tree_node<data_type>*            node_ptr;
            typedef const rb_tree_node<data_type>*      const_node_ptr;

            data_type       _value;
            color_type      _color;
            node_ptr        _parent;
            node_ptr        _left;
            node_ptr        _right;

            rb_tree_node() : _value(), _color(black), _parent(), _left(), _right() {}
            rb_tree_node(const rb_tree_node &node) : _value(node._value), _color(node._color), _parent(node._parent), _left(node._left), _right(node._right) {}
            rb_tree_node &operator=(const rb_tree_node &node)
            {
                if (this != &node)
                {
                    _value = node._value;
                    _color = node._color;
                    _parent = node._parent;
                    _left = node._left;
                    _right = node._right;
                }
                return (*this);
            }

            void change_color()
            {
                _color = ((_color == red) ? black : red);
            }
    };

    // =========================================Utility function=========================================
    template <typename T>
    bool tree_is_left_child(typename rb_tree_node<T>::node_ptr node)
    {
        if (node && node->_parent && node->_parent->_left)
            return node == node->_parent->_left;
        else
            return false;
    }

    template <typename T>
    bool tree_is_left_child(typename rb_tree_node<T>::const_node_ptr node)
    {
        if (node && node->_parent && node->_parent->_left)
            return node == node->_parent->_left;
        else
            return false;
    }

    template <typename T>
    typename rb_tree_node<T>::node_ptr tree_min(typename rb_tree_node<T>::node_ptr root)
    {
        while (root->_left != NULL)
            root = root->_left;
        return root;
    }

    template <typename T>
    typename rb_tree_node<T>::const_node_ptr tree_min(typename rb_tree_node<T>::const_node_ptr root)
    {
        while (root->_left != NULL)
            root = root->_left;
        return root;
    }

    template <typename T>
    typename rb_tree_node<T>::node_ptr tree_max(typename rb_tree_node<T>::node_ptr root)
    {
        while (root->_right != NULL)
            root = root->_right;
        return root;
    }

    template <typename T>
    typename rb_tree_node<T>::const_node_ptr tree_max(typename rb_tree_node<T>::const_node_ptr root)
    {
        while (root->_right != NULL)
            root = root->_right;
        return root;
    }

    // ============================================Iterators============================================

    template <typename node_ptr, typename T>
    class rb_tree_iterator
    {
        public:
            typedef ft::bidirectional_iterator_tag      iterator_category;
            typedef std::ptrdiff_t                      difference_type;
            typedef T                                   value_type;
            typedef T*                                  Pointer;
            typedef T&                                  reference;
        
        private:
            node_ptr    _node;

        public:
            rb_tree_iterator(): _node() {}
            rb_tree_iterator(const rb_tree_iterator& iter): _node(iter._node) {}
            rb_tree_iterator(const node_ptr& n): _node(n) {}
            rb_tree_iterator& operator=(const rb_tree_iterator& iter)
            {
                if (this != &iter)
                    _node = iter._node;
                return *this;
            }
            rb_tree_iterator& operator=(const node_ptr& ptr)
            {
                _node = ptr;
                return *this;
            }
            reference operator*() const { return _node->_value; }
            Pointer operator->() const { return &_node->_value; }
            rb_tree_iterator& operator++()
            {
                if (_node->_right != NULL)
                    _node = tree_min<valu_type>(_node->_right);
                else
                {
                    while (!tree_is_left_child<value_type>(_node))
                        _node = _node->_parent;
                    _node = _node->_parent;
                }
                return *this;
            }
            rb_tree_iterator operator++(int)
            {
                rb_tree_iterator rtn(*this);
                ++(*this);
                return (rtn);
            }
            rb_tree_iterator& operator--()
            {
                if (_node->_left != NULL)
                    _node = tree_max<value_type>(_node->_left);
                else
                {
                    while (tree_is_left_child<value_type>(_node))
                        _node = _node->_parent;
                    _node = _node->_parent;
                }
                return *this;
            }
            rb_tree_iterator operator--(int)
            {
                rb_tree_iterator rtn(*this);
                --(*this);
                return rtn;
            }
            node_ptr base() const { return _node; }
    };
    
    template<typename node_ptr, typename T>
    bool operator==(const rb_tree_iterator<node_ptr, T>& rhs, const rb_tree_iterator<node_ptr, T>& lhs)
    { return rhs.base() == lhs.base(); }

    template<typename node_ptr, typename T>
    bool operator!=(const rb_tree_iterator<node_ptr, T>& rhs, const rb_tree_iterator<node_ptr, T>& lhs)
    { return rhs.base() != lhs.base(); }

    // =========================================Const Iterators=========================================
    template <typename const_node_ptr, typename T>
    class rb_tree_const_iterator
    {
        public:
            typedef ft::bidirectional_iterator_tag                                              iterator_category;
            typedef std::ptrdiff_t                                                              difference_type;
            typedef T                                                                           value_type;
            typedef const T*                                                                    pointer;
            typedef const T&                                                                    reference;
            typedef rb_tree_iterator<typename rb_tree_node<value_type>::node_ptr, value_type>   origin_iterator;
        
        private:
            const_node_ptr _node;
        
        public:
            rb_tree_const_iterator() : _node() {}
            rb_tree_const_iterator(const rb_tree_const_iterator& iter): _node(iter._node) {}
            rb_tree_const_iterator(const origin_iterator& iter): _node(iter.base()) {}
            rb_tree_const_iterator(const const_node_ptr& n): _node(n) {}
            rb_tree_const_iterator& operator=(const rb_tree_const_iterator& iter)
            {
                if (this != &iter)
                    _node = iter._node;
                return *this;
            }
            rb_tree_const_iterator& operator=(const const_node_ptr& ptr)
            {
                _node = ptr;
                return *this;
            }
            reference operator*() const { return _node->_value; }
            pointer operator->() const { return &_node->_value; }
            rb_tree_const_iterator& operator++()
            {
                if (_node->_right != NULL)
                    _node = tree_min<value_type>(_node->_right);
                else
				{
                    while (!tree_is_left_child<value_type>(_node))
                        _node = _node->_parent;
                    _node = _node->_parent;
				}
                return *this;
            }
            rb_tree_const_iterator operator++(int)
            {
                rb_tree_const_iterator rtn(*this);
                ++(*this);
                return rtn;
            }
            rb_tree_const_iterator& operator--()
            {
                if (_node->_left != NULL)
                    _node = tree_max<value_type>(_node->_left);
                else
                {
                    while (tree_is_left_child<value_type>(_node))
                        _node = _node->_parent;
                    _node = _node->_parent;
                }
                return *this;
            }
            rb_tree_const_iterator operator--(int)
            {
                rb_tree_const_iterator rtn(*this);
                --(*this);
                return rtn;
            }
            const_node_ptr base() const
            { return _node; }
    };

    template<typename const_node_ptr, typename T>
    inline bool operator==(const rb_tree_const_iterator<const_node_ptr, T>& rhs, const rb_tree_const_iterator<const_node_ptr, T>& lhs)
    { return rhs.base() == lhs.base(); }

    template<typename const_node_ptr, typename T>
    inline bool operator!=(const rb_tree_const_iterator<const_node_ptr, T>& rhs, const rb_tree_const_iterator<const_node_ptr, T>& lhs)
    { return rhs.base() != lhs.base(); }

    template<typename const_node_ptr, typename node_ptr, typename T>
    inline bool operator==(const rb_tree_const_iterator<const_node_ptr, T>& rhs, const rb_tree_iterator<node_ptr, T>& lhs)
    { return rhs.base() == lhs.base(); }

    template<typename const_node_ptr, typename node_ptr, typename T>
    inline bool operator!=(const rb_tree_const_iterator<const_node_ptr, T>& rhs, const rb_tree_iterator<node_ptr, T>& lhs)
    { return rhs.base() != lhs.base(); }

    template<typename node_ptr, typename const_node_ptr, typename T>
    inline bool operator==(const rb_tree_iterator<node_ptr, T>& rhs, const rb_tree_const_iterator<const_node_ptr, T>& lhs)
    { return rhs.base() == lhs.base(); }

    template<typename node_ptr, typename const_node_ptr, typename T>
    inline bool operator!=(const rb_tree_iterator<node_ptr, T>& rhs, const rb_tree_const_iterator<const_node_ptr, T>& lhs)
    { return rhs.base() != lhs.base(); }

    // =============================================RB tree=============================================

    
}

#endif