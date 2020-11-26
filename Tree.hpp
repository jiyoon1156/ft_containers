#ifndef TREE_HPP
# define TREE_HPP
#include <iostream>

namespace ft
{
	template <typename T>
	struct Node
	{
		Node *left;
		Node *right;
		T data;
	};

	template <typename T>
	class BSTree
	{
		private:
			Node<T> *root;

			void Inorder(Node<T> *current)
			{
				if (current)
				{
					Inorder(current->left);
					std::cout << current->data << " ";
					Inorder(current->right);
				}
			}

			Node<T>* SearchMinNode(Node<T> *node)
			{
				if (!node)
					return (NULL);
				while (node->left)
				{
					node = node->left;
				}
				return (node);
			}

			Node<T>* SearchMaxNode(Node<T> *node)
			{
				if (!node)
					return (NULL);
				while (node->right)
				{
					node = node->right;
				}
				return (node);
			}

			Node<T> *RemoveSequence(Node<T> *node, T data)
			{
				if (node == nullptr)
					return node;
				else if (node->data > data)
					node->left = RemoveSequence(node->left, data);
				else if (node->data < data)
					node->right = RemoveSequence(node->right, data);
				else
				{
					Node<T>* ptr = node;
					//자식이없을떄
					if (node->right==nullptr && node->left==nullptr)
					{
						delete node;
						node = nullptr;
					}
					//자식이 하나일떄
					else if (node->right == nullptr)
					{
						node = node->left;
						delete ptr;
					}
					else if (node->left == nullptr)
					{
						node = node->right;
						delete ptr;
					}
					//자식이 두개일떄 :: 왼쪽 노드중 가장큰값 찾아 부모노드로 바꾸기
					else
					{
						ptr = SearchMaxNode(node->left);
						node->data = ptr->data;
						node->left = RemoveSequence(node->left, ptr->data);
					}
				}
				return node;
			};
		public:
			BSTree(): root(nullptr) {};
			// BSTree(){};
			~BSTree(){};
			void AddNode(T data);
			bool SearchData(T data);
			void RemoveNode(T data);
			void Display();
			void begin();
			void end();
	};

	template <typename T>
	void BSTree<T>::RemoveNode(T data)
	{
		Node<T>* ptr = root;
		RemoveSequence(ptr, data);
	}

	template<typename T>
	void BSTree<T>::Display()
	{
		Inorder(root);
	}

	template <typename T>
	bool BSTree<T>::SearchData(T data)
	{
		Node<T>* ptr = root;

		while (ptr!=nullptr)
		{
			if (ptr->data == data)
			{
				std::cout << data << " 값을 찾았습니다." << std::endl;
				return true;
			}
			else if (ptr->data > data)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
		std::cout << data << " 값을 찾지 못했습니다." << std::endl;
		return false;
	}

	template <typename T>
	void BSTree<T>::AddNode(T data)
	{
		Node<T>* node = new Node<T>();
		Node<T>* tmpRoot = nullptr;

		node->data = data;

		if (root == nullptr)
			root = node;
		else
		{
			Node<T>* ptr = root;

			while (ptr != nullptr)
			{
				tmpRoot = ptr;
				if (node->data < ptr->data)
				{
					ptr = ptr->left;
				}
				else
				{
					ptr = ptr->right;
				}
			}
			//넣을 위치에 대입
			if (node->data < tmpRoot->data )
				tmpRoot->left = node;
			else
				tmpRoot->right = node;
		}
	}
}

# endif
