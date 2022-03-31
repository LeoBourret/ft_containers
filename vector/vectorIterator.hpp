#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include <iterator>

template <typename T>
class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
	private:
		T*	_ptr;
	public:
		typedef	VectorIterator iterator;
		typedef std::random_access_iterator_tag iterator_category;

		iterator(void) : _ptr(NULL) {}
		iterator(const iterator &src) {_ptr = src->_ptr;}
		~iterator() {}

		iterator& operator=(const iterator &rhs)		{_ptr = rhs->_ptr; return *this;}
		iterator& operator++()							{_ptr = _ptr + 1; return *this;}
		iterator operator++(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr + 1; return tmp;}
		iterator& operator--()							{_ptr = _ptr - 1; return *this;}
		iterator operator--(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr - 1; return tmp;}
		iterator& operator+=(size_type n)				{_ptr = _ptr + n; return *this;}
		iterator operator+(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;}
		iterator& operator-=(size_type n)				{_ptr = _ptr - n; return *this;}
		iterator operator-(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;}
		difference_type operator-(iterator rhs) const	{return (_ptr - rhs._ptr);}
		friend iterator operator+(size_type n, const iterator& rhs)

		bool operator==(const iterator& rhs) const		{return (*this == rhs ? true : false);}
		bool operator!=(const iterator& rhs) const		{return (*this != rhs ? true :false);}
		bool operator<(const iterator& rhs) const		{return _ptr < rhs._ptr ? true : false;}
		bool operator>(const iterator& rhs) const		{return (_ptr > rhs.ptr ? true : false);}
		bool operator<=(const iterator& rhs) const		{return (_ptr <= rhs.ptr ? true : false);}
		bool operator>=(const iterator& rhs) const		{return  (_ptr >= rhs._ptr ? true : false);}


		reference operator*() const				{return *_ptr;}
		pointer operator->() const				{return _ptr;}
		reference operator[](size_type n) const {return _ptr + n;};

};

template <typename T>
class ConstVectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
	private:
		T*	_ptr;
	public:
		typedef	ConstVectorIterator iterator;
		typedef std::random_access_iterator_tag iterator_category;

		iterator(void) : _ptr(NULL) {}
		iterator(const iterator &src) {_ptr = src->_ptr;}
		iterator(const VectorIterator &src) {_ptr = src->_ptr;}
		~iterator() {}

		iterator& operator=(const iterator &rhs)		{_ptr = rhs->_ptr; return *this;}
		iterator& operator++()							{_ptr = _ptr + 1; return *this;}
		iterator operator++(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr + 1; return tmp;}
		iterator& operator--()							{_ptr = _ptr - 1; return *this;}
		iterator operator--(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr - 1; return tmp;}
		iterator& operator+=(size_type n)				{_ptr = _ptr + n; return *this;}
		iterator operator+(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;}
		iterator& operator-=(size_type n)				{_ptr = _ptr - n; return *this;}
		iterator operator-(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;}
		difference_type operator-(iterator rhs) const	{return (_ptr - rhs._ptr);}
		friend iterator operator+(size_type n, const iterator& rhs)

		bool operator==(const iterator& rhs) const		{return (*this == rhs ? true : false);}
		bool operator!=(const iterator& rhs) const		{return (*this != rhs ? true :false);}
		bool operator<(const iterator& rhs) const		{return _ptr < rhs._ptr ? true : false;}
		bool operator>(const iterator& rhs) const		{return (_ptr > rhs.ptr ? true : false);}
		bool operator<=(const iterator& rhs) const		{return (_ptr <= rhs.ptr ? true : false);}
		bool operator>=(const iterator& rhs) const		{return  (_ptr >= rhs._ptr ? true : false);}


		reference operator*() const				{return *_ptr;}
		pointer operator->() const				{return _ptr;}
		reference operator[](size_type n) const {return _ptr + n;};

};

template <typename T>
class ReverseVectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
	private:
		T*	_ptr;

	public:
		typedef	ReverseVectorIterator iterator;
		typedef std::random_access_iterator_tag iterator_category;

		iterator(void) : _ptr(NULL) {}
		iterator(const iterator &src) {_ptr = src->_ptr;}
		~iterator() {}

		iterator& operator=(const iterator &rhs)		{_ptr = rhs->_ptr; return *this;}
		iterator& operator++()							{_ptr = _ptr - 1; return *this;}
		iterator operator++(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr - 1; return tmp;}
		iterator& operator--()							{_ptr = _ptr + 1; return *this;}
		iterator operator--(int n)						{(void)n; iterator tmp(*this); _ptr = _ptr + 1; return tmp;}
		iterator& operator+=(size_type n)				{_ptr = _ptr - n; return *this;}
		iterator operator+(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;}
		iterator& operator-=(size_type n)				{_ptr = _ptr + n; return *this;}
		iterator operator-(size_type n) const			{iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;}
		difference_type operator-(iterator rhs) const	{return (_ptr + rhs._ptr);}
		friend iterator operator+(size_type n, const iterator& rhs)

			bool operator==(const iterator& rhs) const		{return (*this == rhs ? true : false);}
		bool operator!=(const iterator& rhs) const		{return (*this != rhs ? true :false);}
		bool operator<(const iterator& rhs) const		{return _ptr < rhs._ptr ? true : false;}
		bool operator>(const iterator& rhs) const		{return (_ptr > rhs.ptr ? true : false);}
		bool operator<=(const iterator& rhs) const		{return (_ptr <= rhs.ptr ? true : false);}
		bool operator>=(const iterator& rhs) const		{return  (_ptr >= rhs._ptr ? true : false);}


		reference operator*() const				{return *_ptr;}
		pointer operator->() const				{return _ptr;}
		reference operator[](size_type n) const {return _ptr + n;};

};
#endif
