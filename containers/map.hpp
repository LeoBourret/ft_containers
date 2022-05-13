#ifndef MAP_HPP
# define MAP_HPP

# include "utils/btree.hpp"
# include "utils/pair.hpp"
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
		typedef  Key								key_type;
		typedef  T									mapped_type;
		typedef  ft::pair<const key_type,mapped_type>	value_type;
		typedef  Compare							key_compare;
	}
}

#endif
