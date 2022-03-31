#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include "vectorIterator.hpp"

namespace ft
{
	template<class T, class A = std::allocator<T>>
		class vector
		{
			public:
				typedef	A allocator_type;
				typedef typename A::value_type		value_type;
				typedef typename A::reference		reference;
				typedef typename A::const_reference const_reference;
				typedef typename A::difference_type difference_type;
				typedef typename A::size_type		size_type;

				explicit vector(const allocator_type& alloc = allocator_type())
					:	_vector(NULL), _size(0), _capacity(0), _alloc(alloc)
				{
				};
				explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
					: _size(n), _capacity(n), _alloc(alloc)
				{
					_vector = _alloc.allocate(n);
					for (size_type i; i < n; i++)
						_vector[i] = val;
				};
				template <class InputIterator>
					vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type())
					: _size(last - first), _capacity(last - first), _alloc(alloc)
					{
						size_type i = 0;
						_vector = _alloc.allocate(_size);
						while (first != last)
						{
							_vector[i++];
							first++;
						}
					};
				vector (const vector& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
			{
				_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_vector[i] = x.vector[i];
			};
				~vector()
				{
					this->clear();
					_alloc.deallocate(_vector, _capacity);
				};

				iterator	begin()
				{
					return (ft::vector<T, A>::iterator(&_vector[0]));
				};
				const iterator	begin() const
				{
					return (ft::vector<T, A>::const_iterator(&_vector[0]));
				};
				iterator	end()
				{
					return (ft::vector<T, A>::iterator(&_vector[_size]));
				}
				const iterator	end() const
				{
					return (ft::vector<T, A>::const_iterator(&_vector[_size]));
				}
			private:
				value_type		*_vector;
				allocator_type	_alloc;
				size_t			_capacity;
				size_t			_size;
		};
}
#endif
