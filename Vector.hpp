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
			Alloc		_alloc;
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

			/*
			allocate 초기화되지 않은 메모리 공간 할당해서 시작 주소 반환
			deallocate 함수는 메모리 공간을 해제
			construct 함수는 초기화되지 않은 공간에 요소를 저장
			destroy 함수는 객체를 소멸
			uninitialized_copy 함수는 멤버 함수는 아니지만 자주 사용되는 관련된 함수입니다.
			STL의 std::copy함수와 비슷하며 입력 반복자 2개(first, last)와 순방향 반복자 1개(out)를 인자로 받습니다.
			[first, last) 범위의 요소들을 out이 가리키는 위치에 순서대로 복사합니다.
			그리고 이 함수는 복사가 완료된 위치의 다음 요소를 가리키는 포인터를 반환합니다.
			즉 1~5 위치에 복사를 완료했다면 6위치를 가리키는 포인터를 반환합니다.
			*/
			explicit Vector (const allocator_type& alloc = allocator_type()): _ptr(nullptr), _size(0), _capa(0)
			{
				_ptr = _alloc.allocate(1);
			};
			explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _ptr(nullptr), _size(n), _capa(n)
			{
				_ptr = _alloc.allocate(n + 1);
				for (int i = 0; i < n; ++i)
					_alloc.construct(&_ptr[i], val);
			};
			template <class InputIterator>
			Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _ptr(nullptr), _size(0), _capa(0)
			{
				_ptr = _alloc.allocate(1);
				assign(first, last);
			};
			Vector (const Vector& x): _ptr(nullptr), _size(0), _capa(0)
			{
				*this = x;
			};
			~Vector()
			{
				for (int i = 0; i < _size; ++i)
					_alloc.destroy((_ptr + i));
				_alloc.deallocate(_ptr, _capa + 1);
			};
			Vector& operator= (const Vector& x)
			{
				assing(x.begin(), x.end());
				return (*this);
			};

			/* iterators */
			iterator begin()
			{
				return iterator(_ptr);
			};
			const_iterator begin() const
			{
				return const_iterator(_ptr);
			};
			iterator end()
			{
				return iterator(_ptr + _size);
			};
			const_iterator end() const
			{
				return const_iterator(_ptr + _size);
			};
			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			};
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			};
			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			};
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			};

			/* capacity */
			size_type size() const
			{
				return (_size);
			};
			size_type max_size() const
			{
				return (std::numeric_limits<T>::max() / sizeof(T));
			};
			void resize (size_type n, value_type val = value_type())
			{
				while(n < _size)
					pop_back();
				while(_size < n)
					push_back(val);
			};
			size_type capacity() const
			{
				return (_capa);
			};
			bool empty() const
			{
				return (_size == 0);
			};
			void reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("length error");
				if (n > _capa)
				{
					T* newPtr;
					newPtr = _alloc.allocate(n + 1);
					for (size_type i = 0; i < _size; ++i)
						_alloc.construct(&newPtr[i], _ptr[i]);
					_ptr = newPtr;
					_capa = n;
				}
				else
					throw std::bad_alloc("bad alloc");
			};

			/* element access */
			reference operator[] (size_type n)
			{
				return (_ptr[n]);
			};
			const_reference operator[] (size_type n) const
			{
				return (_ptr[n]);
			};
			reference at (size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("out of range");
				return (_ptr[n]);
			};
			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("out of range");
				return (_ptr[n]);
			};
			reference front()
			{
				return (*_ptr);
			};
			const_reference front() const
			{
				return (*_ptr);
			};
			reference back()
			{
				return (*(_ptr + _size - 1));
			};
			const_reference back() const;
			{
				return (*(_ptr + _size - 1));
			};
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
	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		//사이즈로 먼저 비교하고 val 비교
		if (lhs.size() != rhs.size())
			return (false);
		typename Vector<T, Alloc>::const_iterator	it_r = rhs.begin();
		typename Vector<T, Alloc>::const_iterator	it_l = lhs.begin();
		for (; (it_l != lhs.end()) && (it_r != rhs.end()); ++it_l, ++it_r)
		{
			if (*it_l != *it_r)
				return (false);
		}
		return (true);
	};

	template <class T, class Alloc>
	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	};

	template <class T, class Alloc>
	bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		typename Vector<T, Alloc>::const_iterator	it_r = rhs.begin();
		typename Vector<T, Alloc>::const_iterator	it_l = lhs.begin();
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
	bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (!(lhs > rhs));
	};

	template <class T, class Alloc>
	bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	};

	template <class T, class Alloc>
	bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	};

	template <class T, class Alloc>
	void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)
	{
		x.swap(y);
	};

	// /* class template specialization */
	// template < class T, class Alloc = allocator<T> > class vector; // generic template
	// template <class Alloc> class vector<bool,Alloc>;               // bool specialization
}

#endif
