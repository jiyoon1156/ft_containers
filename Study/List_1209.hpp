#ifndef LIST_HPP
# define LIST_HPP

#include "Iterator.hpp"
#include "Node.hpp"

namespace ft
{
	// template <typename T, class Category = bidirectional_iterator_tag>
	template <class T>
	class ListIterator : public iterator<bidirectional_iterator_tag, T>
	{
		private:
			Node<T>* _ptr;
		public:
			/*           *           */
			/* iterator member types */
			/*           *           */
			// typedef T 							value_type;
			// typedef std::ptrdiff_t	difference_type;
			// typedef T*							pointer;
			// typedef T&							reference;
			// typedef Category				iterator_category;

			ListIterator(): _ptr(nullptr) {}
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
				return (!(_ptr == other._ptr));
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

	template <typename T, typename Alloc = std::allocator<T> >
	class List
	{
		private:
			typedef typename Alloc::template rebind<Node<T> >::other node_alloc;

			Node<T> *_head;
			Node<T>	*_tail;
			size_t	_size;
			Alloc		_alloc;

			Node<T> *dup_node(Node<T> *prev, Node<T> *next, T data)
			{
				Node<T> tmp;
				Node<T> *dest;

				tmp.prev = prev;
				tmp.next = next;
				tmp.data = data;

				dest = node_alloc(_alloc).allocate(1);
				node_alloc(_alloc).construct(dest, tmp);
				return (dest);
			}
			void del_node(Node<T>* node)
			{
				node_alloc(_alloc).destroy(node);
				node_alloc(_alloc).deallocate(node, 1);
				node = nullptr;
			}

		public:
			typedef T																value_type;
			typedef Alloc														allocator_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			typedef ListIterator<T>									iterator;
			typedef ListIterator<const T>						const_iterator;
			typedef ReverseIterator<iterator>				reverse_iterator;
			typedef ReverseIterator<const_iterator>	const_reverse_iterator;
			typedef std::ptrdiff_t 									difference_type;
			typedef size_t 													size_type;

			// explicit List(const allocator_type& alloc = allocator_type());
			// explicit List(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			// template <class InputIterator>
			// List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

			explicit List(const allocator_type& alloc = allocator_type())
			: _head(nullptr), _tail(nullptr), _size(0), _alloc(alloc)
			{
				_tail = dup_node(nullptr, nullptr, 0);
				_head = _tail;
			};
			explicit List(size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type())
			: _head(nullptr), _tail(nullptr), _size(0), _alloc(alloc)
			{
				_tail = dup_node(nullptr, nullptr, 0);
				_head = _tail;
				//n 개의 컨테이너를 val 값으로 채운다.
				insert(end(), (size_type)n, val);
			};
			template <class InputIterator>
			List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			: _head(nullptr), _tail(nullptr), _size(0), _alloc(alloc)
			{
				_tail = dup_node(nullptr, nullptr, 0);
				_head = _tail;
				//input iterator라 처음과 끝사이에 있는 값들이 채워짐
				insert(end(), first, last);
			};
			~List()
			{
				// if (_size)
				// 	clear();
				// if (_tail)
				// 	del_node(_tail);
			};
			List(const List& copy): _head(nullptr), _tail(nullptr), _size(0)
			{
				*this = copy;
			};
			List& operator=(const List& other)
			{
				_alloc = other._alloc;
				if (_size != 0)
					clear();
				if (!_tail)
				{
					_tail = dup_node(nullptr, nullptr, 0);
					// _tail = new Node<T>();
					// _tail->next = nullptr;
					// _tail->prev = nullptr;
					// _tail->data = 0;
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
				if (_size)
					clear();
				insert(end(), first, last);
			};
			void assign (size_type n, const value_type& val)
			{
				if (_size)
					clear();
				insert(end(), n, val);
			};

			void push_front (const value_type& val)
			{
				Node<T> *new_node;
				new_node = dup_node(nullptr, _head, val);
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
				del_node(tmp);
				--_size;
			};

			void push_back (const value_type& val)
			{
				Node<T> *new_node;
				new_node = dup_node(_tail->prev, _tail, val);
				if (_size != 0)
					_tail->prev->next = new_node;
				else
					_head = new_node;
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
				// if (tmp == _head)
				// 	_head = _tail;
				// else
				// 	tmp->prev->next = _tail;
				if (tmp->prev != nullptr)
					tmp->prev->next = _tail;
				else
					_head = _tail;
				del_node(tmp);
				--_size;
			};

			iterator insert (iterator position, const value_type& val)
			{
				insert(position, (size_type)1, val);
				return (position.getPtr()->prev);
			};

    	void insert (iterator position, size_type n, const value_type& val)
			{
				//n개만큼 노드 삽입하는데 그것의 값들은 val
				size_type i = 0;
				if (position == begin()) //|| position.getPtr() == nullptr)
				{
					push_front(val);
					++i;
				}
				if (_size == 0)
				{
					push_back(val);
					++i;
				}
				Node<T> *tmp;
				tmp = position.getPtr()->prev;
				while (i < n)
				{
					Node<T> *new_node;
					new_node = dup_node(tmp, tmp->next, val);
					tmp->next = new_node;
					new_node->next->prev = new_node;
					++_size;
					tmp = new_node;
					++i;
				}
			};

			template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last)
			{
				InputIterator it;
				it = first;
				if (position == begin())
				{
					push_front(*it);
					++it;
				}
				if (_size == 0)
				{
					push_back(*it);
					++it;
				}
				Node<T> *tmp;
				tmp = position.getPtr()->prev;
				while (it != last)
				{
					Node<T> *new_node;
					new_node = dup_node(tmp, tmp->next, *it);
					tmp->next = new_node;
					new_node->next->prev = new_node;
					++_size;
					tmp = new_node;
					++it;
				}
			};

