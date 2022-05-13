#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include "../utils.hpp"

namespace ft
{
	template <typename T, class Compare>
	class	bidirectional_iterator
	{
		private:
			T*		_ptr;
			T*		_management_node;
			Compare _comp;


		public:
			typedef typename T::value_type														value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef T&																			reference;
			typedef T*																			pointer;

			bidirectional_iterator(const Compare& comp = Compare())											: _ptr(u_nullptr), _management_node(u_nullptr), _comp(comp)					{};
			bidirectional_iterator(pointer ptr, pointer management_node , const Compare& comp = Compare())	: _ptr(ptr), _management_node(management_node), _comp(comp)					{};
			bidirectional_iterator(const bidirectional_iterator &src)										: _ptr(src._ptr), _management_node(src._management_node), _comp(src._comp)	{};

			bidirectional_iterator&	operator=(const bidirectional_iterator &rhs)
			{
				if (*this == rhs)
					return (*this);
				_ptr = rhs._ptr;
				_management_node = rhs._management_node;
				_comp = rhs._comp;
				return (*this);
			};
			virtual ~bidirectional_iterator() {};


			bool		operator==(const bidirectional_iterator &it) const	{return (this->_ptr == it->_ptr);};
			bool		operator!=(const bidirectional_iterator &it) const	{return (this->_ptr != it->_ptr);};

			reference	operator*() const									{return (this->_ptr->val);};
			pointer		operator->() const									{return (&this->_ptr->val);};

			pointer	operator++()
			{
				pointer	current;

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
			pointer	operator++(int)
			{
				pointer	tmp(*this);
				operator++();
				return (tmp);
			}
			pointer	operator--()
			{
				pointer	current;

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
			pointer	operator--(int)
			{
				pointer	tmp(*this);
				operator--();
				return (tmp);
			}



	};
}

#endif
