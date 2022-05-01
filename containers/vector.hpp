#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include "utils/type_traits.hpp"
# include "utils/utils.hpp"
# include "utils/random_access_iterator.hpp"
# include "utils/lexicographical_compare.hpp"
# include <iostream>

namespace ft
{
	template<class T, class A = std::allocator<T> >
		class vector
		{
			public:
				typedef T														value_type;
				typedef	A														allocator_type;
				typedef typename A::reference									reference;
				typedef typename A::const_reference								const_reference;
				typedef typename A::pointer										pointer;
				typedef typename A::const_pointer								const_pointer;
				typedef	typename ft::random_access_iterator<value_type>			iterator;
				typedef	typename ft::random_access_iterator<const value_type>	const_iterator;
				typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
				typedef	std::ptrdiff_t											difference_type;
				typedef size_t													size_type;

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
	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T>::const_iterator flhs = lhs.begin();
		typename ft::vector<T>::const_iterator frhs = rhs.begin();
		while (flhs != lhs.end())
		{
			if (frhs == rhs.end() || *flhs != *frhs)
				return (false);
			flhs++;
			frhs++;
		}
		return (true);
	}
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
		bool operator>=  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}


}
#endif
