#ifndef TREE_HPP
# define TREE_HPP

namespace ft
{
	template <class pair>
	struct Node
	{
		Node *parent;
		Node *left;
		Node *right;
		pair data;

		Node(Node *parent, Node *left, Node *right, pair data)
		: parent(parent), left(left), right(right), data(data) {}
	};

	template<class Key, class T, class Compare, class Alloc>
	class BSTree
	{
		private:
		public:
	};
}

# endif
