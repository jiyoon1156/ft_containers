#include "Queue.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=====constructor==========" << std::endl;
	ft::List<int> mylist ((size_t)2,200);

	ft::Queue<int> first;
	ft::Queue<int,ft::List<int> > third; // empty queue with list as underlying container
	ft::Queue<int,ft::List<int> > fourth (mylist);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';

	std::cout << "=====empty==========" << std::endl;
	ft::Queue<int> myqueue;
	int sum (0);

	for (int i=1;i<=10;i++) myqueue.push(i);

	while (!myqueue.empty())
	{
		sum += myqueue.front(); // 1
		myqueue.pop();
	}

	std::cout << "total: " << sum << '\n';

	std::cout << "=====size==========" << std::endl;
	ft::Queue<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';

	std::cout << "=====front and back==========" << std::endl;
	ft::Queue<int> q1;

	q1.push(77);
	q1.push(16); // 77 16

	q1.front() -= q1.back();    // 77-16=61

	std::cout << "q1.front() is now " << q1.front() << '\n';

	ft::Queue<int> q2;

	q2.push(12);
	q2.push(75);   // this is now the back 12 75

	q2.back() -= q2.front(); // 75-12=63

	std::cout << "q2.back() is now " << q2.back() << '\n';

	std::cout << "=====push and pop==========" << std::endl;
	ft::Queue<int> q3;
	int myint;

	std::cout << "Please enter some integers (enter 0 to end):\n";

	do {
	std::cin >> myint;
	q3.push (myint);
	} while (myint);

	std::cout << "q3 contains: ";
	while (!q3.empty())
	{
	std::cout << ' ' << q3.front();
	q3.pop();
	}
	std::cout << '\n';
	std::cout << "===========relational operators===========" << std::endl;

	if (q1 == q2)
		std::cout << "q1 == q2" << std::endl;
	if (q1 != q2)
		std::cout << "q1 != q2" << std::endl;
	if (q1 >= q2)
		std::cout << "q1 >= q2" << std::endl;
	if (q1 <= q2)
		std::cout << "q1 <= q2" << std::endl;
	if (q1 > q2)
		std::cout << "q1 >= q2" << std::endl;
	if (q1 < q2)
		std::cout << "q1 <= q2" << std::endl;

	std::cout << "===============================" << std::endl;
	return (0);
}
