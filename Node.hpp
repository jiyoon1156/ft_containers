#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <cstddef> //ptrdiff_t
#include <memory>
#include <limits> //max size
#include <string>

namespace ft
{
	template <typename T>
	struct Node
	{
		Node<T> *prev;
		Node<T> *next;
		T data;
	};
}

#endif