			iterator erase (iterator position)
			{
				//position에 있는 걸 지우고 그 다음꺼를 return?
				if (position == begin())
				{
					pop_front();
					return (begin());
				}
				if (position == end())
					return (end());
				Node<T> *tmp = position.getPtr();
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				del_node(tmp);
				--_size;
				return (tmp->next);
			};

			iterator erase (iterator first, iterator last)
			{

				Node<T> *tmp = first.getPtr();
				iterator it = first;
				while (it != last)
				{
					if (tmp == _head)
						_head = tmp->next;
					else
						tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					del_node(tmp);
					--_size;
					tmp = it.getPtr();
					++it;
				}
				return (tmp);

			};

			void swap (List& x)
			{
				std::swap(_head, x._head);
				std::swap(_tail, x._tail);
				std::swap(_size, x._size);
			};

			void resize (size_type n, value_type val = value_type())
			{
				while(n < _size)
					pop_back();
				while(_size < n)
					push_back(val);
			};

			void clear()
			{
				erase(begin(), end());
			};

			/* operations */
			void splice (iterator position, List& x)
			{
				insert(position, x.begin(), x.end());
				x.clear();
			};

			void splice (iterator position, List& x, iterator i)
			{
				insert(position, *i);
				x.erase(i);
			};

			void splice (iterator position, List& x, iterator first, iterator last)
			{
				insert(position, first, last);
				x.erase(first, last);
			};

			void remove (const value_type& val)
			{
				iterator it = begin();
				while (it != end())
				{
					if (*it == val)
						it = erase(it);
					else
						++it;
				}
			};

			template <class Predicate>
  		void remove_if (Predicate pred)
			{
				iterator it = begin();
				while (it != end())
				{
					if (pred(*it))
						it = erase(it);
					else
						++it;
				}
			};

			void unique()
			{
				for(iterator first = begin(); first != end(); ++first)
				{
					iterator next = first;
					next++;
					for (;next != end(); ++next)
					{
						if (*first == *next)
							erase(next);
					}
				}
			};

			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred)
			{
				for(iterator first = begin(); first != end(); ++first)
				{
					iterator next = first;
					next++;
					for (;next != end(); ++next)
					{
						if (binary_pred(*first, *next))
							erase(next);
					}
				}
			};

			void merge (List& x)
			{
				if (&x == this)
					return ;
				for (iterator it = x.begin(); it != x.end(); it++)
					push_back(*it);
				sort();
				x.clear();
			};

			template <class Compare>
  		void merge (List& x, Compare comp)
			{
				if (&x == this)
					return ;
				for (iterator it = x.begin(); it != x.end(); it++)
					push_back(*it);
				sort(comp);
				x.clear();
			};

			void sort()
			{
				for(iterator first = begin(); first != end(); ++first)
				{
					iterator next = first;
					next++;
					for (;next != end(); ++next)
					{
						if (*first > *next)
							std::swap(*first, *next);
					}
				}
			};

			template <class Compare>
			void sort (Compare comp)
			{
				for(iterator first = begin(); first != end(); ++first)
				{
					iterator next = first;
					next++;
					for (;next != end(); ++next)
					{
						if (!comp(*first, *next))
							std::swap(*first, *next);
					}
				}
			};

			void reverse()
			{
				iterator first = begin();
				iterator last = end();
				for (size_type i = 0; i < (_size / 2); ++i)
				{
					std::swap(first, last);
					++first;
					--last;
				}
			};
	};

	/**/
	/* Non-member function overloads */
	/**/
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
}

#endif
