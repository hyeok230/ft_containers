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
            typedef T*                                  pointer;
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
            pointer operator->() const { return &_node->_value; }
            rb_tree_iterator& operator++()
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
    template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
    class rb_tree
    {
        public:
            typedef ft::rb_tree_node<T>                                         node_type;
            typedef T                                                           value_type;
            typedef Compare                                                     value_compare;
            typedef Alloc                                                       allocator_type;
            typedef typename allocator_type::template rebind<node_type>::other  node_alloc_type;
            typedef typename allocator_type::pointer							pointer;
		    typedef typename allocator_type::const_pointer 						const_pointer;
		    typedef typename allocator_type::reference							reference;
		    typedef typename allocator_type::const_reference					const_reference;
            typedef std::ptrdiff_t												difference_type;
            typedef std::size_t													size_type;
            typedef typename node_type::node_ptr                                node_ptr;
            typedef typename node_type::const_node_ptr                          const_node_ptr;
            typedef ft::rb_tree_iterator<node_ptr, value_type>                  iterator;
            typedef ft::rb_tree_const_iterator<const_node_ptr, value_type>      const_iterator;
            typedef ft::reverse_iterator<iterator>                              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;

        private:
            size_type       _size;
            node_type       _parent;
            node_ptr        _begin;
            value_compare   _compare;
            allocator_type  _value_alloc;
            node_alloc_type _node_alloc;

        public:
            rb_tree(const value_compare &comp, const allocator_type &alloc)
                : _size(), _parent(), _begin(&_parent), _compare(comp), _value_alloc(alloc), _node_alloc(alloc) {}
            rb_tree(const rb_tree &obj)
                : _size(), _parent(), _begin(&_parent), _compare(obj._compare), _value_alloc(obj._value_alloc), _node_alloc(obj._node_alloc) 
            {
                if (obj.root() != NULL)
                {
                    this->root() = this->copy(obj.root());
                    this->root()->_parent = &(this->_parent);
                }
            }
            ~rb_tree()
            {
                if (this->root() != NULL)
                {
                    this->destroy(this->root());
                    this->root() = NULL;
                    this->_begin = this->end_node();
                }
            }
            rb_tree& operator=(const rb_tree &obj)
            {
                if (this != &obj)
                {
                    this->clear();
                    this->_compare = obj._compare;
                    if (obj.root() != NULL)
                    {
                        this->root() = this->copy(obj.root());
                        this->root()->_parent = &(this->_parent);
                    }
                }
                return *this;
            }

            iterator begin() { return iterator(_begin); }
            const_iterator begin() const { return const_iterator(_begin); }
            iterator end() { return iterator(&_parent); }
            const_iterator end() const { return const_iterator(&_parent); }
            reverse_iterator rbegin() { return reverse_iterator(end()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
            reverse_iterator rend() { return reverse_iterator(begin()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

            bool empty() const { return _size == 0; }
            size_type size() const { return _size; }
            size_type max_size() const { return _node_alloc.max_size(); }

            ft::pair<iterator, bool> insert(const value_type& val)
            {
                iterator it = this->find(val);
                if (it != this->end())
                    return (ft::make_pair<iterator, bool>(it, false));
                node_ptr new_node = this->make_node(val);
                iterator pos;
                this->root() = this->insert(this->root(), new_node, pos);
                root()->_parent = &this->_parent;
                this->insert_sort(new_node);
                this->root()->_color = black;
                return ft::make_pair(pos, true);
            }

            iterator insert(iterator position, const value_type& val)
            {
                (void)position;
                return (insert(val).first);
            }

            template<typename InputIterator>
            void insert(InputIterator first, InputIterator last)
            {
                for (; first != last; first++)
                    insert(*first);
            }

            void erase(iterator position)
            {
                node_ptr node = position.base();
                if (node == this->_begin)
                {
                    position++;
                    this->_begin = position.base();
                }
                this->erase(this->root(), node);
                if (this->root() != NULL)
                {
                    this->root()->_parent = this->end_node();
                    this->root()->_color = black;
                }
                this->destroy_node(node);
            }

            size_type erase(const value_type& val)
            {
                iterator iter = this->find(val);
                if (iter == this->end())
                    return 0;
                erase(iter);
                return 1;
            }

            void erase(iterator first, iterator last)
            {
                while (first != last)
                    erase(first++);
            }

            void swap(rb_tree& t)
            {
                ft::swap(this->_begin, t._begin);
                ft::swap(this->_parent._left, t._parent._left);
                ft::swap(this->_size, t._size);
                if (this->_size != 0 && t._size != 0)
                	ft::swap(this->root()->_parent, t.root()->_parent);
                else if (this->_size != 0)
                	this->root()->_parent = this->end_node();
                else if (t._size != 0)
                	t.root()->_parent = t.end_node();
                ft::swap(this->_compare, t._compare);
            }

            size_type count(const value_type& val) const { return find(val) != this->end(); }

            iterator find(const value_type& val)
            {
                node_ptr node = this->root();

                while(node != NULL)
                {
                    if (this->_compare(node->_value, val))
                        node = node->_right;
                    else if (this->_compare(val, node->_value))
                        node = node->_left;
                    else
                        return iterator(node);
                }
                return this->end();
            }

            const_iterator find(const value_type& val) const
            {
                const_node_ptr node = this->root();
                
                while (node != NULL)
                {
                    if (this->_compare(node->_value, val))
                        node = node->_right;
                    else if (this->_compare(val, node->_value))
                        node = node->_left;
                    else
                        return const_iterator(node);
                }
                return this->end();
            }

            void clear()
            {
                if (root() != NULL)
                {
                    this->destroy(this->root());
                    this->root() = NULL;
                    this->_begin = this->end_node();
                }
            }

            iterator lower_bound(const value_type& val)
            {
                node_ptr node = this->root();
                node_ptr pos = this->end_node();

                while (node != NULL)
                {
                    // node->_value <= val : ture
                    if (!this->_compare(node->_value, val))
                    {
                        pos = node;
                        node = node->_left;
                    }
                    else
                        node = node->_right;
                }
                return iterator(pos);
            }

            const_iterator lower_bound(const value_type& val) const
            {
                const_node_ptr node = this->root();
                const_node_ptr pos = this->end_node();

                while (node != NULL)
                {
                    if (!this->_compare(node->_value, val))
                    {
                        pos = node;
                        node = node->_left;
                    }
                    else 
                        node = node->_right;
                }
                return const_iterator(pos);
            }

            iterator upper_bound(const value_type& val)
            {
                node_ptr node = this->root();
                node_ptr pos = this->end_node();

                while (node != NULL)
                {
                    // val < node->_value : true
                    if (this->_compare(val, node->_value))
                    {
                        pos = node;
                        node = node->_left;
                    }
                    else
                        node = node->_right;
                }
                return iterator(pos);
            }

            const_iterator upper_bound(const value_type& val) const
            {
                const_node_ptr node = this->root();
                const_node_ptr pos = this->end_node();

                while (node != NULL)
                {
                    if (this->_compare(val, node->_value))
                    {
                        pos = node;
                        node = node->_left;
                    }
                    else 
                        node = node->_right;
                }
                return const_iterator(pos);
            }

            ft::pair<iterator,iterator> equal_range( const value_type& val )
            {
                return ft::make_pair(this->lower_bound(val), this->upper_bound(val));
            }
            ft::pair<const_iterator,const_iterator> equal_range( const value_type& val ) const
            {
                return ft::make_pair(this->lower_bound(val), this->upper_bound(val));
            }
            value_compare value_comp() const { return this->_compare; }
            allocator_type get_allocator() const { return this->_value_alloc; }
    
        private:
            node_ptr& root() { return this->_parent._left; }
            const_node_ptr& root() const { return const_cast<const_node_ptr&>(this->_parent._left); }
            node_ptr end_node() { return &(this->_parent);}
            const_node_ptr end_node() const { return const_cast<const_node_ptr>(&(this->_parent)); }

            node_ptr insert(node_ptr node, node_ptr new_node, iterator& pos)
            {
                if (node == NULL)
                {
                    pos = new_node;
                    return new_node;
                }
                if (this->_compare(new_node->_value, node->_value))
                {
                    node->_left = this->insert(node->_left, new_node, pos);
                    node->_left->_parent = node;
                }
                else if (this->_compare(node->_value, new_node->_value))
                {
                    node->_right = this->insert(node->_right, new_node, pos);
                    node->_right->_parent = node;
                }
                else
                    pos = node;
                return node;
            }

            node_ptr make_node(const value_type& val)
            {
                node_ptr new_node = _node_alloc.allocate(1);
                _value_alloc.construct(&new_node->_value, val);
                new_node->_color = red;
                new_node->_parent = NULL;
                new_node->_left = NULL;
                new_node->_right = NULL;
                if (this->empty() || this->_compare(val, this->_begin->_value))
                    this->_begin = new_node;
                ++_size;
                return new_node;
            }

            node_ptr copy(const_node_ptr node)
            {
                if (node == NULL)
                    return NULL;
                node_ptr new_node = make_node(node->_value);
                new_node->_left = this->copy(node->_left);
                if (new_node->_left != NULL)
                    new_node->_left->_parent = new_node;
                new_node->_right = this->copy(node->_right);
                if (new_node->_right != NULL)
                    new_node->_right->_parent = new_node;
                return new_node;
            }

            void destroy_node(node_ptr node)
            {
                this->_value_alloc.destroy(&node->_value);
                this->_node_alloc.deallocate(node, 1);
                this->_size--;
            }

            void destroy(node_ptr node)
            {
                if (node == NULL)
                    return ;
                destroy(node->_left);
                destroy(node->_right);
                destroy_node(node);
            }

            node_ptr get_sibling(node_ptr node) const
            {
                if (tree_is_left_child<value_type>(node))
                    return node->_parent->_right;
                else
                    return node->_parent->_left;
            }

            color get_node_color(node_ptr node)
            {
                if (node == NULL)
                    return (black);
                else
                    return (node->_color);
            }

            void rotate_left(node_ptr node)
            {
                node_ptr right_node = node->_right;
                node->_right = right_node->_left;
                if (node->_right != NULL)
                    node->_right->_parent = node;
                right_node->_parent = node->_parent;
                if (tree_is_left_child<value_type>(node))
                    node->_parent->_left = right_node;
                else
                    node->_parent->_right = right_node;
                right_node->_left = node;
                node->_parent = right_node;
            }

            void rotate_right(node_ptr node)
            {
                node_ptr left_node = node->_left;
                node->_left = left_node->_right;
                if (node->_left != NULL)
                    node->_left->_parent = node;
                left_node->_parent = node->_parent;
                if (tree_is_left_child<value_type>(node))
                    node->_parent->_left = left_node;
                else
                    node->_parent->_right = left_node;
                left_node->_right = node;
                node->_parent = left_node;
            }

            void insert_sort(node_ptr node)
            {
                while (node != this->root() && get_node_color(node->_parent) == red)
                {
                    node_ptr uncle = this->get_sibling(node->_parent);
                    if (this->get_node_color(uncle) == red)
                    {
                        uncle->change_color();
                        node = node->_parent;
                        node->change_color();
                        node = node->_parent;
                        node->change_color();
                    }
                    else if (tree_is_left_child<value_type>(node->_parent))
                    {
                        if (!tree_is_left_child<value_type>(node))
                        {
                            node = node->_parent;
                            this->rotate_left(node);
                        }
                        node = node->_parent;
                        node->change_color();
                        node = node->_parent;
                        node->change_color();
                        this->rotate_right(node);
                        break ;
                    }
                    else
                    {
                        if (tree_is_left_child<value_type>(node))
                        {
                            node = node->_parent;
                            this->rotate_right(node);
                        }
                        node = node->_parent;
                        node->change_color();
                        node = node->_parent;
                        node->change_color();
                        this->rotate_left(node);
                        break ;
                    }
                }
            }

            node_ptr replace_node(node_ptr node) const
            {
                if (node->_left == NULL || node->_right == NULL) //node의 자식이 0개 또는 1개일때
                    return node;
                else  
                    return tree_min<value_type>(node->_right);     //node의 자식이 2개일 때
            }

            void erase(node_ptr root, node_ptr node)
            {
                node_ptr rep_node = replace_node(node);
                node_ptr rep_child = rep_node->_left == NULL ? rep_node->_right : rep_node->_left;   //rep_node의 자식(자식은 0개 혹은 1개일 수 밖에 없기 떄문)
                node_ptr sibling = NULL;

                if (rep_child != NULL)                          //rep_node의 자리를 대체해야 하기 때문에 rep_child는 rep_node의 부모를 가리키게 한다. (자식이 없을 경우 x)
                    rep_child->_parent = rep_node->_parent;
                if (tree_is_left_child<value_type>(rep_node))   //rep_node가 parent의 왼쪽일때
                {
                    rep_node->_parent->_left = rep_child;     //rep_node의 부모도 rep_child를 가리키게 한다
                    if (rep_node == root)                       //rep_node가 root일 떄 예외처리
                        root = rep_child;
                    else
                        sibling = rep_node->_parent->_right;
                }
                else                                            //rep_node가 parent의 오른쪽일때
                {
                    rep_node->_parent->_right = rep_child;
                    sibling = rep_node->_parent->_left;
                }
                color rep_color = rep_node->_color;
                if (rep_node != node)                           //node의 자식이 2개일때 (replace_node()함수의 else문 일때만) rep_node의 요소 저장
                {
                    rep_node->_parent = node->_parent;
                    if (tree_is_left_child<value_type>(node))   //node->parent에서 rep_node로 연결
                        rep_node->_parent->_left = rep_node;
                    else
                        rep_node->_parent->_right = rep_node;
                    rep_node->_left = node->_left;            //node의 자식들과 rep_node를 연결한다.
                    rep_node->_left->_parent = rep_node;
                    rep_node->_right = node->_right;
                    if (rep_node->_right != NULL)
                        rep_node->_right->_parent = rep_node;
                    rep_node->_color = node->_color;          //node에 맞게 rep_node 색 변경
                    if (node == root)
                        root = rep_node;
                }
                if (rep_color == black && root != NULL) //black + root, red + root, red + non-root 모두 해당되지 않음 (규칙 5에 어긋나지 않음)
                {
                    if (rep_child != NULL)          //자식을 black으로 바꿔서 black level 유지. (규칙 5)
                        rep_child->_color = black;
                    else
                        erase_sort(root, rep_child, sibling);  //자식이 없을 때는 추가 조치
                }
            }

            void erase_sort(node_ptr root, node_ptr node, node_ptr sibling)
            {
                while (true)
                {
                    if (!tree_is_left_child<value_type>(sibling))
                    {
                        if (get_node_color(sibling) == red)
                        {
                            sibling->change_color();
                            sibling->_parent->change_color();
                            rotate_left(sibling->_parent);
                            if (root == sibling->_left)
                                root = sibling;
                            sibling = sibling->_left->_right;
                        }
                        if (get_node_color(sibling->_left) == black && get_node_color(sibling->_right) == black)
                        {
                            sibling->change_color();
                            node = sibling->_parent;
                            if (node == root || get_node_color(node) == red)
                            {
                                node->_color = black;
                                break;
                            }
                            sibling = get_sibling(node);
                        }
                        else
                        {
                            if (get_node_color(sibling->_right) == black)
                            {
                                sibling->_left->change_color();
                                sibling->change_color();
                                rotate_right(sibling);
                                sibling = sibling->_parent;
                            }
                            sibling->_color = sibling->_parent->_color;
                            sibling->_parent->_color = black;
                            sibling->_right->_color = black;
                            rotate_left(sibling->_parent);
                            break;
                        }
                    }
                    else
                    {
                        if (get_node_color(sibling) == red)
                        {
                            sibling->change_color();
                            sibling->_parent->change_color();
                            rotate_right(sibling->_parent);
                            if (root == sibling->_right)
                                root = sibling;
                            sibling = sibling->_right->_left;
                        }
                        if (get_node_color(sibling->_left) == black && get_node_color(sibling->_right) == black)
                        {
                            sibling->change_color();
                            node = sibling->_parent;
                            if (node == root || get_node_color(node) == red)
                            {
                                node->_color = black;
                                break;
                            }
                            sibling = get_sibling(node);
                        }
                        else
                        {
                            if (get_node_color(sibling->_left) == black)
                            {
                                sibling->_right->change_color();
                                sibling->change_color();
                                rotate_left(sibling);
                                sibling = sibling->_parent;
                            }
                            sibling->_color = sibling->_parent->_color;
                            sibling->_parent->_color = black;
                            sibling->_left->_color = black;
                            rotate_right(sibling->_parent);
                            break;
                        }
                    }
                }
            }
    };
    template<typename T, typename Compare, typename Alloc>
    void swap(rb_tree<T, Compare, Alloc>& first, rb_tree<T, Compare, Alloc>& second) { first.swap(second); }
}

#endif