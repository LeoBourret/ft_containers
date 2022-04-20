#ifndef MAP_HPP
# define MAP_HPP

# include "btree.hpp"
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
		template < class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key,T> > >
	class map
	{
		typedef typename Key								mapped_type;
		typedef typename T									key_type;
		typedef typename pair<const key_type,mapped_type>	value_type;
		typedef typename Compare							key_compare;
		typedef typename Alloc								value_compare;
	}
}

#endif
