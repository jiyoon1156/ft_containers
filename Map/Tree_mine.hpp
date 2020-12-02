#ifndef TREE_MINE_HPP
# define TREE_MINE_HPP

#include "../Iterator.hpp"
# include <cstddef>
# include <memory>
# include <iostream>
# include <limits>
# include <exception>
# include <utility>
# include <functional>

namespace ft
{
	template<class pair>
	struct  Node
	{
		pair		data;
		Node*		left;
		Node*		right;
		Node*		parent;

		Node(pair data, Node* left, Node* right, Node* parent)
		: data(data), left(left), right(right), parent(parent) {}
	};

	template<class Key, class T, class Compare, class Alloc>
	class	BSTree
	{
		private:
			typedef std::pair<const Key, T>	pair;
			typedef typename Alloc::template rebind<Node<pair> >::other node_alloc;

			Node<pair>*	_root;
			Node<pair>*	_head;//최소
			Node<pair>*	_tail;//최대

			Compare	_comp;
			Alloc	_alloc;

			BSTree();
			Node<pair>*	create_node(pair data, Node<pair>* left, Node<pair>* right, Node<pair>* parent)
			{
				Node<pair>	tmp(data, left, right, parent);
				Node<pair>*	new_node;

				new_node = node_alloc(_alloc).allocate(1);
				node_alloc(_alloc).construct(new_node, tmp);
				return (new_node);
			}
			void		delete_node(Node<pair>** node)
			{
				if (node)
				{
					node_alloc(_alloc).destroy(*node);
					node_alloc(_alloc).deallocate(*node, 1);
					*node = 0;
				}
			}

			Node<pair>*	insert_node(Node<pair>* node, const std::pair<const Key, T> &data)
			{
				Node<pair>*	tmp_parent = nullptr;
				//위치 잡아주기
				while (node != nullptr)
				{
					tmp_parent = node;
					if (_comp(data.first, node->data.first))
						node = node->left;
					else if (_comp(node->data.first, data.first))
						node = node->right;
					// std::cout << "111" << std::endl;
				}
				node = create_node(data, nullptr, nullptr, tmp_parent);
				//값 넣어주기
				if (tmp_parent == nullptr && _root == nullptr)
				{
					_root = node;
					// std::cout << "222" << std::endl;
				}
				else
				{
					if (_comp(data.first, tmp_parent->data.first))
						tmp_parent->left = node;
					else
					{
						tmp_parent->right = node;
						// std::cout << "right" << std::endl;
					}
					node->parent = tmp_parent;
					// std::cout << "333" << std::endl;
				}
				return (node);
			}
			void	remove_node(Node<pair>* node)
			{
				Node<pair>* tmp;
				//자식이 두개
				//오른쪽 자식중에 가장 작은값을 삭제노드 위치에 올린다. 가장 작은값은 자식이 1개 혹은 0개임.
			  //오른쪽자식 최솟값이 리프일 경우 걍 삭제, 1개일 경우 duplicate하고 그 오른쪽 자식 삭제
				if (node->left && node->right)
				{
					Node<pair>*	new_node;
					tmp = min(node->right); // 원래 노드와 교체할 노드
					//node 자리에 새 노드
					new_node = create_node(tmp->data, node->left, node->right, node->parent);
					if (node->parent == nullptr)
						_root = new_node;
					else if (node->parent->right == node)
						node->parent->right = new_node;
					else
						node->parent->left = new_node;
					node->left->parent = new_node;
					node->right->parent = new_node;
					delete_node(&node);
					node = tmp;
				}
				tmp = node->left ? node->left : node->right;
				//자식이 한개일때
				if (tmp != nullptr)
				{
					tmp->parent = node->parent;
					if (node->parent == nullptr)
						_root = tmp;
					else if (node->parent->right == node)
						node->parent->right = tmp;
					else
						node->parent->left = tmp;
				}
				if (tmp == nullptr)
				{
					if (node->parent == nullptr)
						_root = nullptr;
					else if (node->parent->right == node)
						node->parent->right = tmp;
					else
						node->parent->left = tmp;
				}
				delete_node(&node);
				_head = min(_root);
				_tail = max(_root);
			}
			// void	remove_node(Node<pair>* node)
			// {
			// 	Node<pair> *child = NULL;
			// 	Node<pair> *grandp = NULL;
			// 	if (node == nullptr)
			// 		return ;
			// 	else if (node->left == nullptr && node->right == nullptr)//자식이 없는경우
			// 	{
			// 		// std::cout << "no child here" << std::endl;
			// 		delete_node(&node);
			// 	}
			// 	else if (node->left == nullptr) //자식이 하나
			// 	{
			// 		// std::cout << "only one right child" << std::endl;
			// 		child = node->right;
			// 		grandp = node->parent;
			// 		child->parent = grandp;
			// 		std::cout << "seg1";
			// 		if (grandp == nullptr)
			// 		{
			// 			std::cout << "seg?";
			// 			_root = node->right;
			// 		}
			// 		else //if (grandp->right == node)
			// 			grandp->right = child;
			// 		delete_node(&node);
			// 	}
			// 	else if (node->right == nullptr)
			// 	{
			// 		child = node->left;
			// 		grandp = node->parent;
			// 		child->parent = grandp;
			// 		if (grandp == nullptr)
			// 			_root = node->left;
			// 		else
			// 			grandp->left = child;
			// 		delete_node(&node);
			// 	}
			// 	//오른쪽 자식중에 가장 작은값을 삭제노드 위치에 올린다. 가장 작은값은 자식이 1개 혹은 0개임.
			// 	//오른쪽자식 최솟값이 리프일 경우 걍 삭제, 1개일 경우 duplicate하고 그 오른쪽 자식 삭제
			// 	else if (node->left && node->right)//자식이 두개
			// 	{
			// 		Node<pair>* tmp;
			// 		Node<pair>* copy_node;
			// 		tmp = min(node->right);
			// 		//tmp 복사해서 node에 넣어준다음에 remove_node(tmp) 해주면 되지 않을까?

