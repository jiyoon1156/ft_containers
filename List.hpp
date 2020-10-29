#ifndef LIST_HPP
#define LIST_HPP

#include "Node.hpp"

namespace ft{
	/*								 *						  				 */
	/* iterator template parameters : category */
	/*								 *											 */
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

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
}

#endif
