#ifndef BSTREE_HPP
# define BSTREE_HPP
#include <iostream>
#include <utility>

namespace ft
{
	template <class Key, class T>
	struct Node
	{
		Node *left;
		Node *right;
		pair<Key, T> data;

		Node(pair<Key, T> data, Node* left, Node* right): data(data), left(left), right(right){}
	};

	template <class Key, class T>
	class BSTree
	{
		private:
			typedef std::pair<const Key, T> pair;
			Node<pair> *_root;

			void Inorder(Node<pair> *current)
			{
				if (current)
				{
					Inorder(current->left);
					std::cout << current->data << " ";
					Inorder(current->right);
				}
			}

			Node<pair>* SearchMinNode(Node<pair> *node)
			{
				if (!node)
					return (NULL);
				while (node->left)
				{
					node = node->left;
				}
				return (node);
			}

			Node<pair>* SearchMaxNode(Node<pair> *node)
			{
				if (!node)
					return (NULL);
				while (node->right)
				{
					node = node->right;
				}
				return (node);
			}

			Node<pair> *RemoveSequence(Node<pair> *node, T data)
			{
				if (node == nullptr)
					return node;
				else if (node->data > data)
					node->left = RemoveSequence(node->left, data);
				else if (node->data < data)
					node->right = RemoveSequence(node->right, data);
				else
				{
					Node<pair>* ptr = node;
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
			BSTree(): _root(nullptr){};
			BSTree(const BSTree &cp): _root(nullptr)
			{
				*this = cp;
			}
			BSTree& operator=(const BSTree &other)
			{
				_root = other._root;
				return (*this);
			}
			~BSTree(){};
			void AddNode(T data);
			bool SearchData(T data);
			void RemoveNode(T data);
			void Display()
			{
				Inorder(_root);
			};
			Node<pair> *begin()
			{
				Node<pair>* ptr = _root;
				return (SearchMinNode(ptr));
			};
			Node<pair> *end()
			{
				Node<pair>* ptr = _root;
				return (SearchMaxNode(ptr));
			};
			Node<pair> *root()
			{
				return (_root);
			};
			Node<pair>* insert(Node<pair> *node, const pair& data)
			{
				Node<pair>* tmp_root = nullptr;

				node->data = data;

				if (_root == nullptr)
					_root = node;
				else
				{
					Node<pair>* ptr = _root;

					while (ptr != nullptr)
					{
						tmp_root = ptr;
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
					if (node->data < tmp_root->data )
						tmp_root->left = node;
					else
						tmp_root->right = node;
					return (node);
				}
			}
			void erase(Node<pair>* node)
			{
				(void)node;
				// RemoveSequence(node)
			}
			Node<pair>* find(const Key& k) const
			{
				Node<pair>* ptr = _root;

				while (ptr!=nullptr)
				{
					if (ptr->data.first == k)
					{
						std::cout << ptr->data.first << " 값을 찾았습니다." << std::endl;
						return (ptr);
					}
					else if (ptr->data.first > k)
						ptr = ptr->left;
					else
						ptr = ptr->right;
				}
				std::cout << ptr->data.first << " 값을 찾지 못했습니다." << std::endl;
				return (nullptr);
			}
	};

	// template <typename T>
	// void BSTree<T>::RemoveNode(T data)
	// {
	// 	Node<pair>* ptr = _root;
	// 	RemoveSequence(ptr, data);
	// }

}

# endif
