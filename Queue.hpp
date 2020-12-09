#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "List.hpp"

namespace ft
{
	template <class T, class Container = List<T> >
	class Queue
	{
		private:
			Container _container;
		public:
			typedef T					value_type;
			typedef Container container_type;
			typedef size_t		size_type;

		explicit Queue(const container_type& ctnr = container_type()): _container(ctnr){}
		Queue(const Queue& copy) : _container(copy) {};
		Queue& operator=(const Queue& Queue)
		{
			if (this == &Queue)
				return (*this);
			this->container_ = Queue.container_;
			return (*this);
		}
		~Queue() {};
		bool empty() const
		{
			return (_container.empty());
		}
		size_type size() const
		{
			return (_container.size());
		}
		value_type& front()
		{
			return (_container.front());
		}
		const value_type& front() const
		{
			return (_container.front());
		}
		value_type& back()
		{
			return (_container.back());
		}
		const value_type& back() const
		{
			return (_container.back());
		}
		void push(const value_type& val)
		{
			_container.push_back(val);
		}
		void pop()
		{
			_container.pop_front();
		}
		friend bool operator== (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
		{
			return (lhs._container == rhs._container);
		}
		friend bool operator!= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
		{
			return (!(lhs._container == rhs._container));
		}
		friend bool operator<  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
		{
			return (lhs._container < rhs._container);
		}
		friend bool operator<= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
		{
			return (!(lhs._container > rhs._container));
		}
		friend bool operator>  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
		{
			return (lhs._container > rhs._container);
		}
		friend bool operator>= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
		{
			return (!(lhs._container < rhs._container));
		}
	};
}

#endif
