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
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef std::random_access_iterator_tag	iterator_category;
			typedef T&																				reference;
			typedef T*																				pointer;

			random_access_iterator(void) : _ptr(u_nullptr)								{};
			random_access_iterator(pointer ptr)	: _ptr(ptr)								{};
			random_access_iterator(const random_access_iterator &src) : _ptr(src._ptr)	{};
			random_access_iterator& operator=(const random_access_iterator &rhs)
			{
				_ptr = rhs._ptr;
				return *this;
			};
			virtual ~random_access_iterator()	{};

			pointer	base() const										{return (_ptr);};

			random_access_iterator& operator++()						{_ptr = _ptr + 1; return *this;};
			random_access_iterator operator++(int)						{random_access_iterator tmp(*this); _ptr = _ptr + 1; return tmp;};
			random_access_iterator& operator--()						{_ptr = _ptr - 1; return *this;};
			random_access_iterator operator--(int)						{random_access_iterator tmp(*this); _ptr = _ptr - 1; return tmp;};
			random_access_iterator& operator+=(difference_type n)		{_ptr = _ptr + n; return *this;};
			random_access_iterator operator +(difference_type n) const	{ return (random_access_iterator(_ptr + n)); };
			random_access_iterator& operator-=(difference_type n)		{_ptr = _ptr - n; return *this;};
			random_access_iterator operator-(difference_type n) const	{return (random_access_iterator(_ptr - n));};
			difference_type operator-(random_access_iterator rhs) const	{return (_ptr - rhs._ptr);};

			difference_type operator +(random_access_iterator b) { return (_ptr + b._ptr); };

			reference operator*() const						{return (*_ptr);};
			pointer	operator&()	const						{return _ptr;};
			pointer operator->() const						{return &(this->operator*());};
			reference operator[](difference_type n) const	{return *(operator+(n));};

			operator random_access_iterator<const T> () const
			{ return (random_access_iterator<const T>(this->_ptr)); }
	};
    template <typename T>
	bool operator==(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /* For iterator == const_iterator */
    template<typename T_L, typename T_R>
	bool operator==(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
	bool operator!=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /* For iterator != const_iterator */
    template<typename T_L, typename T_R>
	bool operator!=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    bool operator<(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /* For iterator < const_iterator */
    template<typename T_L, typename T_R>
	bool
    operator<(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
	bool operator>(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    /* For iterator > const_iterator */
    template<typename T_L,
             typename T_R>
	bool operator>(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
	bool operator<=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /* For iterator <= const_iterator */
    template<typename T_L, typename T_R>
	bool operator<=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
	bool operator>=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /* For iterator >= const_iterator */
    template<typename T_L, typename T_R>
    bool operator>=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T>
    ft::random_access_iterator<T> operator+(
        typename ft::random_access_iterator<T>::difference_type n,
        typename ft::random_access_iterator<T>& rai)
        {
            return (&(*rai) + n);
        }

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
