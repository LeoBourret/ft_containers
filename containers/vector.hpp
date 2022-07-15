#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include "type_traits.hpp"
# include "utils.hpp"
# include "random_access_iterator.hpp"
# include "lexicographical_compare.hpp"
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
						_alloc.construct(_vector + i, val);
				};

				template <class InputIterator>
					vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type(),
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = u_nullptr)
					: _alloc(alloc), _capacity(0), _size(0)
					{
						_size = std::distance(first, last);
						_capacity = _size;
						_vector = _alloc.allocate(_size);
						for (size_type i = 0; i < _size; i++)
						{
							_alloc.construct(_vector + i, *first);
							first++;
						}
					}

				vector (const vector& x) :  _alloc(x._alloc), _capacity(x._size), _size(x._size)
				{
					_vector = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_vector + i, x._vector[i]);
				};

				~vector()
				{
					this->clear();
					_alloc.deallocate(_vector, _capacity);
				};

				vector & operator= (vector const & x)
				{
					if (this == &x)
						return *this;
					this->clear();
					_alloc.deallocate(_vector, _capacity);
					_size = x._size;
					if (_capacity < x._size)
						_capacity = _size;
					_vector = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_vector + i, x._vector[i]);
					return *this;
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
					if (n < _size)
						while (_size > n)
							pop_back();
					else if (n > _size)
						insert(end(), n - size(), val);

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
					size_type	new_capacity;;

					if (n > max_size())
						throw std::length_error("vector::reserve");
					else if (n <= _capacity)
						return ;
					else
					{
						tmp = _alloc.allocate(n);
						new_capacity = n;
					}
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&tmp[i], _vector[i]);
					size_save = _size;
					clear();
					_alloc.deallocate(_vector, _capacity);
					_size = size_save;
					_capacity = new_capacity;
					_vector = tmp;
				};

				/*
				 * ELEMENT ACCESS
				 */
				reference operator[] (size_type n)
				{
					return (_vector[n]);
				};

				const_reference operator[] (size_type n) const
				{
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
					if (_size == _capacity)
						reserve((_capacity ? _capacity * 2 : 1));
					_alloc.construct(_vector + _size, val);
					_size++;
				};

				void pop_back()
				{
					if (_size)
					{
						_alloc.destroy(&_vector[_size - 1]);
						--_size;
					}
				};

				iterator insert (iterator position, const value_type& val)
				{
					size_type pos_size_t = position - begin();

					if (_size == _capacity)
						reserve((_capacity ? _capacity * 2 : 1));
					position = _vector + pos_size_t;
					if (position != end())
					{
						for (iterator it = end() - 1; it != position - 1; it--)
						{
							_alloc.construct((it + 1).base(), *it);
							_alloc.destroy(it.base());
						}
					}
					_alloc.construct(position.base(), val);
					++_size;
					return (position);
				};
				void insert (iterator position, size_type n, const value_type& val)
				{
					size_type pos_size_t = position - begin();

					if (n <= 0)
						return ;
					if (n > _capacity - _size)
					{
						if (n <= _size)
							reserve(_size * 2);
						else
							reserve(_size + n);
						position = _vector + pos_size_t;
					}
					if (position != end())
					{
						for (iterator it = end() - 1; it != position - 1; it--)
						{
							_alloc.construct((it + n).base(), *it);
							_alloc.destroy(it.base());
						}
					}
					for (size_type i = 0; i < n; i++)
					{
						_alloc.construct((position).base(), val);
						position++;
					}
					_size += n;
				};
				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = u_nullptr)
					{
						size_type	size = std::distance(first, last);
						size_type pos_size_t = position - begin();

						if (size <= 0)
							return ;
						if (size > _capacity - _size)
						{
							if (size <= _size)
								reserve(_size * 2);
							else
								reserve(_size + size);
						}
						position = _vector + pos_size_t;
						if (position != end())
						{
							for (iterator it = end() - 1; it != position - 1; it--)
							{
								_alloc.construct((it + size).base(), *it);
								_alloc.destroy(it.base());
							}
						}
						for (size_type i = 0; i < size; i++)
						{
							_alloc.construct(position.base(), *first);
							position++;
							first++;
						}
						_size += size;
					};

				iterator erase (iterator position)
				{
					iterator ret = position;

					for (; position != end(); ++position)
					{
						_alloc.destroy(position.base());
						if (position != end() - 1)
							_alloc.construct(position.base(), *(position + 1));
					}
					--_size;
					return (ret);
				};

				iterator erase (iterator first, iterator last)
				{
					iterator ret = first;
					size_type distance =last - first;
					size_type size = distance;

					if (distance == 0)
						return (first);
					for (;first + size != end(); first++)
					{
						_alloc.destroy(first.base());
						_alloc.construct(first.base(), *(first + size));
					}
					for (iterator it = end() - 1; size != 0; size--)
					{
						_alloc.destroy(it.base());
						it--;
					}
					_size -= distance;
					return (ret);
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

				allocator_type	get_allocator () const {return _alloc;};
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
		return (!(lhs > rhs));
	}
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
		bool operator>=  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs <= lhs);
	}

template <class T, class Alloc>
void swap (vector<T, Alloc> & x, vector<T, Alloc> & y) {
	x.swap(y);
}


}
#endif
