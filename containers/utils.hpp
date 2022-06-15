#ifndef UTILS_HPP
# define UTILS_HPP


# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>

static class u_nullptr_t
{
    public:
               template<class T>
        operator T*() const { return (0); }

               template<class C, class T>
        operator T C::*() const { return (0); }

    private:

               void operator&() const;

} u_nullptr = {};

namespace ft
{
    class bidirectional_iterator_tag { };
    class random_access_iterator_tag { };


    template <bool is_valid, typename T>
        struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };

	template <typename T>
        struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };

	template <>
        struct is_input_iterator_tagged<ft::random_access_iterator_tag>
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };
    template <>
        struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    template <typename T>
        struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };

    template <>
        struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    template <>
        struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::forward_iterator_tag */
	template <class Iterator>
		struct iterator_traits
		{
			public:
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::iterator_category	iterator_category;
		};
	template <class T>
		struct iterator_traits<T*>
		{
			public:
				typedef ptrdiff_t						difference_type;
				typedef T								value_type;
				typedef T*								pointer;
				typedef T&								reference;
				typedef ft::random_access_iterator_tag	iterator_category;

		};
	template <class T>
		struct iterator_traits<const T*>
		{
			public:
				typedef ptrdiff_t						difference_type;
				typedef T								value_type;
				typedef const T*						pointer;
				typedef const T&						reference;
				typedef ft::random_access_iterator_tag	iterator_category;

		};

	template <class Category, class T, class Distance = ptrdiff_t,
			 class Pointer = T*, class Reference = T&>
				 class iterator
				 {
					 public:
						 typedef T         value_type;
						 typedef Distance  difference_type;
						 typedef Pointer   pointer;
						 typedef Reference reference;
						 typedef Category  iterator_category;
				 };

	template <class Iterator>
		class	reverse_iterator
	{
		public:
			typedef				Iterator											iterator_type;
			typedef typename	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename    ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename	ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef	typename	ft::iterator_traits<Iterator>::pointer				pointer;
			typedef	typename	ft::iterator_traits<Iterator>::reference			reference;

			reverse_iterator(void) : _ptr()							{};
			explicit reverse_iterator(iterator_type it) : _ptr(it)				{};
			template <class It>
                reverse_iterator (const reverse_iterator<It>& rev_it)
                :
                    _ptr(rev_it.base())
                {}
			virtual ~reverse_iterator()											{};

			iterator_type base() const									{return (_ptr);};
			reverse_iterator& operator++()								{_ptr--; return *this;};
			reverse_iterator operator++(int)							{reverse_iterator tmp(*this); _ptr--; return tmp;};
			reverse_iterator& operator--()								{_ptr++; return *this;};
			reverse_iterator operator--(int)							{reverse_iterator tmp(*this); _ptr++; return tmp;};
			reverse_iterator& operator+=(difference_type n)				{_ptr = _ptr - n; return *this;};
			reverse_iterator operator+(difference_type n) const			{return (reverse_iterator(_ptr - n));};
			reverse_iterator& operator-=(difference_type n)				{_ptr = _ptr + n; return *this;};
			reverse_iterator operator-(difference_type n) const			{return (reverse_iterator(_ptr + n));};

			reference operator*() const									{iterator_type tmp = _ptr; return *(--tmp);};
			pointer operator->() const									{return &(operator*());};
			reference operator[] (difference_type n) const				{return (this->base()[-n - 1]);}

		private:
			iterator_type	_ptr;

	};

    template <class Iterator>
        bool operator== (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator== (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator!= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator>
        bool operator<  (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator< (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator<= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator>
        bool operator> (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator> (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() < rhs.base()); }
    template <class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator>= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator>
        reverse_iterator<Iterator> operator+ (
            typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }

    template <class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator- (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		typename reverse_iterator<Iterator_L>::difference_type operator- (const reverse_iterator<Iterator_L>& lhs,
				const reverse_iterator<Iterator_R>& rhs) { return (rhs.base() - lhs.base()); }

}



#endif
