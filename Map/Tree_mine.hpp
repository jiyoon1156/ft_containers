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
				node_alloc(_alloc).destroy(*node);
				node_alloc(_alloc).deallocate(*node, 1);
				*node = 0;
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
			Node<pair>*	begin()
			{
				Node<pair> *min = _root;

				while(min && min->left)
					min = min->left;
				_head = min;
				return (_head);
			}
			Node<pair>*	end()
			{
				Node<pair> *max = _root;

				while (max && max->right)
					max = max->right;
				_tail = max;
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
				// insert_fixup(node);
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
