#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include<iterator>

namespace ft
{
	class	iterator
	{
		private:
			T*	_ptr;

		public:
			typedef A										allocator_type;
			typedef typename A::value_type					value_type;
			typedef typename A::reference					reference;
			typedef typename A::difference_type				difference_type;
			typedef typename A::size_type					size_type;
			typedef std::random_access_iterator_tag			iterator_category;

			iterator(void) : _ptr(NULL)						{};
			iterator(pointer ptr)							{_ptr = ptr;};
			iterator(const iterator &src)					{_ptr = src._ptr;};
			~iterator()										{};

			iterator& operator=(const iterator &rhs)		{_ptr = rhs._ptr; return *this;};
			iterator& operator++()							{_ptr = _ptr + 1; return *this;};
			iterator operator++(int)						{iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
			iterator& operator--()							{_ptr = _ptr - 1; return *this;};
			iterator operator--(int)						{iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
			iterator& operator+=(size_type n)				{_ptr = _ptr + n; return *this;};
			iterator operator +(size_type n) const			{ return (iterator(_ptr + n)); }; // a + n
			iterator& operator-=(size_type n)				{_ptr = _ptr - n; return *this;};
			iterator operator-(size_type n) const			{return (iterator(_ptr - n));};
			difference_type operator-(iterator rhs) const	{return (_ptr - rhs._ptr);};
			friend iterator operator+(size_type n, const iterator& rhs);

			difference_type operator +(iterator b) { return (_ptr + b._ptr); };

			bool operator==(const iterator& rhs) const		{return (_ptr == rhs._ptr);};
			bool operator!=(const iterator& rhs) const		{return !(operator==(rhs));};
			bool operator<(const iterator& rhs) const		{return (_ptr < rhs._ptr);};
			bool operator>(const iterator& rhs) const		{return (_ptr > rhs.ptr);};
			bool operator<=(const iterator& rhs) const		{return (operator==(rhs) || operator<(rhs));};
			bool operator>=(const iterator& rhs) const		{return  (operator==(rhs) || operator>(rhs));};


			reference operator*() const						{return *_ptr;};
			pointer	operator&()	const						{return _ptr;};
			pointer operator->() const						{return _ptr;};
			reference operator[](difference_type n) const	{return *(_ptr + n);};

	};
};

#endif
