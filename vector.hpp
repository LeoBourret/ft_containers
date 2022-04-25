#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include "type_traits.hpp"
# include "utils.hpp"
# include <iostream>

namespace ft
{
	template<class T, class A = std::allocator<T> >
		class vector
		{
			public:
				typedef	A allocator_type;
				typedef typename A::value_type		value_type;
				typedef typename A::pointer			pointer;
				typedef typename A::reference		reference;
				typedef typename A::const_reference const_reference;
				typedef size_t						size_type;
				typedef	std::ptrdiff_t				difference_type;
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
				class const_iterator
				{
					private:
						T*	_ptr;
					public:
						typedef std::random_access_iterator_tag iterator_category;
						typedef typename A::difference_type difference_type;
						typedef typename A::value_type value_type;
						typedef typename A::size_type size_type;
						typedef typename A::const_reference reference;
						typedef typename A::const_pointer pointer;
						typedef typename A::pointer n_const_pointer;
						typedef std::random_access_iterator_tag iterator_categ;

						const_iterator(void) : _ptr(NULL)						{};
						const_iterator(n_const_pointer ptr)						{_ptr = ptr;};
						const_iterator(const iterator &src)						{*this = src;};
						const_iterator(const const_iterator &src)				{*this = src;};
						~const_iterator() {};

