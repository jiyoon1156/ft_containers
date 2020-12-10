#ifndef DEQUE_HPP
#define DEQUE_HPP
#include  "List.hpp"
#include <exception>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class Deque
	{
		private:
			List<T, Alloc> _list;
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

			explicit Deque() : _list()
			{};
			explicit Deque(size_type n, const value_type& val = value_type()) : _list(n, val)
			{};
			template <class InputIterator>
			Deque(InputIterator first, InputIterator last): _list(first, last)
			{};
			Deque(const Deque& x): _list(x._list)
			{};
			Deque& operator=(const Deque &copy)
			{
				_list = copy._list;
				return (*this);
			}
			iterator 		begin(void)
			{
				return (_list.begin());
			}
			const_iterator 		begin(void) const
			{
				return (_list.begin());
			}
			iterator 		end(void)
			{
				return (_list.end());
			}
			const_iterator	end(void) const
			{
				return (_list.end());
			}
			reverse_iterator 		rbegin(void)
			{
				return (_list.rbegin());
			}
			const_reverse_iterator	rbegin(void) const
			{
				return (_list.rbegin());
			}
			reverse_iterator 		rend(void)
			{
				return (_list.rend());
			}
			const_reverse_iterator	rend(void) const
			{
				return (_list.rend());
			}
			size_type size() const
			{
				return (_list.size());
			}
			size_type max_size() const
			{
				return (_list.max_size());
			}
			void	resize (size_type n, value_type val = value_type())
			{
				_list.resize(n, val);
			}
			bool	empty() const
			{
				return (_list.empty());
			}
			reference operator[] (size_type n)
			{
				iterator pos = _list.begin();
				while (n)
				{
					++pos;
					--n;
				}
				return (pos.getPtr()->data);
			}
			const_reference operator[] (size_type n) const
			{
				iterator pos = _list.begin();
				while (n)
				{
					++pos;
					--n;
				}
				return (pos.getPtr()->data);
			}
			reference front()
			{
				return (_list.front());
			}
			reference at (size_type n)
			{
				if (n >= _list.size())
					throw std::out_of_range("out of range");
				iterator pos = _list.begin();
				while (n)
				{
					++pos;
					--n;
				}
				return (pos.getPtr()->data);
			}
			const_reference at (size_type n) const
			{
				if (n >= _list.size())
					throw std::out_of_range("out of range");
				iterator pos = _list.begin();
				while (n)
				{
					++pos;
					--n;
				}
				return (pos.getPtr()->data);
			}
			const_reference front() const
			{
				return (_list.front());
			}
			reference			back(void)
			{
				return (_list.back());
			}

			const_reference		back(void) const
			{
				return (_list.back());
			}
			template <typename InputIt>
			void assign(InputIt first, InputIt last)
			{
				_list.assign(first, last);
			}
			void assign(size_type n, const value_type& val)
			{
				_list.assign(n, val);
			}
			void push_back (const value_type& val)
			{
				_list.push_back(val);
			}
			void push_front (const value_type& val)
			{
				_list.push_front(val);
			}
			void pop_back()
			{
				_list.pop_back();
			}
			void pop_front()
			{
				_list.pop_front();
			}
			iterator insert (iterator position, const value_type& val)
			{
				_list.insert(position, val);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				_list.insert(position, n, val);
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				_list.insert(position, first, last);
			}
			iterator erase (iterator position)
			{
				_list.erase(position);
			}
			iterator erase (iterator first, iterator last)
			{
				_list.erase(first, last);
			}
			void swap (Deque& x)
			{
				_list.swap(x._list);
			}
			void clear()
			{
				_list.clear();
			}

			friend bool operator== (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
			{
				return (lhs._list == rhs._list);
			}
			friend bool operator!= (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
			{
				return (lhs._list != rhs._list);
			}

			friend bool operator> (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
			{
				return (lhs._list > rhs._list);
			}

			friend bool operator< (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
			{
				return (lhs._list < rhs._list);
			}
	};
	template <class T, class Alloc>
	bool operator>= (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator<= (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}

	template <class T, class Alloc>
  void swap (Deque<T, Alloc>& x, Deque<T, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
