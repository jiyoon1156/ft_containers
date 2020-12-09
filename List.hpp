#ifndef LIST_HPP
# define LIST_HPP

#include "Iterator.hpp"
#include "Node.hpp"

namespace ft
{
	template <class T>
	class ListIterator : public iterator<bidirectional_iterator_tag, T>
	{
		private:
			Node<T>*	_ptr;
		public:
			ListIterator(void) : _ptr(nullptr) {}
			virtual ~ListIterator(void) {}
			ListIterator(Node<T>* ptr) : _ptr(ptr) {}
			ListIterator(const ListIterator& other)
			{
				*this = other;
			}
			ListIterator&	operator=(const ListIterator& other)
			{
				_ptr = other._ptr;
				return (*this);
			}
			ListIterator&	operator++(void)
			{
				if (_ptr && _ptr->next)
					_ptr = _ptr->next;
				return (*this);
			}
			ListIterator	operator++(int)
			{
				ListIterator	tmp(*this);
				operator++();
				return (tmp);
			}
			ListIterator&	operator--(void)
			{
				if (_ptr && _ptr->prev)
					_ptr = _ptr->prev;
				return (*this);
			}
			ListIterator	operator--(int)
			{
				ListIterator	tmp(*this);
				operator--();
				return (tmp);
			}
			bool	operator==(const ListIterator &other) const
			{
				return (_ptr == other._ptr);
			}
			bool	operator!=(const ListIterator &other) const
			{
				return (_ptr != other._ptr);
			}
			T&	operator*(void)
			{
				return (_ptr->data);
			}
			T*	operator->(void)
			{
				return (&(_ptr->data));
			}
			Node<T>	*getPtr(void)
			{
				return (_ptr);
			}
	};

	template <typename T, typename Alloc = std::allocator<T> >
	class List
	{
		private:
			typedef typename Alloc::template rebind<Node<T> >::other node_alloc;

			Node<T>*	_head;
			Node<T>*	_tail;
			size_t		_size;
			Alloc		_alloc;

			Node<T>*	dup_node(Node<T>* prev, Node<T>* next, T data)
			{
				Node<T>	tmp;
				Node<T>	*new_node;

				tmp.prev = prev;
				tmp.next = next;
				tmp.data = data;
				new_node = node_alloc(_alloc).allocate(1);
				node_alloc(_alloc).construct(new_node, tmp);
				return (new_node);
			}
			void		del_node(Node<T>* node)
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
			typedef std::ptrdiff_t									difference_type;
			typedef size_t													size_type;

