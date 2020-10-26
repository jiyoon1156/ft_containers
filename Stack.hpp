/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:16:00 by jhur              #+#    #+#             */
/*   Updated: 2020/10/26 18:36:49 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

template <typename T>
class Stack{
	T *buf;
	int top;
	int size;

	public:
		Stack(int s);
		virtual ~Stack();
		int back();
		int stack_size();
		// bool full() const;
		bool empty() const;
		void push(const T &a);
		void push(T&& a);
		T&& pop();
};

#endif
