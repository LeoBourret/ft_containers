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

			random_access_iterator(void) : _ptr(u_nullptr)								{};
			random_access_iterator(pointer ptr)	: _ptr(ptr)								{};
			random_access_iterator(const random_access_iterator &src) : _ptr(src._ptr)	{};
			random_access_iterator& operator=(const random_access_iterator &rhs)
			{
				if (this == rhs)
					return (*this);
				_ptr = rhs._ptr;
				return *this;
			};
			virtual ~random_access_iterator()	{};

			pointer	base() const										{return (this->_ptr);};

			random_access_iterator& operator++()						{_ptr = _ptr + 1; return *this;};
			random_access_iterator operator++(int)						{random_access_iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
			random_access_iterator& operator--()						{_ptr = _ptr - 1; return *this;};
			random_access_iterator operator--(int)						{random_access_iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
			random_access_iterator& operator+=(difference_type n)		{_ptr = _ptr + n; return *this;};
			random_access_iterator operator +(difference_type n) const	{ return (random_access_iterator(_ptr + n)); }; // a + n
			random_access_iterator& operator-=(difference_type n)		{_ptr = _ptr - n; return *this;};
			random_access_iterator operator-(difference_type n) const	{return (random_access_iterator(_ptr - n));};
			difference_type operator-(random_access_iterator rhs) const	{return (_ptr - rhs._ptr);};

			friend random_access_iterator operator+(difference_type n, const random_access_iterator& rhs);

			difference_type operator +(random_access_iterator b) { return (_ptr + b._ptr); };

			bool operator==(const random_access_iterator& rhs) const	{return (_ptr == rhs._ptr);};
			bool operator!=(const random_access_iterator& rhs) const	{return !(operator==(rhs));};
			bool operator<(const random_access_iterator& rhs) const		{return (_ptr < rhs._ptr);};
			bool operator>(const random_access_iterator& rhs) const		{return (_ptr > rhs.ptr);};
			bool operator<=(const random_access_iterator& rhs) const	{return (operator==(rhs) || operator<(rhs));};
			bool operator>=(const random_access_iterator& rhs) const	{return  (operator==(rhs) || operator>(rhs));};


			reference operator*() const						{return (*_ptr);};
			pointer	operator&()	const						{return _ptr;};
			pointer operator->() const						{return &(this->operator*());};
			reference operator[](difference_type n) const	{return *(operator+(n));};

			operator random_access_iterator<const T> () const
			{ return (random_access_iterator<const T>(this->_ptr)); }
	};
/*	template<typename T>
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
	}*/
	/*
    ** @brief Check if the pointer of "lhs"
    ** is equal than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if equal than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator==(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /* For iterator == const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator==(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is different than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if different than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator!=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /* For iterator != const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator!=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is lower than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if lower than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /* For iterator < const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is upper than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if upper than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    /* For iterator > const_iterator */
    template<typename T_L,
             typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is lower or equal than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if lower or equal than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /* For iterator <= const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is upper or equal than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if upper or equal than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /* For iterator >= const_iterator */
    template<typename T_L,
             typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /*
    ** @brief Give a random access iterator pointing to
    ** "rai" plus "n".
    **
    ** @param n The number of location away the element pointed
    ** by rai.
    ** @param rai The random access iterator.
    ** @return A random access iterator pointing to n element
    ** after rai pointed element.
    */
    template<typename T>
    ft::random_access_iterator<T> operator+(
        typename ft::random_access_iterator<T>::difference_type n,
        typename ft::random_access_iterator<T>& rai)
        {
            return (&(*rai) + n);
        }

    /*
    ** @brief Give the difference between the address
    ** of two random access iterators.
    **
    ** @param lhs,rhs the two random access iterator with whom
    ** to make a difference.
    ** @return The difference.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator-(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    /* For iterator - const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator-(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }
};

#endif