						const_iterator& operator=(const iterator &rhs)			{_ptr = rhs.operator->(); return *this;};
						const_iterator& operator++()							{_ptr = _ptr + 1; return *this;};
						const_iterator operator++(int n)						{(void)n; const_iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
						const_iterator& operator--()							{_ptr = _ptr - 1; return *this;};
						const_iterator operator--(int n)						{(void)n; const_iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
						const_iterator& operator+=(size_type n)					{_ptr = _ptr + n; return *this;};
						const_iterator operator+(size_type n) const				{const_iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;};
						const_iterator& operator-=(size_type n)					{_ptr = _ptr - n; return *this;};
						const_iterator operator-(size_type n) const				{const_iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;};
						difference_type operator-(const_iterator rhs) const		{return (_ptr - rhs._ptr);};
						friend const_iterator operator+(size_type n, const const_iterator& rhs);


						bool operator==(const const_iterator& rhs) const		{return (_ptr == rhs._ptr);};
						bool operator!=(const const_iterator& rhs) const		{return !(operator==(rhs));};
						bool operator<(const const_iterator& rhs) const			{return (_ptr < rhs._ptr);};
						bool operator>(const const_iterator& rhs) const			{return (_ptr > rhs.ptr);};
						bool operator<=(const const_iterator& rhs) const		{return (operator==(rhs) || operator<(rhs));};
						bool operator>=(const const_iterator& rhs) const		{return  (operator==(rhs) || operator>(rhs));};

						reference operator*() const								{return *_ptr;};
						pointer	operator&()	const								{return _ptr;};
						pointer operator->() const								{return _ptr;};
						reference operator[](size_type n) const					{return _ptr + n;};

				};
				class	reverse_iterator
				{
					private:
						T*	_ptr;

					public:
						typedef A													allocator_type;
						typedef typename A::value_type								value_type;
						typedef typename A::reference								reference;
						typedef typename A::difference_type							difference_type;
						typedef typename A::size_type								size_type;
						typedef std::random_access_iterator_tag						iterator_category;

						reverse_iterator(void) : _ptr(NULL)							{};
						reverse_iterator(const reverse_iterator &src)				{_ptr = src->_ptr;};
						~reverse_iterator()											{};

						reverse_iterator& operator=(const reverse_iterator &rhs)	{_ptr = rhs->_ptr; return *this;};
						reverse_iterator& operator++()								{_ptr = _ptr - 1; return *this;};
						reverse_iterator operator++(int)							{reverse_iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
						reverse_iterator& operator--()								{_ptr = _ptr + 1; return *this;};
						reverse_iterator operator--(int)							{reverse_iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
						reverse_iterator& operator+=(size_type n)					{_ptr = _ptr - n; return *this;};
						reverse_iterator operator+(size_type n) const				{reverse_iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;};
						reverse_iterator& operator-=(size_type n)					{_ptr = _ptr + n; return *this;};
						reverse_iterator operator-(size_type n) const				{reverse_iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;};
						difference_type operator-(iterator rhs) const				{return (_ptr + rhs._ptr);};
						friend reverse_iterator operator+(size_type n, const reverse_iterator& rhs);

						bool operator==(const reverse_iterator& rhs) const			{return (*this == rhs ? true : false);};
						bool operator!=(const reverse_iterator& rhs) const			{return (*this != rhs ? true :false);};
						bool operator<(const reverse_iterator& rhs) const			{return (_ptr > rhs._ptr ? true : false);};
						bool operator>(const reverse_iterator& rhs) const			{return (_ptr < rhs.ptr ? true : false);};
						bool operator<=(const reverse_iterator& rhs) const			{return (_ptr >= rhs.ptr ? true : false);};
						bool operator>=(const reverse_iterator& rhs) const			{return  (_ptr <= rhs._ptr ? true : false);};


						reference operator*() const									{return *_ptr;};
						pointer operator->() const									{return _ptr;};
						reference operator[](size_type n) const						{return _ptr - n;};

				};
				class	const_reverse_iterator
				{
					private:
						T*	_ptr;

					public:
						typedef A																allocator_type;
						typedef typename A::value_type											value_type;
						typedef typename A::const_reference										reference;
						typedef typename A::difference_type										difference_type;
						typedef typename A::size_type											size_type;
						typedef std::random_access_iterator_tag									iterator_category;

						const_reverse_iterator(void) : _ptr(NULL)								{};
						const_reverse_iterator(const const_reverse_iterator &src)				{_ptr = src->_ptr;};
						~const_reverse_iterator()												{};

						const_reverse_iterator& operator=(const const_reverse_iterator &rhs)	{_ptr = rhs->_ptr; return *this;};
						const_reverse_iterator& operator++()									{_ptr = _ptr - 1; return *this;};
						const_reverse_iterator operator++(int n)								{(void)n; const_reverse_iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
						const_reverse_iterator& operator--()									{_ptr = _ptr + 1; return *this;};
						const_reverse_iterator operator--(int n)								{(void)n; const_reverse_iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
						const_reverse_iterator& operator+=(size_type n)							{_ptr = _ptr - n; return *this;};
						const_reverse_iterator operator+(size_type n) const						{const_reverse_iterator tmp(*this); tmp._ptr = tmp._ptr - n; return tmp;};
						const_reverse_iterator& operator-=(size_type n)							{_ptr = _ptr + n; return *this;};
						const_reverse_iterator operator-(size_type n) const						{const_reverse_iterator tmp(*this); tmp._ptr = tmp._ptr + n; return tmp;};
						difference_type operator-(iterator rhs) const							{return (_ptr + rhs._ptr);};
						friend const_reverse_iterator operator+(size_type n, const const_reverse_iterator& rhs);

						bool operator==(const const_reverse_iterator& rhs) const				{return (*this == rhs ? true : false);};
						bool operator!=(const const_reverse_iterator& rhs) const				{return (*this != rhs ? true :false);};
						bool operator<(const const_reverse_iterator& rhs) const					{return (_ptr > rhs._ptr ? true : false);};
						bool operator>(const const_reverse_iterator& rhs) const					{return (_ptr < rhs.ptr ? true : false);};
						bool operator<=(const const_reverse_iterator& rhs) const				{return (_ptr >= rhs.ptr ? true : false);};
						bool operator>=(const const_reverse_iterator& rhs) const				{return  (_ptr <= rhs._ptr ? true : false);};


						reference operator*() const												{return *_ptr;};
						pointer operator->() const												{return _ptr;};
						reference operator[](size_type n) const									{return _ptr - n;};

				};
			private:
				value_type		*_vector;
				allocator_type	_alloc;
				size_type		_capacity;
				size_type		_size;

			public:
				explicit vector(const allocator_type& alloc = allocator_type())
					:	_vector(NULL), _alloc(alloc), _capacity(0), _size(0)
				{
				};
				explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
					:  _alloc(alloc), _capacity(n), _size(n)
				{
					_vector = _alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(&_vector[i], val);
				};
				template <class InputIterator>
					vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type(),
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = u_nullptr)
					: _alloc(alloc), _capacity(0), _size(0)
					{
						assign(first, last);
					};
				vector (const vector& x) :  _alloc(x._alloc), _capacity(x._capacity), _size(x._size)
				{
					_vector = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_vector[i] = x._vector[i];
				};
				~vector()
				{
					this->clear();
				//	_alloc.deallocate(_vector, _capacity);
				};
				void	printStatus()
				{
					std::cout << "size == " << _size << std::endl << "capacity == " << _capacity << std::endl;
				}
				/*
				 * ITERATORS
				 */
				iterator	begin()
				{
					return (iterator(&_vector[0]));
				};
				const_iterator	begin() const
				{
					return (const_iterator(&_vector[0]));
				};
				iterator	end()
				{
					return (iterator(&_vector[_size]));
				}
				const_iterator	end() const
				{
					return (const_iterator(&_vector[_size]));
				}
				reverse_iterator rbegin()
				{
					return (ft::vector<T, A>::reverse_iterator(&_vector[_size - 1]));
				};
				const_reverse_iterator rbegin() const
				{
					return (ft::vector<T, A>::const_reverse_iterator(&_vector[_size - 1]));
				};
				reverse_iterator rend()
				{
					return (ft::vector<T, A>::reverse_iterator(&_vector[-1]));
				};
				const_reverse_iterator rend() const
				{
					return (ft::vector<T, A>::const_reverse_iterator(&_vector[-1]));
				};

				/*
				** CAPACITY
				*/

				size_type size() const
				{
					return (_size);
				};
				size_type max_size() const
				{
					return (_alloc.max_size());
				};
				void resize (size_type n, value_type val = value_type())
				{
					//f n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
					if (n < _size)
						while (_size > n)
							pop_back();
					//If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n.
					//If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
					else if (n > _size)
						while (n > _size)
							push_back(val);
					//If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
					else if (n > _capacity)
					{
						reserve(n);
						while (n > _size)
							push_back(val);
					}

				};
				size_type capacity() const
				{
					return (_capacity);
				};
				bool empty() const
				{
					return (_size == 0);
				};
				void reserve (size_type n)
				{
					pointer		tmp;
					size_type	size_save;
					size_type	capacity_save;

					if (n > max_size())
						throw std::length_error("Size set for reserve is greater than max_size.");
					else if (n <= _capacity)
						return ;
					else if (n < _capacity * 2)
					{
						tmp = _alloc.allocate(_capacity * 2);
						_capacity *= 2;
					}
					else
					{
						tmp = _alloc.allocate(n);
						_capacity = n;
					}
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&tmp[i], _vector[i]);
					size_save = _size;
					capacity_save = _capacity;
					clear();
					_size = size_save;
					_capacity = capacity_save;
					_vector = tmp;
				};

				/*
				 * ELEMENT ACCESS
				 */
				reference operator[] (size_type n)
				{
					if (n < 0 || n > (_size - 1))
						throw std::out_of_range("Requested element is out of range.");
					return (_vector[n]);
				};
				const_reference operator[] (size_type n) const
				{
					if (n < 0 || n > (_size - 1))
						throw std::out_of_range("Requested element is out of range.");
					return (_vector[n]);
				};
				reference at(size_type n)
				{
					if (n < 0 || n > (_size - 1))
						throw std::out_of_range("Requested element is out of range.");
					return (_vector[n]);
				};
				const_reference at(size_type n) const
				{
					if (n < 0 || n > (_size - 1))
						throw std::out_of_range("Requested element is out of range.");
					return (_vector[n]);
				};
				reference front()
				{
					return (_vector[0]);
				};
				const_reference front() const
				{
					return (_vector[0]);
				};
				reference back()
				{
					return (_vector[_size - 1]);
				};
				const_reference back() const
				{
					return (_vector[_size - 1]);
				};
				/*
				 * MODIFIERS
				 */

				template <class InputIterator>
					void assign (InputIterator first, InputIterator last)
					{
						clear();
						insert(begin(), first, last);
					};
				void assign (size_type n, const value_type& val)
				{
					clear();
					insert(begin(), n, val);
				};
				void push_back (const value_type& val)
				{
					if (_capacity == 0)
					{
						_vector = _alloc.allocate(1);
						_alloc.construct(&_vector[0], val);
						_capacity++;
						_size++;
						return ;
					}
					else if (_size + 1 >= _capacity)
						reserve(_capacity * 2);
					_alloc.construct(&_vector[_size], val);
					_size++;

				};
				void pop_back()
				{
					_alloc.destroy(&_vector[_size - 1]);
					--_size;
				};

				iterator insert (iterator position, const value_type& val)
				{
					size_type	pos_size_t = position - begin();
					iterator	ret;
					size_type	size_save = _size;
					size_type	capacity_save = _capacity;

					if (position != end())
					{
						if (_size + 1 > _capacity)
						{
							pointer tmp = _alloc.allocate(_size + 1);
							for (size_type i  = end() - begin() - 1; i >= pos_size_t; --i)
							{
								if (i > max_size())
									break ;
								_alloc.construct(&tmp[i + 1], _vector[i]);
							}
							_alloc.construct(&tmp[pos_size_t], val);
							for (size_type i = pos_size_t - 1; i >= 0; --i)
							{
								if (i > max_size())
									break ;
								_alloc.construct(&tmp[i], _vector[i]);
							}
							clear();
							_vector = tmp;
							_capacity = capacity_save + 1;
							_size = size_save + 1;
						}
						else
						{
							for (size_type i = _size; i > pos_size_t; --i)
								_alloc.construct(&_vector[i], _vector[i - 1]);
							_alloc.construct(&_vector[pos_size_t], val);
							++_size;
						}
					}
					else
						push_back(val);
					ret = begin() + pos_size_t;

					return (ret);
				};
				void insert (iterator position, size_type n, const value_type& val)
				{
					//printStatus();
					size_type	pos_size_t = position - begin();
					size_type	size_save = _size;
					size_type	capacity_save = _capacity;

					if (n == 0)
						return ;
					if (position != end())
					{
						if (_size + n > _capacity)
						{
							pointer tmp = _alloc.allocate(_size + n);
							for (size_type i  = end() - begin() - 1; i >= pos_size_t; --i)
							{
								if (i > max_size())
									break ;
								_alloc.construct(&tmp[i + n], _vector[i]);
							}
							for (size_type i = pos_size_t + n - 1; i >= pos_size_t; --i)
							{
								if (i > max_size())
									break ;
								_alloc.construct(&tmp[i], val);
							}
							for (size_type i = pos_size_t - 1; i >= 0; --i)
							{
								if (i > max_size())
									break ;
								_alloc.construct(&tmp[i], _vector[i]);
							}
							clear();
							_vector = tmp;
							_capacity = capacity_save + n;
							_size = size_save + n;
						}
						else
						{
							for (size_type i = _size; i > pos_size_t; --i)
								_alloc.construct(&_vector[i], _vector[i - n]);
							for (size_type i = 0; i < n; ++i)
								_alloc.construct(&_vector[pos_size_t++], val);
							_size += n;
						}
					}
					else
						for (size_type i = 0; i < n; ++i)
							push_back(val);
				};
				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = u_nullptr)
					{
						size_type	pos_size_t = position - begin();
						size_type	n = 0;
						size_type	size_save = _size;
						size_type	capacity_save = _capacity;

						for (InputIterator it = first; it != last; ++it)
							++n;
						if (position != end())
						{
							if (_size + n > _capacity)
							{
								pointer tmp = _alloc.allocate(_size + n);
								for (size_type i  = end() - begin() - 1; i >= pos_size_t; --i)
								{
									if (i > max_size())
										break ;
									_alloc.construct(&tmp[i + n], _vector[i]);
								}
								for (size_type i = pos_size_t + n - 1; i >= pos_size_t; --i)
								{
									if (i > max_size())
										break ;
									--last;
									_alloc.construct(&tmp[i], *(last));
								}
								for (size_type i = pos_size_t - 1; i >= 0; --i)
								{
									if (i > max_size())
										break ;
									_alloc.construct(&tmp[i], _vector[i]);
								}
								clear();
								_vector = tmp;
								_capacity = capacity_save + n;
								_size = size_save + n;
							}
							else
							{
								for (size_type i = _size; i > pos_size_t; --i)
									_alloc.construct(&_vector[i], _vector[i - 1]);
								while (first != last)
									_alloc.construct(&_vector[pos_size_t++], *(first++));
								_size += n;
							}
						}
						else
							for (size_type i = 0; i < n; ++i)
								push_back(*first++);
					};

				iterator erase (iterator position)
				{
					_alloc.destroy(&position);
					--_size;
					for (iterator it = position; it != end(); ++it)
						*it = *(it + 1);
					return (position);
				};
				iterator erase (iterator first, iterator last)
				{
					size_type pos = 0;
					size_type len = 0;
					size_type tmp_pos;

					for (iterator it = begin(); it != first; ++it)
						pos++;
					for (iterator it = first; it != last; ++it)
						len++;
					tmp_pos = pos;
					for (iterator it = first; it != last; ++it)
						_alloc.destroy(&_vector[tmp_pos++]);
					for (size_type i = pos; (i - pos) < (_size - len); ++i)
						_alloc.construct(&_vector[i], _vector[i + len]);
					_size -= len;
					return (first);
				};
				void swap (vector& x)
				{
					size_type tmp_size_t = x._size;
					x._size = _size;
					_size = tmp_size_t;

					tmp_size_t = x._capacity;
					x._capacity = _capacity;
					_capacity = tmp_size_t;

					pointer	tmp_vector = x._vector;
					x._vector = _vector;
					_vector = tmp_vector;

					allocator_type tmp_alloc = x._alloc;
					x._alloc = _alloc;
					_alloc = tmp_alloc;
				};
				void clear()
				{
					erase(begin(), end());
				};

		};
}
#endif