			// 		copy_node = create_node(tmp->data, node->left, node->right, node->parent);
			// 		if (node->parent == nullptr)
			// 			_root = copy_node;
			// 		else if (node->parent->right == node)
			// 			node->parent->right = copy_node;
			// 		else
			// 			node->parent->left = copy_node;
			// 		node->left->parent = copy_node;
			// 		node->right->parent = copy_node;
			// 		remove_node(tmp);
			// 		// delete_node(&node);
			// 		// node = tmp;
			// 	}
			// }
		public:
			BSTree(const Compare& comp, const Alloc& alloc)
			: _root(nullptr), _head(nullptr), _tail(nullptr), _comp(comp), _alloc(alloc) {}
			~BSTree(){}
			BSTree(const BSTree &copy)
			: _root(nullptr), _head(nullptr), _tail(nullptr) { *this = copy; }
			BSTree&	operator=(const BSTree &x)
			{
				_root = x._root;
				_head = x._head;
				_tail = x._tail;
				_comp = x._comp;
				_alloc = x._alloc;
				return (*this);
			}
			Node<pair>* min(Node<pair> *node)
			{
				while(node && node->left)
					node = node->left;
				return (node);
			}
			Node<pair>* max(Node<pair> *node)
			{
				while(node && node->right)
					node = node->right;
				return (node);
			}
			Node<pair>*	begin()
			{
				return (_head);
			}
			Node<pair>*	end()
			{
				return (_tail);
			}
			Node<pair>*	root()
			{
				return (_root);
			}

			Node<pair>*	insert(Node<pair>* node, const pair& data)
			{
				// std::cout << data.first << " " << data.second << " " << std::endl;
				node = insert_node(node, data);
				// std::cout << node->data.first << " " << node->data.second << " " << std::endl;
				if ((_head && _comp(data.first, _head->data.first)) || !_head)
					_head = node;
				if ((_tail && _comp(_tail->data.first, data.first)) || !_tail)
					_tail = node;
				return (node);
			}

			void		erase(Node<pair>* node)
			{
				remove_node(node);
			}

			Node<pair>*	find(const Key& k) const
			{
				Node<pair>* node = _root;

				while (node)
				{
					if (k == node->data.first) //값 찾음
						return (node);
					else if (_comp(k, node->data.first)) //data.first > k
						node = node->left;
					else
						node = node->right;
				}
				return (nullptr); // 값 못찾음
			}
	};


}


#endif
