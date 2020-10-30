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
			/*
			Node<T> *getPtr(void)
			{
				return (_ptr);
			}
			*/
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

			explicit List(const allocator_type& alloc = allocator_type())
			{

			};
			explicit List(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{

			};
			template <class InputIterator>
			List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			{

			};
			~List(){};
			List(const List& copy)
			{
				*this = copy;
			};
			List& operator=(const List& other)
			{

			};
			/* iterators */
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			const_iterator cbegin() const noexcept;
			const_iterator cend() const noexcept;
			const_reverse_iterator crbegin() const noexcept;
			const_reverse_iterator crend() const noexcept;
			/* capacity */
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			/* element access */
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			/* modifiers */
			template <class InputIterator>
  		void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val);
			template <class... Args>
  		void emplace_front (Args&&... args);
			void push_front (const value_type& val);
			void pop_back();
			template <class... Args>
  		iterator emplace (const_iterator position, Args&&... args);
			iterator insert (iterator position, const value_type& val);
    	void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last);
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			void swap (list& x);
			void resize (size_type n, value_type val = value_type());
			void clear();
			/* operations */
			void splice (iterator position, list& x);
			void splice (iterator position, list& x, iterator i);
			void splice (iterator position, list& x, iterator first, iterator last);
			void remove (const value_type& val);
			template <class Predicate>
  		void remove_if (Predicate pred);
			void unique();
			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred);
			void merge (list& x);
			template <class Compare>
  		void merge (list& x, Compare comp);
			void sort();
			template <class Compare>
			void sort (Compare comp);
			void reverse();
			/* observers */
			allocator_type get_allocator() const;
			/**/
			/* Non-member function overloads */
			/**/
			template <class T, class Alloc>
			bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

			template <class T, class Alloc>
			bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

			template <class T, class Alloc>
			bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

			template <class T, class Alloc>
			bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

			template <class T, class Alloc>
			bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

			template <class T, class Alloc>
			bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

			template <class T, class Alloc>
  		void swap (list<T,Alloc>& x, list<T,Alloc>& y);
	};
}

#endif