			explicit List(const allocator_type& alloc = allocator_type())
			: _head(nullptr), _tail(nullptr), _size(0), _alloc(alloc)
			{
				_tail = dup_node(nullptr, nullptr, 0);
				_head = _tail;
			}
			explicit List(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _head(nullptr), _tail(nullptr), _size(0), _alloc(alloc)
			{
				_tail = dup_node(nullptr, nullptr, 0);
				_head = _tail;
				insert(end(), (size_type)n, val);
			}
			template <class InputIterator>
			List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			: _head(nullptr), _tail(nullptr), _size(0), _alloc(alloc)
			{
				_tail = dup_node(nullptr, nullptr, 0);
				_head = _tail;
				insert(end(), first, last);
			}
			List(const List& other)
			: _head(nullptr), _tail(nullptr), _size(0)
			{
				*this = other;
			}
			~List(void)
			{
				// if (_size)
				// 	clear();
				// if (_tail)
				// 	del_node(_tail);
			}
			List&	operator=(const List<T>& other)
			{
				_alloc = other._alloc;
				if (_size != 0)
					clear();
				if (!_tail)
				{
					_tail = dup_node(nullptr, nullptr, 0);
					_head = _tail;
				}
				if (other._size)
					insert(end(), other.begin(), other.end());
				return (*this);
			};
			/* iterators */
			iterator				begin(void)
			{
				return (iterator(_head));
			}
			const_iterator			begin(void) const
			{
				return (const_iterator((Node<const T>*)_head));
			}
			iterator				end(void)
			{
				return (iterator(_tail));
			}
			const_iterator			end(void) const
			{
				return (const_iterator((Node<const T>*)_tail));
			}
			reverse_iterator		rbegin(void)
			{
				return (reverse_iterator(end()));
			}
			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(end()));
			}
			reverse_iterator		rend(void)
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}
			/* capacity */
			bool	empty(void) const
			{
				//size 0 이면 true 아니면 false
				return (_size == 0);
			}
			size_type	size(void) const
			{
				return (_size);
			}
			size_type	max_size(void) const
			{
				return (std::numeric_limits<T>::max() / sizeof(Node<T>));
			}
			/* element access */
			reference	front(void)
			{
				return (_head->data);
			}
			const_reference	front(void) const
			{
				return (_head->data);
			}
			reference	back(void)
			{
				return (_tail->prev->data);
			}
			const_reference	back(void) const
			{
				return (_tail->prev->data);
			}
			/* modifiers */
			template <class InputIterator>
 			void	assign(InputIterator first, InputIterator last)
			{
				if (_size)
					clear();
				insert(end(), first, last);
			}
			void	assign(size_type n, const value_type& val)
			{
				if (_size)
					clear();
				insert(end(), n, val);
			}
			void	push_front(const value_type& val)
			{
				Node<T>	*node;
				node = dup_node(nullptr, _head, val);
				_head->prev = node;
				_head = node;
				++_size;
			}
			void	pop_front()
			{
				if (_head == _tail)
					return ;
				Node<T> *tmp;
				tmp = _head;
				_head = _head->next;
				del_node(tmp);
				--_size;
			}
			void	push_back(const value_type& val)
			{
				Node<T> *new_node;
				new_node = dup_node(_tail->prev, _tail, val);
				if (_size == 0)
					_head = new_node;
				else
					_tail->prev->next = new_node;
				_tail->prev = new_node;
				++_size;
			}
			void	pop_back()
			{
				if (_head == _tail)
					return ;
				Node<T> *node_del;
				node_del = _tail->prev;
				_tail->prev = node_del->prev;
				if (node_del->prev)
					node_del->prev->next = _tail;
				else
					_head = _tail;
				del_node(node_del);
				--_size;
			}
			iterator insert(iterator position, const value_type& val)
			{
				insert(position, (std::size_t)1, val);
				return (position.getPtr()->prev);
			}
			void	insert(iterator position, size_type n, const value_type& val)
			{
				size_type i = 0;
				if (_size == 0)
				{
					push_back(val);
					++i;
				}
				if (position == begin())
				{
					push_front(val);
					++i;
				}
				Node<T> *pos;
				pos = position.getPtr();
				for (;i < n;++i)
				{
					Node<T> *new_node;
					new_node = dup_node(pos->prev, pos, val);
					pos->prev->next = new_node;
					pos->prev = new_node;
					pos = new_node->next;
					++_size;
				}
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last)
			{
				InputIterator it = first;
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
				Node<T> *pos;
				pos = position.getPtr();
				for (;it != last;++it)
				{
					Node<T> *new_node;
					new_node = dup_node(pos->prev, pos, *it);
					pos->prev->next = new_node;
					pos->prev = new_node;
					pos = new_node->next;
					++_size;
				}
			}
			iterator erase(iterator position)
			{
				if (position == begin())
				{
					pop_front();
					return (begin());
				}
				if (position == end())
					return (end());
				Node<T> *pos, *ret;
				pos = position.getPtr();
				ret = pos->next;
				ret->prev = pos->prev;
				pos->prev->next = ret;
				del_node(pos);
				--_size;
				return (ret);
			}
			iterator erase(iterator first, iterator last)
			{
				Node<T>	*pos = first.getPtr();
				iterator it = first;
				it++;
				while (it != last)
				{
					if (pos == _head)
						_head = pos->next;
					else
						pos->prev->next = pos->next;
					pos->next->prev = pos->prev;
					del_node(pos);
					pos = it.getPtr();
					--_size;
					it++;
				}
				return (pos);

			}
			void swap(List& x)
			{
				std::swap(_head, x._head);
				std::swap(_tail, x._tail);
				std::swap(_size, x._size);
			}
			void resize(size_type n, value_type val = value_type())
			{
				while (_size > n)
					pop_back();
				while (_size < n)
					push_back(val);
			}
			void clear()
			{
				erase(begin(), end());
			}
			void splice(iterator position, List& x)
			{
				Node<T>*	pos = position.getPtr();

				if (position == begin())
					_head = x._head;
				else
				{
					x._head->prev = pos->prev;
					pos->prev->next = x._head;
				}
				pos->prev = x._tail->prev;
				x._tail->prev->next = pos;
				_size += x._size;

				x._tail->prev = nullptr;
				x._head = x._tail;
				x._size = 0;
			}
			void splice(iterator position, List& x, iterator i)
			{
				Node<T>*	pos = position.getPtr();
				Node<T>*	tmp = i.getPtr();

				if (i != x.begin())
					tmp->prev->next = tmp->next;
				else
					x._head = tmp->next;
				tmp->next->prev = tmp->prev;
				--x._size;

				if (position != begin())
					pos->prev->next = tmp;
				else
					_head = tmp;
				tmp->prev = pos->prev;
				pos->prev = tmp;
				tmp->next = pos;
				++_size;
			}
			void splice(iterator position, List& x, iterator first, iterator last)
			{
				Node<T>*	pos = position.getPtr();
				Node<T>*	start = first.getPtr();
				Node<T>*	end = last.getPtr()->prev;

				if (first != x.begin())
					start->prev->next = end->next;
				else
					x._head = end->next;
				end->next->prev = start->prev;

				if (position != begin())
					pos->prev->next = start;
				else
					_head = start;
				start->prev = pos->prev;
				pos->prev = end;
				end->next = pos;

				for (iterator it = first; it != last; ++it)
				{
					_size += 1;
					x._size -= 1;
				}
			}
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
			}
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
			}
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
			}
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
			}
			void merge (List& x)
			{
				if (&x == this)
					return ;
				for (iterator it = x.begin(); it != x.end(); it++)
					push_back(*it);
				sort();
				x.clear();
			}
			template <class Compare>
 			void merge (List& x, Compare comp)
			{
			if (&x == this)
					return ;
				for (iterator it = x.begin(); it != x.end(); it++)
					push_back(*it);
				sort(comp);
				x.clear();
			}
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
			}
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
			}
			void reverse()
			{
				iterator	first = begin();
				iterator	last = end();
				--last;

				for (unsigned int i = 0; i < _size / 2; ++i)
				{
					std::swap(*first, *last);
					++first;
					--last;
				}
			}
    };

	template <class T, class Alloc>
	bool operator== (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);

		typename List<T, Alloc>::const_iterator	l_it = lhs.begin();
		typename List<T, Alloc>::const_iterator	r_it = rhs.begin();
		for (unsigned int i = 0; i < lhs.size(); ++i)
		{
			if (*l_it != *r_it)
				return (false);
			++l_it;
			++r_it;
		}
		return (true);
	}
	template <class T, class Alloc>
	bool operator!= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator<  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		typename List<T, Alloc>::const_iterator	l_it = lhs.begin();
		typename List<T, Alloc>::const_iterator	r_it = rhs.begin();
		for (; (l_it != lhs.end()) && (r_it != rhs.end()); ++l_it, ++r_it)
		{
			if (*l_it < *r_it)
				return (true);
			if (*r_it < *l_it)
				return (false);
		}
		return (l_it == lhs.end() && r_it != rhs.end());
	}
	template <class T, class Alloc>
	bool operator<= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Alloc>
 	bool operator>  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
	template <class T, class Alloc>
	void swap (List<T,Alloc>& x, List<T,Alloc>& y)
	{
		x.swap(y);
	}
};




#endif
