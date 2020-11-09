#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Iterator.hpp"
#include "Node.hpp"

namespace ft
{
	template <typename T, class Category = random_access_iterator_tag>
	class VectorIterator
	{
		private:
			T* _ptr;
		public:
			/*           *           */
			/* iterator member types */
			/*           *           */
			typedef T 							value_type;
			typedef std::ptrdiff_t	difference_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef Category				iterator_category;

			VectorIterator(): _ptr(nullptr){}
			VectorIterator(T *ptr): _ptr(ptr){}
			VectorIterator(const VectorIterator &copy){ *this = copy; }
			VectorIterator& operator=(const VectorIterator& other)
			{
				_ptr = other._ptr;
				return (*this);
			}
			virtual ~VectorIterator(){}
			bool operator==(const VectorIterator &other) const
			{
				return (_ptr == other._ptr);
			}
			bool operator!=(const VectorIterator &other) const
			{
				return (_ptr != other._ptr);
			}
			T& operator*(void)
			{
				return(*_ptr);
			}
			T* operator->(void)
			{
				return(_ptr);
			}
			VectorIterator& operator++(void)
			{
				++_ptr;
				return (*this);
			}
			VectorIterator operator++(int)
			{
				VectorIterator tmp(*this);
				operator++();
				return (tmp);
			}
			VectorIterator& operator--(void)
			{
				--_ptr;
				return (*this);
			}
			VectorIterator operator--(int)
			{
				VectorIterator tmp(*this);
				operator--();
				return (tmp);
			}
			VectorIterator operator+(difference_type n)
			{
				return (VectorIterator(_ptr + n));
			}
			VectorIterator operator-(difference_type n)
			{
				return (VectorIterator(_ptr - n));
			}
			bool operator<(const VectorIterator &other) const
			{
				return (_ptr < other._ptr);
			}
			bool operator>(const VectorIterator &other) const
			{
				return (other._ptr < _ptr);
			}
			bool operator<=(const VectorIterator &other) const
			{
				return (!(other._ptr < _ptr));
			}
			bool operator>=(const VectorIterator &other) const
			{
				return (!(_ptr < other._ptr));
			}
			VectorIterator&	operator+= (difference_type n)
			{
				_ptr += n;
				return (*this);
			};
			VectorIterator&	operator-= (difference_type n)
			{
				_ptr -= n;
				return (*this);
			};
			T& operator[](int n)
			{
				return (*(_ptr + n));
			}
			T* getPtr()
			{
				return (_ptr);
			}
	};

	template <class T, class Alloc = std::allocator<T>>
	class Vector
	{
		private:
			T*			_ptr;
			size_t	_capa;
			size_t	_size;
		public:
			typedef T																value_type;
			typedef Alloc														allocator_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			typedef VectorIterator<T>								iterator;
			typedef VectorIterator<const T>					const_iterator;
			typedef ReverseIterator<iterator>				reverse_iterator;
			typedef ReverseIterator<const_iterator>	const_reverse_iterator;
			typedef std::ptrdiff_t 									difference_type;
			typedef size_t 													size_type;

			explicit Vector (const allocator_type& alloc = allocator_type());
			explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
			Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			Vector (const Vector& x);
			~Vector(){};
			Vector& operator= (const Vector& x);

			/* iterators */
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			/* capacity */
			size_type size() const;
			size_type max_size() const;
			void resize (size_type n, value_type val = value_type());
			size_type capacity() const;
			bool empty() const;
			void reserve (size_type n);
			void shrink_to_fit();

			/* element access */
			reference operator[] (size_type n);
			const_reference operator[] (size_type n) const;
			reference at (size_type n);
			const_reference at (size_type n) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			/* modifiers */
			template <class InputIterator>
  		void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val);
			void push_back (const value_type& val);
			void pop_back();
			iterator insert (iterator position, const value_type& val);
    	void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last);
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			void swap (vector& x);
			void clear();

			/* allocator */
			allocator_type get_allocator() const;
	};

	/* non-member function overloads */
	template <class T, class Alloc>
	bool operator== (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		//사이즈로 먼저 비교하고 val 비교
		if (lhs.size() != rhs.size())
			return (false);
		typename List<T, Alloc>::const_iterator	it_r = rhs.begin();
		typename List<T, Alloc>::const_iterator	it_l = lhs.begin();
		for (; (it_l != lhs.end()) && (it_r != rhs.end()); ++it_l, ++it_r)
		{
			if (*it_l != *it_r)
				return (false);
		}
		return (true);
	};

	template <class T, class Alloc>
	bool operator!= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	};

	template <class T, class Alloc>
	bool operator<  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		typename List<T, Alloc>::const_iterator	it_r = rhs.begin();
		typename List<T, Alloc>::const_iterator	it_l = lhs.begin();
		for (; (it_l != lhs.end()) && (it_r != rhs.end()); ++it_l, ++it_r)
		{
			if (*it_l < *it_r)
				return (true);
			if (*it_r < *it_l)
				return (false);
		}
		return (it_l == lhs.end() && it_r != rhs.end());
	};

	template <class T, class Alloc>
	bool operator<= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(lhs > rhs));
	};

	template <class T, class Alloc>
	bool operator>  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	};

	template <class T, class Alloc>
	bool operator>= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	};

	template <class T, class Alloc>
	void swap (List<T,Alloc>& x, List<T,Alloc>& y)
	{
		x.swap(y);
	};

	// /* class template specialization */
	// template < class T, class Alloc = allocator<T> > class vector; // generic template
	// template <class Alloc> class vector<bool,Alloc>;               // bool specialization
}

#endif
