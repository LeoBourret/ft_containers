#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include "../utils.hpp"
//#include "binary_tree_node1.hh"
#include "pair.hpp"
#include "btree.hpp"


//using namespace ft;

namespace ft
{
	template <class Key, class T, class Compare = std::less<T> >
		class	bidirectional_iterator
		{
			public:
				typedef ft::Node<Key, T>													Node;
				typedef	ft::pair<Key, T>	value_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
				typedef value_type*																	pointer;
				typedef value_type&																	reference;

			private:
				Node*	_ptr;
				Compare		_comp;

			public:
				bidirectional_iterator(const Compare& comp = Compare())					: _ptr(u_nullptr), _comp(comp)		{};
				bidirectional_iterator(Node* ptr, const Compare& comp = Compare())	: _ptr(ptr), _comp(comp)			{};
				bidirectional_iterator(const bidirectional_iterator &src)				: _ptr(src._ptr), _comp(src._comp)	{};

				bidirectional_iterator&	operator=(const bidirectional_iterator &rhs)
				{
					if (*this == rhs)
						return (*this);
					_ptr = rhs._ptr;
					_comp = rhs._comp;
					return (*this);
				};
				virtual ~bidirectional_iterator() {};


				bool		operator==(const bidirectional_iterator &it) const	{return (this->_ptr == it._ptr);};
				bool		operator!=(const bidirectional_iterator &it) const	{return (this->_ptr != it._ptr);};

				value_type&	operator*() const									{return (this->_ptr->val);};
				value_type*	operator->() const									{return &operator*();};

				bidirectional_iterator & operator++()
				{
					value_type	*current;

					current = _ptr;
					if (current->right)
					{
						current = current->right;
						while (current->left)
							current = current->left;
					}
					else
					{
						while (!current->isLeftChild)
							current = current->parent;
						current = current->parent;
					}
					_ptr = current;
					return (*this);
				}
				bidirectional_iterator	operator++(int)
				{
					value_type*	tmp(*this);
					operator++();
					return (tmp);
				}
				bidirectional_iterator &	operator--()
				{
					value_type*	current;

					current = _ptr;
					if (current->left)
					{
						current = current->left;
						while (current->right)
							current = current->right;
					}
					else
					{
						while (current->isLeftChild)
							current = current->parent;
						current = current->parent;
					}
					_ptr = current;
					return (*this);
				}
				bidirectional_iterator	operator--(int)
				{
					value_type*	tmp(*this);
					operator--();
					return (tmp);
				}
				operator bidirectional_iterator<Key const, T const>() const {
					return bidirectional_iterator<Key const, T const>(_ptr);
					}
		};
}

#endif
