#ifndef MAP_HPP
# define MAP_HPP
/*
# include "utils/rbtree.hpp"
# include "utils/pair.hpp"
# include "utils//utils.hpp"
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"*/
# include "rbtree.hpp"
# include "pair.hpp"
# include "utils.hpp"
# include "equal.hpp"
# include "lexicographical_compare.hpp"

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
		typedef typename ft::bidirectional_iterator<value_type>						iterator;
		typedef typename ft::const_bidirectional_iterator<value_type>				const_iterator;
		typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type				difference_type;
		typedef	typename Alloc::size_type											size_type;

		private:
			allocator_type														_alloc;
			Compare																_comp;
			RedBlackTree<value_type, const key_type, mapped_type, key_compare>	_rbt;

		public:

		explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _rbt(comp)	{}

		template <class InputIterator>
			map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _rbt(comp)
			{
				this->insert(first, last);
			}

		map (const map& x) : _alloc(x._alloc), _comp(x._comp), _rbt(x._rbt)
		{
		}

		map &	operator= (map const & rhs)
		{
			this->_rbt = rhs._rbt;
			return *this;
		}


		~map() {}


		/*	Iterators functions */
		iterator begin()
		{
			return (iterator(_rbt.findMin(), _rbt.getManagement(), _rbt.getLeaf()));
		};

		const_iterator begin() const
		{
			return (const_iterator(_rbt.findMin(), _rbt.getManagement(), _rbt.getLeaf()));
		};

		iterator end()
		{
			return (_rbt.end());
		};
		const_iterator end() const
		{
			return (const_iterator(_rbt.getManagement(), _rbt.getManagement(), _rbt.getLeaf()));
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
			return (!_rbt.getSize() ? true : false);
		};

		size_type size() const
		{
			return (_rbt.getSize());
		};

		size_type max_size() const
		{
			std::allocator<Node<value_type> >	tmp;
			return tmp.max_size();
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

			if (count(val.first))
			{
				iterator it = find(val.first);
				return ft::make_pair(it, false);
			}
			iterator it(_rbt.insert(val), _rbt.getManagement(), _rbt.getLeaf());
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
			_rbt.deleteNode(position->first);
		};


		size_type erase (const key_type& k)
		{
			iterator it = find(k);

			if (it == end())
				return (0);
			_rbt.deleteNode(k);
			return (1);
		};

		void erase (iterator first, iterator last)
		{
			iterator tmp;

			while (first != last)
			{
				tmp = first;
				first++;
				erase(tmp);
			}
		};

		void	swap(map &x)
		{
			Node<value_type> *	management_tmp = _rbt.getManagement();
			Node<value_type> *	leaf_temp = _rbt.getLeaf();
			size_type	size_temp = _rbt.getSize();

			_rbt.setManagement(x._rbt.getManagement());
			_rbt.setLeaf(x._rbt.getLeaf());
			_rbt.setSize(x._rbt.getSize());

			x._rbt.setManagement(management_tmp);
			x._rbt.setLeaf(leaf_temp);
			x._rbt.setSize(size_temp);
		};

		void	clear(void)
		{
			_rbt.clear();
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

			it = iterator(_rbt.searchTree(k), _rbt.getManagement(), _rbt.getLeaf());
			return (it.getNode() != _rbt.getLeaf() ? it : this->end());
		};

		const_iterator find (const key_type& k) const
		{
			const_iterator it(_rbt.searchTree(k), _rbt.getManagement(), _rbt.getLeaf());
			return (it.getNode() != _rbt.getLeaf() ? it : this->end());
		};

		size_type count(const key_type &k) const
		{
			if (this->find(k) == this->end())
				return (0);
			return (1);
		};

		iterator	lower_bound (key_type const & k)
		{
			iterator it = begin();

			for (iterator ite = end(); it != ite; it++) {
				if (it->first ==k || !_comp(it->first, k))
					return it;
			}
			return end();
		}

		const_iterator	lower_bound (key_type const & k) const
		{
			const_iterator it = begin();

			for (const_iterator ite = end(); it != ite; it++) {
				if (it->first == k || !_comp(it->first, k))
					return it;
			}
			return end();
		}

		iterator	upper_bound (key_type const & k)
		{
			iterator it = begin();

			for (iterator ite = end(); it != ite; it++)
			{
				if (it->first != k && !_comp(it->first, k))
					return it;
			}
			return end();
		}

		const_iterator	upper_bound (key_type const & k) const
		{
			const_iterator it = begin();

			for (const_iterator ite = end(); it != ite; it++)
			{
				if (it->first != k && !_comp(it->first, k))
					return it;
			}
			return end();
		}

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
		template <class Key, class T, class Compare, class Alloc>
			bool operator== (map<Key, T, Compare, Alloc> const & lhs,
					map<Key, T, Compare, Alloc> const & rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator!= (map<Key, T, Compare, Alloc> const & lhs,
					map<Key, T, Compare, Alloc> const & rhs)
			{
				return !(lhs == rhs);
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator< (map<Key, T, Compare, Alloc> const & lhs,
					map<Key, T, Compare, Alloc> const & rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator> (map<Key, T, Compare, Alloc> const & lhs,
					map<Key, T, Compare, Alloc> const & rhs)
			{
				return rhs < lhs;
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator<= (map<Key, T, Compare, Alloc> const & lhs,
					map<Key, T, Compare, Alloc> const & rhs)
			{
				return !(rhs < lhs);
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator>= (map<Key, T, Compare, Alloc> const & lhs,
					map<Key, T, Compare, Alloc> const & rhs)
			{
				return !(lhs < rhs);
			}

}
		namespace std
		{
		template <class Key, class T, class Compare, class Alloc>
			void swap (ft::map<Key, T, Compare, Alloc> & x,
					ft::map<Key, T, Compare, Alloc> & y)
			{
				x.swap(y);
			}
		};


#endif
