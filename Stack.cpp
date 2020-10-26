/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:16:04 by jhur              #+#    #+#             */
/*   Updated: 2020/10/26 18:36:33 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"

template <typename T> Stack <T>::Stack(int s):size(s), top(s)
{
	buf = new T[s];
}

template <typename T> Stack<T>::~Stack()
{
	delete[] buf;
}

template <typename T> int Stack<T>::back()
{
	return top;
}

template <typename T> int Stack<T>::stack_size()
{
	return size;
}

// template <typename T> bool Stack<T>::full() const
// {
// 	return !top;
// }

template <typename T> bool Stack<T>::empty() const
{
	return top == size;
}

template <typename T> void Stack<T>::push(const T& a)
{
	buf[--top] = a;
}

template <typename T> void Stack<T>::push(T&& a)
{
	buf[--top] = move(a);
}

template <typename T> T&& Stack<T>::pop()
{
	return move(buf[top++]);
}
