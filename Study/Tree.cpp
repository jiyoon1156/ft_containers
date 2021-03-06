#include "Tree.hpp"

int main()
{
	ft::BSTree<int>* BST = new ft::BSTree<int>();
	BST->AddNode(1);
	BST->AddNode(3);
	BST->AddNode(6);
	BST->AddNode(9);
	BST->AddNode(13);
	BST->AddNode(22);
	BST->AddNode(17);
	BST->AddNode(10);
	BST->AddNode(0);

	BST->Display(); std::cout << std::endl;
	BST->SearchData(4);
	BST->SearchData(17);

	std::cout << std::endl;
	BST->RemoveNode(17);
	BST->RemoveNode(9);
	BST->RemoveNode(6);
	BST->RemoveNode(3);
	BST->Display(); std::cout << std::endl;

	std::cout << "===================" << std::endl;
	std::cout << "Begin is " << BST->begin()->data << std::endl;
	std::cout << "End is " <<BST->end()->data<< std::endl;
	std::cout << "Root is " <<BST->Root()->data<< std::endl;
	return 0;
}
