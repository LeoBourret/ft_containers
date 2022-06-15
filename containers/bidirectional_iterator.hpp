#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include "../utils.hpp"
#include "rbtree.hpp"
//#include "binary_tree_node1.hh"
#include "pair.hpp"

namespace ft
{
	template <class T>
		class	bidirectional_iterator
		{
			public:
				typedef	T																						value_type;
				typedef Node<T>																					Node;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
				typedef value_type*																				pointer;
				typedef value_type&																				reference;

			private:
				Node*	_ptr;
				Node*	_management_node;
				Node*	_leaf;

			public:
				bidirectional_iterator()									: _ptr(u_nullptr), _management_node(u_nullptr), _leaf(u_nullptr)				{};
				bidirectional_iterator(Node* ptr, Node* mn, Node* leaf)		: _ptr(ptr), _management_node(mn), _leaf(leaf)									{};
				bidirectional_iterator(const bidirectional_iterator &src)	: _ptr(src._ptr), _management_node(src._management_node), _leaf(src._leaf)		{};

				bidirectional_iterator&	operator=(const bidirectional_iterator &rhs)
				{
					if (*this == rhs)
						return (*this);
					_ptr = rhs._ptr;
					return (*this);
				};
				virtual ~bidirectional_iterator() {};


				bool		operator==(const bidirectional_iterator &it) const	{return (this->_ptr == it._ptr);};
				bool		operator==(Node *ptr) const							{return (this->_ptr == ptr);};
				bool		operator!=(const bidirectional_iterator &it) const	{return (this->_ptr != it._ptr);};

				reference	operator*() const									{return (this->_ptr->data);};
				pointer		operator->() const									{return &operator*();};
				bidirectional_iterator & operator++()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}

					if (_ptr->right != _leaf)
					{
						_ptr = _ptr->right;
						while (_ptr->left != _leaf)
							_ptr = _ptr->left;
					}
					else
					{
						while (_ptr == _ptr->parent->right && _ptr != _ptr->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}

				bidirectional_iterator	operator++(int)
				{
					bidirectional_iterator	tmp = *this;
					operator++();
					return (tmp);
				}

				bidirectional_iterator &	operator--()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}

					if (_ptr->left != _leaf)
					{
						_ptr = _ptr->left;
						while (_ptr->right != _leaf)
							_ptr = _ptr->right;
					}
					else
					{
						while (_ptr == _ptr->parent->left && _ptr != _ptr->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}

				Node	*getNode() const
				{
					return (_ptr);
				}

				Node	*getLeaf() const
				{
					return (_leaf);
				}

				Node	*getManagement() const
				{
					return (_management_node);
				}

		};

	template <class T>
		class	const_bidirectional_iterator
		{
			public:
				typedef	T const																					value_type;
				typedef Node<T>																					Node;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
				typedef value_type const*																		pointer;
				typedef value_type	const&																		reference;

			private:
				Node*	_ptr;
				Node*	_management_node;
				Node*	_leaf;

			public:
				const_bidirectional_iterator()											: _ptr(u_nullptr), _management_node(u_nullptr), _leaf(u_nullptr)				{};
				const_bidirectional_iterator(Node* ptr, Node* mn, Node* leaf)			: _ptr(ptr), _management_node(mn), _leaf(leaf)									{};
				const_bidirectional_iterator(const const_bidirectional_iterator &src)	: _ptr(src._ptr), _management_node(src._management_node), _leaf(src._leaf)		{};
				const_bidirectional_iterator(const bidirectional_iterator<T> &src)		: _ptr(src.getNode()), _management_node(src.getManagement()), _leaf(src.getLeaf())	{};

				const_bidirectional_iterator&	operator=(const const_bidirectional_iterator &rhs)
				{
					if (*this == rhs)
						return (*this);
					_ptr = rhs._ptr;
					return (*this);
				};

				virtual ~const_bidirectional_iterator() {};


				bool		operator==(const const_bidirectional_iterator &it) const	{return (this->_ptr == it._ptr);};
				bool		operator==(Node *ptr) const									{return (this->_ptr == ptr);};
				bool		operator==(const bidirectional_iterator<T> &it) const		{return (this->_ptr == it.getNode());};
				bool		operator!=(const const_bidirectional_iterator &it) const	{return (this->_ptr != it._ptr);};

				reference	operator*() const									{return (this->_ptr->data);};
				pointer		operator->() const									{return &operator*();};
				const_bidirectional_iterator & operator++()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}

					if (_ptr->right != _leaf)
					{
						_ptr = _ptr->right;
						while (_ptr->left != _leaf)
							_ptr = _ptr->left;
					}
					else
					{
						while (_ptr == _ptr->parent->right && _ptr != _ptr->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}

				const_bidirectional_iterator	operator++(int)
				{
					const_bidirectional_iterator	tmp = *this;
					operator++();
					return (tmp);
				}

				const_bidirectional_iterator &	operator--()
				{
					if (_ptr == _management_node)
					{
						_ptr = _ptr->right;
						return (*this);
					}

					if (_ptr->left != _leaf)
					{
						_ptr = _ptr->left;
						while (_ptr->right != _leaf)
							_ptr = _ptr->right;
					}
					else
					{
						while (_ptr == _ptr->parent->left && _ptr != _ptr->parent)
							_ptr = _ptr->parent;
						_ptr = _ptr->parent;
					}
					return (*this);
				}

				Node*	getNode() const
				{
					return (_ptr);
				}
		};

}

#endif
