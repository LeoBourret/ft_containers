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

		template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
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
		typedef typename ft::bidirectional_iterator<Key, T>							iterator;
		typedef typename ft::bidirectional_iterator<const Key, const T>						const_iterator;
		typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type				difference_type;
		typedef	size_t																size_type;

		private:
			allocator_type								_alloc;
			Compare										_comp;
			Rb_tree<value_type, key_type, mapped_type>	_rbt;

		public:

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
			return (iterator(_rbt.getManagementNode()->left));
		};

		const_iterator begin() const
		{
			return (const_iterator(_rbt.getManagementNode()->left));
		};

		iterator end()
		{
			return (iterator(_rbt.getManagementNode()->right));
		};
		const_iterator end() const
		{
			return (const_iterator(_rbt.getManagementNode()->right));
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
			return (_rbt.getManagementNode()->parent == _rbt.getManagementNode());
		};

		size_type size() const
		{
			return (_rbt.getManagementNode()->value.first);
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

		ft::pair<iterator,bool> insert (const value_type& val)
		{
			iterator it;

			if (count(val.first))
			{
				it = find(val.first);
				return ft::make_pair(it, false);
			}
			it = iterator(_rbt.add(val));
			return (ft::make_pair(it, true));
		};

		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			return (this->insert(val).first);
		};

		template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
					this->insert(*first++);
			};

		void erase (iterator position)
		{
			_rbt.deleteNode(*position._ptr._pair.first);
		};


		size_type erase (const key_type& k)
		{
			return (_rbt.deleteNode(k));
		};

		void erase (iterator first, iterator last)
		{
			for (iterator it = ++first; it != last; it++)
				this->erase(it);
		};

		void	swap(map &x)
		{
			ft::swap(_alloc, x._alloc);
			ft::swap(_comp, x._comp);
			ft::swap(_rbt, x._rbt);
		};

		void	clear(void)
		{
			iterator first = this->begin();

			for (iterator it = ++first; it != this->end(); it++)
				this->erase(it);
		};

		key_compare	key_comp() const
		{
			return (key_compare());
		};

		value_compare value_comp() const
		{
			return (value_compare(_comp));
		};

		iterator find (const key_type& k)
		{
			iterator it;

			it = iterator(_rbt.findNode(k));
			return (it != NULL ? it : this->end());
		};

		const_iterator find (const key_type& k) const
		{
			const_iterator it(_rbt.findNode(k));
			if (it == NULL)
				return (this->end());
			return (it);
		};

		size_type count(const key_type &k) const
		{
			if (this->find(k) == this->end())
				return (0);
			return (1);
		};

		iterator	lower_bound(const key_type &k)
		{
			iterator it;

			it = begin();
			while (_comp(it->first, k) == false && it != end())
				it++;
			return (it);
		};

		const_iterator	lower_bound(const key_type &k) const
		{
			const_iterator it;

			it = begin();
			while (_comp(it->first, k) == false && it != end())
				it++;
			return (it);
		};

		iterator	upper_bound(const key_type &k)
		{
			iterator it;

			it = begin();
			while (_compd(k, it->first) == false && it != end())
				it++;
			return it;
		};

		const_iterator	upper_bound(const key_type &k) const
		{
			const_iterator it;

			it = begin();
			while (_compd(k, it->first) == false && it != end())
				it++;
			return it;
		};

		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		};


		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		};

		allocator_type	get_allocator() const
		{
			return (allocator_type());
		}
	};
}

#endif
