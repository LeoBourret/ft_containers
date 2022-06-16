#ifndef SET_HPP
# define SET_HPP

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
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
		class set {

			public:
				typedef T														key_type;
				typedef T														value_type;
				typedef Compare													key_compare;
				typedef Compare													value_compare;
				typedef Alloc													allocator_type;
				typedef typename Alloc::reference								reference;
				typedef typename Alloc::const_reference							const_reference;
				typedef typename Alloc::pointer									pointer;
				typedef typename Alloc::const_pointer							const_pointer;
				typedef typename ft::const_bidirectional_iterator<value_type>	iterator;
				typedef typename ft::const_bidirectional_iterator<value_type>	const_iterator;
				typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
				typedef typename Alloc::difference_type							difference_type;
				typedef typename Alloc::size_type								size_type;
				typedef ft::Node<value_type>									Node;
				typedef RedBlackTree<value_type, key_compare>		tree_type;

			protected:
				tree_type		_rbt;
				allocator_type	_alloc;
				value_compare	_comp;

			public:
				explicit set (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
					: _rbt(), _alloc(alloc), _comp(comp)
				{
				};

				template <class InputIterator>
					set (InputIterator first, InputIterator last,
							const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type())
					: _rbt(), _alloc(alloc), _comp(comp)
					{
						insert(first, last);
					};

				set (const set& x)
					: _rbt(x._rbt), _alloc(x._alloc), _comp(x._comp)
				{}

				set &	operator= (set const & rhs)
				{
					this->_rbt = rhs._rbt;
					return *this;
				}

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
					return (iterator(_rbt.getManagement(), _rbt.getManagement(), _rbt.getLeaf()));
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
					std::allocator<Node>	tmp;
					return tmp.max_size();
				};


				/* Modifiers function */

				ft::pair<iterator,bool> insert (const value_type& val)
				{

					if (count(val))
					{
						iterator it = find(val);
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
					_rbt.deleteNode(position.getNode());
				};


				size_type erase (const value_type& k)
				{
					iterator it = find(k);

					if (it == end())
						return (0);
					_rbt.deleteNode(it.getNode());
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

				void	swap(set &x)
				{
					Node*		management_tmp = _rbt.getManagement();
					Node*		leaf_temp = _rbt.getLeaf();
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
					return (_comp);
				};

				value_compare value_comp() const
				{
					return (_comp);
				};

				iterator find (const key_type& k) const
				{
					iterator it;

					it = iterator(_rbt.searchTree(k), _rbt.getManagement(), _rbt.getLeaf());
					return (it.getNode() != _rbt.getLeaf() ? it : this->end());
				};

				size_type count(const key_type &k) const
				{
					return (find(k) != end());
				};

				iterator	lower_bound (key_type const & k) const
				{
					iterator it = begin();

					for (iterator ite = end(); it != ite; it++) {
						if (*it == k || !_comp(*it, k))
							return it;
					}
					return end();
				}


				iterator	upper_bound (key_type const & k) const
				{
					iterator it = begin();

					for (iterator ite = end(); it != ite; it++)
					{
						if (*it != k && !_comp(*it, k))
							return it;
					}
					return end();
				}


				ft::pair<iterator, iterator> equal_range(const key_type &k) const
				{
					return (ft::make_pair(lower_bound(k), upper_bound(k)));
				};

				allocator_type	get_allocator() const
				{
					return (_alloc);
				}

		};

	template <class T, class Compare, class Alloc>
		bool operator== (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return equal(lhs.begin(), lhs.end(), rhs.begin());
		}

	template <class T, class Compare, class Alloc>
		bool operator!= (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs)
		{
			return !(lhs == rhs);
		}

	template <class T, class Compare, class Alloc>
		bool operator< (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs)
		{
			return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template <class T, class Compare, class Alloc>
		bool operator> (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs)
		{
			return rhs < lhs;
		}

	template <class T, class Compare, class Alloc>
		bool operator<= (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs)
		{
			return !(rhs < lhs);
		}

	template <class T, class Compare, class Alloc>
		bool operator>= (set<T, Compare, Alloc> const & lhs,
				set<T, Compare, Alloc> const & rhs)
		{
			return !(lhs < rhs);
		}

	template <class T, class Compare, class Alloc>
		void swap (set<T, Compare, Alloc> const & x,
				set<T, Compare, Alloc> const & y)
		{
			x.swap(y);
		}
}

#endif
