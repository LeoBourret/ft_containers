#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "utils.hpp"
namespace ft
{
	template <typename T>
	class	random_access_iterator
	{
		private:
			T*	_ptr;

		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef T&										reference;
			typedef T*										pointer;

			random_access_iterator(void) : _ptr(NULL)					{};
			random_access_iterator(pointer ptr)							{_ptr = ptr;};
			random_access_iterator(const random_access_iterator &src)	{_ptr = src._ptr;};
			~random_access_iterator()									{};

			random_access_iterator& operator=(const random_access_iterator &rhs)	{_ptr = rhs._ptr; return *this;};
			random_access_iterator& operator++()									{_ptr = _ptr + 1; return *this;};
			random_access_iterator operator++(int)									{random_access_iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
			random_access_iterator& operator--()									{_ptr = _ptr - 1; return *this;};
			random_access_iterator operator--(int)									{random_access_iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
			random_access_iterator& operator+=(difference_type n)							{_ptr = _ptr + n; return *this;};
			random_access_iterator operator +(difference_type n) const					{ return (random_access_iterator(_ptr + n)); }; // a + n
			random_access_iterator& operator-=(difference_type n)							{_ptr = _ptr - n; return *this;};
			random_access_iterator operator-(difference_type n) const						{return (random_access_iterator(_ptr - n));};
			difference_type operator-(random_access_iterator rhs) const				{return (_ptr - rhs._ptr);};

			friend random_access_iterator operator+(difference_type n, const random_access_iterator& rhs);

			difference_type operator +(random_access_iterator b) { return (_ptr + b._ptr); };

			bool operator==(const random_access_iterator& rhs) const	{return (_ptr == rhs._ptr);};
			bool operator!=(const random_access_iterator& rhs) const	{return !(operator==(rhs));};
			bool operator<(const random_access_iterator& rhs) const		{return (_ptr < rhs._ptr);};
			bool operator>(const random_access_iterator& rhs) const		{return (_ptr > rhs.ptr);};
			bool operator<=(const random_access_iterator& rhs) const	{return (operator==(rhs) || operator<(rhs));};
			bool operator>=(const random_access_iterator& rhs) const	{return  (operator==(rhs) || operator>(rhs));};


			reference operator*() const						{return *_ptr;};
			pointer	operator&()	const						{return _ptr;};
			pointer operator->() const						{return _ptr;};
			reference operator[](difference_type n) const	{return *(_ptr + n);};

	};
	template<typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator+(typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai)
	{
		return (&(*rai) + n);
	}
	template<typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator-(typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai)
	{
		return (n - &(*rai));
	}
};

#endif
