#include "Stack.hpp"

int main()
{
	Stack <int> si(50);

	si.push(5);
	si.push(10);
	std::cout << "INT STACK: ";
	while (!si.empty())
		std::cout << si.pop() << " ";
	std::cout << std::endl;
}
