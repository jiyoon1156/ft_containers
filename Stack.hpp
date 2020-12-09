#ifndef STACK_HPP
#define STACK_HPP
#include "List.hpp"

namespace ft
{
	template <class T, class Container = List<T> >
	class Stack
	{
		private:
			Container _container;
		public:
			typedef T					value_type;
			typedef Container container_type;
			typedef size_t		size_type;

		explicit Stack(const container_type& ctnr = container_type()): _container(ctnr){}
		Stack(const Stack& copy) : _container(copy) {};
		Stack& operator=(const Stack& stack)
		{
			if (this == &stack)
				return (*this);
			this->container_ = stack.container_;
			return (*this);
		}
		~Stack() {};
		bool empty() const
		{
			return (_container.empty());
		}
		size_type size() const
		{
			return (_container.size());
		}
		value_type& top()
		{
			return (_container.back());
		}
		const value_type& top() const
		{
			return (_container.back());
		}
		void push(const value_type& val)
		{
			_container.push_back(val);
		}
		void pop()
		{
			_container.pop_back();
		}
		friend bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs._container == rhs._container);
		}
		friend bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (!(lhs._container == rhs._container));
		}
		friend bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs._container < rhs._container);
		}
		friend bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (!(lhs._container > rhs._container));
		}
		friend bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs._container > rhs._container);
		}
		friend bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (!(lhs._container < rhs._container));
		}
	};
}
#endif
