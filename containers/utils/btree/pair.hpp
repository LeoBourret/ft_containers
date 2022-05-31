#ifndef PAIR_HPP
# define PAIR_HPP

/*
#ifdef FT_DEBUG_TREE
#include <sstream>
#endif
*/


namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1			first_type;
		typedef	T2			second_type;

		pair		(void)											: first(first_type()), second(second_type()) {}
			template <class U, class V>
		pair		(const pair<U,V> & pr)							: first(pr.first), second(pr.second) {}
		pair		(const first_type & a, const second_type & b)	: first(a), second(b) {}

		first_type		first;
		second_type		second;
	};
	/*	template <class T1, class T2>
	struct pair
	{

# ifdef FT_DEBUG_TREE
		std::string to_string()
		{
			std::stringstream ss;
			ss << first << ": " << second;
			return ss.str();
		};
# endif
		public:
		T1			first;
		T2			second;

		pair(void) : first(T1()), second(T2())
		{
		}

		template<class U, class V>
			pair(const pair<U,V> &pr) : first(pr.first), second(pr.second)
		{
		}

		pair(const T1 &a, const T2 &b) : first(a), second(b)
		{
		}
	};*/
	template <class T1, class T2>
  	ft::pair<T1,T2>		make_pair (T1 x, T2 y)
	{
    	return (ft::pair<T1,T2>(x,y));
  	}

	template <class T1, class T2>
	bool operator==(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first < rhs.first ||
				(!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (!(lhs < rhs));
	}

}

#endif
