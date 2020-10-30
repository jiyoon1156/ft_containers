#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft	{
	/*				 *					 */
	/* iterator categories */
	/*					*					 */
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	/*				*				 */
	/* iterator traits */
	/*				*				 */
	template <class Iterator>
	class iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type					value_type;
		typedef typename Iterator::pointer						pointer;
		typedef typename Iterator::reference					reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	template <class T>
	class iterator_traits<T*>
	{
		typedef std::ptrdiff_t							difference_type;
		typedef T													value_type;
		typedef T*													pointer;
		typedef T&													reference;
		typedef random_access_iterator_tag	iterator_category;
	};
	template <class T>
	class iterator_traits<const T*>
	{
		typedef std::ptrdiff_t							difference_type;
		typedef T														value_type;
		typedef const T*										pointer;
		typedef const T&										reference;
		typedef random_access_iterator_tag	iterator_category;
	};
	/*				* 				*/
	/* Reverse iterator */
	/*				*	 			  */
	template <class Iterator>
	class ReverseIterator
	{
		private:
			Iterator _base_it;
		public:
			typedef Iterator 																							iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type				value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer						pointer;
			typedef typename iterator_traits<Iterator>::reference					reference;

		/*				*					*/
		/* member functions */
		/*				*					*/
		ReverseIterator(){};
		~ReverseIterator(){};
		/* initialization */
		explicit ReverseIterator(iterator_type it)
		{
			_base_it = it;
		};
  	ReverseIterator(const ReverseIterator<Iterator>& copy)
		{
			*this = copy;
		};
		iterator_type			base() const
		{
			return (_base_it);
		};
		reference					operator*() const
		{
			iterator_type Rev_it(_base_it);
			return (*--Rev_it); //coz it points the last + 1
		};
		/*
		Returns a reverse iterator pointing to the element located n positions away
		from the element the iterator currently points to.
		*/
		ReverseIterator		operator+ (difference_type n) const
		{
			return (ReverseIterator(_base_it - n));
		};
		ReverseIterator&	operator++()
		{
			--_base_it;
			return (*this);
		};
		ReverseIterator		operator++(int)
		{
			ReverseIterator temp = *this;
			++(*this);
			return (temp);
		};
		ReverseIterator&	operator+= (difference_type n)
		{
			_base_it -= n;
			return (*this);
		};
		ReverseIterator		operator- (difference_type n) const
		{
			return (ReverseIterator(_base_it + n));
		};
		ReverseIterator&	operator--()
		{
			++_base_it;
			return (*this);
		};
		ReverseIterator		operator--(int)
		{
			ReverseIterator temp = *this;
			--(*this);
			return (temp);
		};
		ReverseIterator&	operator-= (difference_type n)
		{
			_base_it += n;
			return (*this);
		};
		pointer						operator->() const
		{
			return &(operator*());
		};
		reference					operator[] (difference_type n) const
		{
			return (base()[-n-1]);
		};
		/*								*								*/
		/*  Non-member function overloads */
		/*								*					  	  */

		/* relational operators */
		template <class Iterator>
  	bool operator== (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
		{
			return (lhs.base() == rhs.base());
		};
		template <class Iterator>
  	bool operator!= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs);
		{
			return (lhs.base() != rhs.base());
		};
		template <class Iterator>
  	bool operator<  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs);
		{
			return (lhs.base() < rhs.base());
		};
		template <class Iterator>
  	bool operator<= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs);
		{
			return (lhs.base() <= rhs.base());
		};
		template <class Iterator>
  	bool operator>  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs);
		{
			return (lhs.base() > rhs.base());
		};
		template <class Iterator>
  	bool operator>= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs);
		{
			return (lhs.base() >= rhs.base());
		};
		template <class Iterator>
  	ReverseIterator<Iterator> operator+ (typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator>& rev_it)
		{
			return (rev_it + n);
		};
		template <class Iterator>
  	typename ReverseIterator<Iterator>::difference_type operator- (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
		{
			return (rhs.base() - lhs.base());
		};
	};
}

#endif
