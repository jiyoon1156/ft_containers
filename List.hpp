#ifndef LIST_HPP
#define LIST_HPP

#include "Iterator.hpp"
#include "Node.hpp"

namespace ft	{
	template <typename T, class Category = bidirectional_iterator_tag>
	class ListIterator
	{
		private:
			Node<T>* _ptr;
		public:
			/*           *           */
			/* iterator member types */
			/*           *           */
			typedef T 							value_type;
			typedef std::ptrdiff_t	difference_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef Category				iterator_category;

			ListIterator(){}
			virtual ~ListIterator(){}
			ListIterator(Node<T> *ptr) : _ptr(ptr) {}
			ListIterator(const ListIterator& copy)
			{
				*this = copy;
			}
			ListIterator& operator=(const ListIterator& other)
			{
				_ptr = other._ptr;
				return (*this);
			}
			bool operator==(const ListIterator &other) const
			{
				return (_ptr == other._ptr);
			}
			bool operator!=(const ListIterator &other) const
			{
				return (_ptr != other._ptr);
			}
			T& operator*(void)
			{
				return(_ptr->data);
			}
			T* operator->(void)
			{
				return(&(_ptr->data));
			}
			ListIterator& operator++(void)
			{
				if (_ptr && _ptr->next)
					_ptr = _ptr->next;
				return (*this);
			}
			ListIterator operator++(int)
			{
				ListIterator tmp(*this);
				operator++();
				return (tmp);
			}
			ListIterator& operator--(void)
			{
				if (_ptr && _ptr->prev)
					_ptr = _ptr->prev;
				return (*this);
			}
			ListIterator operator--(int)
			{
				ListIterator tmp(*this);
				operator--();
				return (tmp);
			}
			Node<T> *getPtr(void)
			{
				return (_ptr);
			}
	};

	template < class T, class Alloc = std::allocator<T> >
	class List
	{
		private:
			Node<T> *_head;
			Node<T>	*_tail;
			size_t	_size;
		public:
			typedef T													value_type;
			typedef Alloc											allocator_type;
			typedef Alloc											reference;
			typedef Alloc											const_reference;
			typedef Alloc											pointer;
			typedef Alloc 										const_pointer;
			typedef ListIterator<T>						iterator;
			typedef ListIterator<const T>			const_iterator;
			typedef ReverseIterator<T>				reverse_iterator;
			typedef ReverseIterator<const T>	const_reverse_iterator;
			typedef std::ptrdiff_t 						difference_type;
			typedef size_t 										size_type;

			// explicit List(const allocator_type& alloc = allocator_type());
			// explicit List(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			// template <class InputIterator>
			// List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

