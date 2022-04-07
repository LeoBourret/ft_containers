#pragma once
# include <iterator>

template <class T, class A = std::allocator<T> >
class V
{
	class VectorIterator
	{
		private:
			T*	_ptr;

		public:
			typedef	VectorIterator iterator;
			typedef A allocator_type;
			typedef typename A::value_type value_type;
			typedef typename A::reference reference;
			typedef typename A::pointer pointer;
			typedef typename A::difference_type difference_type;
			typedef typename A::size_type size_type;
			typedef std::random_access_iterator_tag iterator_category;

			VectorIterator(void) : _ptr(NULL) {};
			VectorIterator(const iterator &src) {_ptr = src->_ptr;};
			~VectorIterator() {};

			iterator& operator=(const iterator &rhs)		{_ptr = rhs->_ptr; return *this;};
			iterator& operator++()							{_ptr = _ptr + 1; return *this;};
			iterator operator++(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
			iterator& operator--()							{_ptr = _ptr - 1; return *this;};
			iterator operator--(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
			iterator& operator+=(size_type n)				{_ptr = _ptr + n; return *this;};
			iterator operator+(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;};
			iterator& operator-=(size_type n)				{_ptr = _ptr - n; return *this;};
			iterator operator-(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;};
			difference_type operator-(iterator rhs) const	{return (_ptr - rhs._ptr);};
			friend iterator operator+(size_type n, const iterator& rhs);

			bool operator==(const iterator& rhs) const		{return (*this == rhs ? true : false);};
			bool operator!=(const iterator& rhs) const		{return (*this != rhs ? true :false);};
			bool operator<(const iterator& rhs) const		{return _ptr < rhs._ptr ? true : false;};
			bool operator>(const iterator& rhs) const		{return (_ptr > rhs.ptr ? true : false);};
			bool operator<=(const iterator& rhs) const		{return (_ptr <= rhs.ptr ? true : false);};
			bool operator>=(const iterator& rhs) const		{return  (_ptr >= rhs._ptr ? true : false);};


			reference operator*() const				{return *_ptr;};
			pointer operator->() const				{return _ptr;};
			reference operator[](size_type n) const {return _ptr + n;};

	};
	class ConstVectorIterator
	{
		private:
			T*	_ptr;
		public:
			typedef	ConstVectorIterator iterator;
			typedef std::random_access_iterator_tag iterator_category;
			typedef typename A::difference_type difference_type;
	        typedef typename A::value_type value_type;
			typedef typename A::size_type size_type;
		    typedef typename A::const_reference reference;
	        typedef typename A::const_pointer pointer;
	        typedef std::random_access_iterator_tag iterator_categ;

			ConstVectorIterator(void) : _ptr(NULL) {};
			ConstVectorIterator(const iterator &src) {_ptr = src->_ptr;};
			ConstVectorIterator(const VectorIterator &src) {_ptr = src->_ptr;};
			~ConstVectorIterator() {};

			iterator& operator=(const iterator &rhs)		{_ptr = rhs->_ptr; return *this;};
			iterator& operator++()							{_ptr = _ptr + 1; return *this;};
			iterator operator++(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
			iterator& operator--()							{_ptr = _ptr - 1; return *this;};
			iterator operator--(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
			iterator& operator+=(size_type n)				{_ptr = _ptr + n; return *this;};
			iterator operator+(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;};
			iterator& operator-=(size_type n)				{_ptr = _ptr - n; return *this;};
			iterator operator-(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;};
			difference_type operator-(iterator rhs) const	{return (_ptr - rhs._ptr);};
			friend iterator operator+(size_type n, const iterator& rhs);

			bool operator==(const iterator& rhs) const		{return (*this == rhs ? true : false);};
			bool operator!=(const iterator& rhs) const		{return (*this != rhs ? true :false);};
			bool operator<(const iterator& rhs) const		{return _ptr < rhs._ptr ? true : false;};
			bool operator>(const iterator& rhs) const		{return (_ptr > rhs.ptr ? true : false);};
			bool operator<=(const iterator& rhs) const		{return (_ptr <= rhs.ptr ? true : false);};
			bool operator>=(const iterator& rhs) const		{return  (_ptr >= rhs._ptr ? true : false);};


			reference operator*() const				{return *_ptr;};
			pointer operator->() const				{return _ptr;};
			reference operator[](size_type n) const {return _ptr + n;};

	};

	class ReverseVectorIterator
	{
		private:
			T*	_ptr;

		public:
			typedef	ReverseVectorIterator iterator;
			typedef A allocator_type;
			typedef typename A::value_type value_type;
			typedef typename A::reference reference;
			typedef typename A::pointer pointer;
			typedef typename A::difference_type difference_type;
			typedef typename A::size_type size_type;
			typedef std::random_access_iterator_tag iterator_category;

			ReverseVectorIterator(void) : _ptr(NULL) {};
			ReverseVectorIterator(const iterator &src) {_ptr = src->_ptr;};
			~ReverseVectorIterator() {};

			iterator& operator=(const iterator &rhs)		{_ptr = rhs->_ptr; return *this;};
			iterator& operator++()							{_ptr = _ptr - 1; return *this;};
			iterator operator++(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
			iterator& operator--()							{_ptr = _ptr + 1; return *this;};
			iterator operator--(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
			iterator& operator+=(size_type n)				{_ptr = _ptr - n; return *this;};
			iterator operator+(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;};
			iterator& operator-=(size_type n)				{_ptr = _ptr + n; return *this;};
			iterator operator-(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;};
			difference_type operator-(iterator rhs) const	{return (_ptr + rhs._ptr);};
			friend iterator operator+(size_type n, const iterator& rhs);

			bool operator==(const iterator& rhs) const		{return (*this == rhs ? true : false);};
			bool operator!=(const iterator& rhs) const		{return (*this != rhs ? true :false);};
			bool operator<(const iterator& rhs) const		{return _ptr < rhs._ptr ? true : false;};
			bool operator>(const iterator& rhs) const		{return (_ptr > rhs.ptr ? true : false);};
			bool operator<=(const iterator& rhs) const		{return (_ptr <= rhs.ptr ? true : false);};
			bool operator>=(const iterator& rhs) const		{return  (_ptr >= rhs._ptr ? true : false);};


			reference operator*() const				{return *_ptr;};
			pointer operator->() const				{return _ptr;};
			reference operator[](size_type n) const {return _ptr + n;};

	};
};
