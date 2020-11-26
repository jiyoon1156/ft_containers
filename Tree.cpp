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
	BST->AddNode(2);

	BST->Display(); std::cout << std::endl;
	BST->SearchData(4);
	BST->SearchData(17);

	std::cout << std::endl;
	BST->RemoveNode(17);
	BST->RemoveNode(9);
	BST->RemoveNode(6);
	BST->RemoveNode(3);
	BST->Display(); std::cout << std::endl;
	return 0;
}
