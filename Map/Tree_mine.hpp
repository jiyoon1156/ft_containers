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
				while (node)
				{
					tmp_parent = node;
					if (node->data.first > data.first)
						node = node->left;
					else if (node->data.first < data.first)
						node = node->right;
					else
						throw std::range_error("same key exist");
				}
				node = create_node(data, nullptr, nullptr, tmp_parent);
				//값 넣어주기
				if (!tmp_parent && !_root)
					_root = node;
				else
				{
					if (tmp_parent->data.first > data.first)
						tmp_parent->left = node;
					else
						tmp_parent->right = node;
					node->parent = tmp_parent;
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
					tmp = min(node->right);
					node = create_node(tmp->data, node->left, node->right, node->parent);
					remove_node(tmp);
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
			Node<pair>*	begin() const
			{
				return (_head);
			}
			Node<pair>*	end() const
			{
				return (_tail);
			}
			Node<pair>*	root()
			{
				return (_root);
			}

			Node<pair>*	insert(Node<pair>* node, const pair& data)
			{
				node = insert_node(node, data);
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
