#ifndef MAP_HPP
# define MAP_HPP

# include "btree.hpp"
# include "bidirectional_iterator.hpp"
# include "pair.hpp"
# include "../utils.hpp"
# include <cstddef>
# include <limits.h>
# include <stdexcept>
# include <memory>

namespace ft
{
		template <class Key>
	struct less : std::binary_function <Key,Key,bool>
	{
		bool operator() (const Key & x, const Key & y) const
		{
				return (x < y);
		}
	};
		template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		typedef  Key									key_type;
		typedef  T										mapped_type;
		typedef  ft::pair<const key_type,mapped_type>	value_type;
		typedef  Compare								key_compare;

		class value_compare
		{
			friend class map<key_type, mapped_type, key_compare, Alloc>;

			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}

			public:
				bool operator() (const value_type& x, const value_type& y) const
				{ return (comp(x.first, y.first)); }
		};

		typedef	Alloc																allocator_type;
		typedef typename allocator_type::reference									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		typedef typename ft::bidirectional_iterator<value_type, key_compare>		iterator;
		typedef typename ft::bidirectional_iterator<const value_type, key_compare>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type				difference_type;
		typedef	size_t																size_type;

		private:
			allocator_type                          _alloc;
			Compare                                 _comp;
			Rb_tree<value_type, Compare>			_rbt;


		explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _rbt()	{}

		template <class InputIterator>
			map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _rbt()
			{
				this->insert(first, last);
			}

			map (const map& x) : _alloc(x._alloc), _comp(x._comp), _rbt()
		{
			this->insert(x.begin(), x.end());
		}

		~map() {this->clear();}


		/*	Iterators functions */
		iterator begin()
		{
			return (iterator(_rbt._management_node->left, _rbt._management_node));
		};

		const_iterator begin() const
		{
			return (const_iterator(_rbt._management_node->left, _rbt._management_node));
		};

		iterator end()
		{
			return (iterator(_rbt._management_node->right, _rbt._management_node));
		};
		const_iterator end() const
		{
			return (const_iterator(_rbt._management_node->right, _rbt._management_node));
		};

		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		};

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		};

		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		};

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		};

		/* Capacity functions */
		bool empty() const
		{
			return (_rbt._management_node->parent == _rbt._management_node);
		};

		size_type size() const
		{
			return (_rbt._management_node->value.first);
		};

		size_type max_size() const
		{
			return (_rbt.max_size());
		};

		/* Elemet access function */
		mapped_type& operator[] (const key_type& k)
		{
			iterator tmp = this->find(k);

			if (tmp == this->end())
				this->insert(ft::make_pair(k, mapped_type()));
			tmp = this->find(k);
			return ((*tmp).second);
		};

		/* Modifiers function */

		pair<iterator,bool> insert (const value_type& val);

		iterator insert (iterator position, const value_type& val);

		template <class InputIterator>
			void insert (InputIterator first, InputIterator last);

	};
}

#endif