			explicit List(): _head(nullptr), _tail(nullptr), _size(0)
			{
				_tail = new Node<T>();
				_tail->next = nullptr;
				_tail->prev = nullptr;
				_tail->data = 0;
				_head = _tail;
			};
			explicit List(size_type n, const value_type& val = value_type()): _head(nullptr), _tail(nullptr), _size(0)
			{
				_tail = new Node<T>();
				_tail->next = nullptr;
				_tail->prev = nullptr;
				_tail->data = 0;
				//n 개의 컨테이너를 val 값으로 채운다.
				insert(_head, n, val);
			};
			template <class InputIterator>
			List(InputIterator first, InputIterator last): _head(nullptr), _tail(nullptr), _size(0)
			{
				_tail = new Node<T>();
				_tail->next = nullptr;
				_tail->prev = nullptr;
				_tail->data = 0;
				//input iterator라 처음과 끝사이에 있는 값들이 채워짐
				insert(_head, first, last);
			};
			~List(){};
			List(const List& copy)
			{
				*this = copy;
			};
			List& operator=(const List& other)
			{
				// if (_size != 0)
				// 	clear();
				if (!_tail)
				{
					_tail = new Node<T>();
					_tail->next = nullptr;
					_tail->prev = nullptr;
					_tail->data = 0;
					_head = _tail;
				}
				if (other.size())
					insert(end(), other.begin(), other.end());
				return (*this);
			};
			/* iterators */
			iterator begin()
			{
				return iterator(_head);
			};
			const_iterator begin() const
			{
				return const_iterator((Node<const T>*)_head);
			};
			iterator end()
			{
				return iterator(_tail);
			};
			const_iterator end() const
			{
				return const_iterator((Node<const T>*)_tail);
			};
			// reverse_iterator는 node를 받는게 아니라 iterator를 받아서 iterator를 리턴해줘야한다. it.hpp참고
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			};
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			};
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			};
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			};

			// const_iterator cbegin() const noexcept;
			// const_iterator cend() const noexcept;
			// const_reverse_iterator crbegin() const noexcept;
			// const_reverse_iterator crend() const noexcept;

			/* capacity */
			bool empty() const
			{
				//size 0 이면 true 아니면 false
				return (_size == 0);
			};
			size_type size() const
			{
				return (_size);
			};
			size_type max_size() const
			{
				//자료형의 크기(비트)만큼 나눠준면 해당 자료형 max 크기 알 수 있음
				return (std::numeric_limits<T>::max() / sizeof(Node<T>));
			};
			/* element access */
			reference front()
			{
				return (_head->data);
			};
			const_reference front() const
			{
				return (_head->data);
			};
			reference back()
			{
				return (_tail->prev->data);
			};
			const_reference back() const
			{
				return (_tail->prev->data);
			};
			/* modifiers */
			template <class InputIterator>
  		void assign (InputIterator first, InputIterator last)
			{
				// clear();
				insert(begin(), first, last);
			};
			void assign (size_type n, const value_type& val)
			{
				// clear();
				insert(begin(), n, val);
			};

			// template <class... Args>
  		// void emplace_front (Args&&... args);

			void push_front (const value_type& val)
			{
				Node<T> *new_node = new Node<T>();
				new_node->prev = nullptr;
				new_node->next = _head;
				new_node->data = val;
				_head->prev = new_node;
				_head = new_node;
				++_size;
			};
			void pop_front()
			{
				if (_head == _tail)
					return ;
				Node<T> *tmp;
				tmp = _head;
				_head = _head->next;
				_head->prev = nullptr;
				delete tmp;
				--_size;
			};

			// template <class... Args>
  		// void emplace_back (Args&&... args);

			void push_back (const value_type& val)
			{
				Node<T> *new_node = new Node<T>();
				if (_size != 0)
					_tail->prev->next = new_node;
				else
					_head = new_node;
				new_node->prev = _tail->prev;
				new_node->next = _tail;
				new_node->data = val;
				_tail->prev = new_node;
				++_size;
			};
			void pop_back()
			{
				if (_head == _tail)
					return ;
				//리스트 탐색해서 마지막 전 노드 찾는다
				//그 노드 다음을 널 가리키게 함
				//마지막 노드 제거
				Node<T> *tmp;
				tmp = _tail->prev;
				_tail->prev = tmp->prev;
				tmp->next = _tail;
				delete tmp;
				--_size;
			};

			// template <class... Args>
  		// iterator emplace (const_iterator position, Args&&... args);

			iterator insert (iterator position, const value_type& val)
			{
				insert(position, (std::size_t)1, val);
				return (position.getPtr()->prev);
			};
    	void insert (iterator position, size_type n, const value_type& val)
			{
				//n개만큼 노드 삽입하는데 그것의 값들은 val

			};
			// template <class InputIterator>
    	// void insert (iterator position, InputIterator first, InputIterator last);
			// iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);
			// void swap (List& x);
			// void resize (size_type n, value_type val = value_type());
			// void clear();
			// /* operations */
			// void splice (iterator position, List& x);
			// void splice (iterator position, List& x, iterator i);
			// void splice (iterator position, List& x, iterator first, iterator last);
			// void remove (const value_type& val);
			// template <class Predicate>
  		// void remove_if (Predicate pred);
			// void unique();
			// template <class BinaryPredicate>
			// void unique (BinaryPredicate binary_pred);
			// void merge (List& x);
			// template <class Compare>
  		// void merge (List& x, Compare comp);
			// void sort();
			// template <class Compare>
			// void sort (Compare comp);
			// void reverse();
			// /* observers */
			// allocator_type get_allocator() const;
	};

	/**/
	/* Non-member function overloads */
	/**/
	// template <class T, class Alloc>
	// bool operator== (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	// {

	// };

	template <class T, class Alloc>
	bool operator!= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (lhs != rhs);
	};

	// template <class T, class Alloc>
	// bool operator<  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	// {

	// };

	template <class T, class Alloc>
	bool operator<= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (lhs <= rhs);
	};

	template <class T, class Alloc>
	bool operator>  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (lhs > rhs);
	};

	template <class T, class Alloc>
	bool operator>= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (lhs >= rhs);
	};

	template <class T, class Alloc>
	void swap (List<T,Alloc>& x, List<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
