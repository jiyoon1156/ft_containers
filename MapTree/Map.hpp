#ifndef MAP_HPP
#define MAP_HPP

#include "../Iterator.hpp"
#include <iostream>
#include <utility>
namespace ft
{
	template <class Key, class T>
	struct BinaryTreeMap
	{
		BinaryTreeMap		*parent;
		BinaryTreeMap		*left;
		BinaryTreeMap		*right;
		std::pair<Key,T>	pair;
		// size_t				left_height;
		// size_t				right_height;
	};

	template <class Key, class T, class Category = bidirectional_iterator_tag>
	class MapIterator
	{
		private:
		/* Lock to compile error on use */
		MapIterator					operator+(const MapIterator &rhs) const;
		MapIterator					operator+(int n) const;
		MapIterator					operator-(const MapIterator &rhs) const;
		MapIterator					operator-(int n) const;
		bool						operator<(const MapIterator &rhs) const;
		bool						operator>(const MapIterator &rhs) const;
		bool						operator<=(const MapIterator &rhs) const;
		bool						operator>=(const MapIterator &rhs) const;
		MapIterator					&operator+=(int n) const;
		MapIterator					&operator-=(int n) const;
		// T							&operator[](int n) const;

	protected:
		BinaryTreeMap<Key, T>			*ptr;

	public:

	/* ********************************************************************** */
	/*   Member types                                                         */
	/* ********************************************************************** */

		typedef T								value_type;
		typedef T								&reference;
		typedef T								*pointer;
		typedef Category						category;
		typedef std::ptrdiff_t					difference_type;

	/* ********************************************************************** */
	/*   Member functions                                                     */
	/* ********************************************************************** */

		/* Coplien Form */
		MapIterator(void) {}

		~MapIterator(void) {}

		MapIterator(const MapIterator &it)
		{
			std::cout << "copy iter\n";
			*this = it;
		}

		MapIterator				&operator=(const MapIterator &rhs)
		{
			std::cout << "iterator operator???\n";
			this->ptr = rhs.ptr;
			return (*this);
		}


		MapIterator(BinaryTreeMap<Key, T> *map)
		{
			this->ptr = map;
		}

		MapIterator				&operator++(void)
		{
			BinaryTreeMap<Key, T> *next;

			if (!this->ptr)
				return (*this);
			if (!this->ptr->right)
			{
				next = this->ptr;
				while (next->parent && next == next->parent->right)
					next = next->parent;
				next = next->parent;
			}
			else
			{
				next = this->ptr->right;
				while (next->left)
					next = next->left;
			}
			this->ptr = next;
			return (*this);
		}

		MapIterator				operator++(int)
		{
			MapIterator tmp(*this);
			this->operator++();
			return (tmp);
		}

		MapIterator				&operator--(void)
		{
			BinaryTreeMap<Key, T> *next;

			if (!this->ptr->left)
			{
				next = this->ptr;
				while (next->parent && next == next->parent->left)
					next = next->parent;
				next = next->parent;
			}
			else
			{
				next = this->ptr->left;
				while (next->right)
					next = next->right;
			}
			this->ptr = next;
			return (*this);
		}

		MapIterator				operator--(int)
		{
			MapIterator tmp(*this);
			this->operator--();
			return (tmp);
		}

  	bool						operator==(const MapIterator &rhs) const
		{
			return (this->ptr == rhs.ptr);
		}

  	bool						operator!=(const MapIterator &rhs) const
		{
			return (this->ptr != rhs.ptr);
		}

		std::pair<Key, T>			&operator*(void) // dereferenced lvalue
		{
			return (this->ptr->pair);
		}

		std::pair<Key, T>			*operator->(void) // dereferenced rvalue
		{
			return (&this->ptr->pair);
		}

		BinaryTreeMap<Key, T>			*getPtr(void)
		{
			return (this->ptr);
		}
	};

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class Map
	{

		public:

	/* ********************************************************************** */
	/*   Member types                                                         */
	/* ********************************************************************** */

		typedef Key												key_type;
		typedef T												mapped_type;
		typedef std::pair<const key_type, mapped_type>			value_type;
		typedef std::less<key_type>								key_compare;
		typedef Alloc											allocator_type;
		typedef T												&reference;
		typedef const T											&const_reference;
		typedef	T												*pointer;
		typedef	const T											*const_pointer;
		typedef ft::MapIterator<Key, T>							iterator;
		typedef typename ft::MapIterator<Key, T>::difference_type	difference_type;
		typedef size_t											size_type;


	/* ********************************************************************** */
	/* references:                                                            */
	/* https://www.cplusplus.com/reference/map/map/value_comp                 */
	/* ********************************************************************** */

		class value_compare
		{

		// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;

		protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		private:
			allocator_type				alloc;
			key_compare					comp;
			BinaryTreeMap<Key, T>		*root;
			// BinaryTreeMap<Key, T>		*_start;
			// BinaryTreeMap<Key, T>		*_end;
			// size_type					length;
		// void add_node()
		// {

		// }

		public:
			explicit Map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			:root(nullptr)
			{
				std::cout << "생성자\n";
				this->comp = comp;
				this->alloc = alloc;
				// this->_start = new BinaryTreeMap<Key, T>();
				// this->_start->left = NULL;
				// this->_start->right = NULL;
				// this->_end = new BinaryTreeMap<Key, T>();
				// this->_end->left = this->_start;
				// this->_start->parent = this->_end;
				// this->_end->right = NULL;
				// this->_end->parent = NULL;
				// this->root = this->_end;
				std::cout << "생성자끝\n";
			}
			~Map(){};
			Map(const Map &map):root(nullptr)
			{

				// this->_start = new BinaryTreeMap<Key, T>();
				// this->_start->left = NULL;
				// this->_start->right = NULL;
				// this->_end = new BinaryTreeMap<Key, T>();
				// this->_end->left = this->_start;
				// this->_start->parent = this->_end;
				// this->_end->right = NULL;
				// this->_end->parent = NULL;
				// this->root = this->_end;
				*this = map;
			}
			Map						&operator=(const Map &map)
			{
				// this->clear();
				std::cout << "operator=\n";
				this->comp = map.comp;
				this->alloc = map.alloc;
				this->insert(map.begin(), map.end());
				return (*this);
			}
			// template <class InputIterator>
			// Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			// {

			// }
			iterator begin()
			{
				BinaryTreeMap<Key, T>		*node;

				node = this->root;
				while (node->left)
					node = node->left;
				return (iterator(node));
			}
			iterator end()
			{
				BinaryTreeMap<Key, T> *node;
				node = this->root;
				while (node->right)
					node = node->right;
				return (iterator(node));
			}
			mapped_type				&operator[](const key_type &k)
			{
				std::cout << "operator[]\n";
				// BinaryTreeMap<Key, T>	*node;

				// node = this->root;
				// while (node)
				// {
				// 	if (k == node->pair.first)
				// 		return (node->pair.second);
				// 	if (this->comp(k, node->pair.first))
				// 	{
				// 		if (node->left)
				// 			node = node->left;
				// 		else
				// 			insert(iterator(node), value_type(k, 0));
				// 	}
				// 	else
				// 	{
				// 		if (node->right)
				// 			node = node->right;
				// 		else
				// 			insert(iterator(node), value_type(k, 0));
				// 	}
				// }
				// std::cout << k << std::endl;
				// insert(value_type(k, 0));
				// std::cout << "=================\n";
				// std::cout <<"pair first " <<this->root->pair.first << std::endl;
				// std::cout <<"pair second "<<this->root->pair.second<< std::endl;
				// std::cout <<"pair second "<<this->root<< std::endl;
				// std::cout << "=================\n";
				// return (this->root->pair.second);
				std::pair<iterator, bool> ret = insert(std::make_pair(k, mapped_type()));
				return (ret.first->second);
			}
			std::pair<iterator, bool>	insert(const value_type &val)
			{
				Node<value_type>*	node =_tree.find(val.first);
				if (node) //만들어야할 것이 이미 존재하므로 false
					return (std::make_pair(iterator(node, _tree.end()), false));
				node = _tree.insert(_tree.root(), val);
				++_size;
				return (std::make_pair(iterator(node, _tree.end()), true));
			}

			iterator				insert(iterator position, const value_type &val)
			{
				iterator it;
				BinaryTreeMap<Key, T> *node = new BinaryTreeMap<Key, T>();
				BinaryTreeMap<Key, T> *tmp_root = nullptr;

				it = find(val.first);//val.first
				if (it != this->end())
					return (it);
				node->pair = val;
				if (this->root == nullptr)
					this->root = node;
				else
				{
					BinaryTreeMap<Key, T> *ptr = this->root;

					while (ptr != nullptr)
					{
						tmp_root = ptr;
						if (node->pair < ptr->pair)
						{
							ptr = ptr->left;
						}
						else
						{
							ptr = ptr->right;
						}
					}
					//넣을 위치에 대입
					if (node->pair < tmp_root->pair )
						tmp_root->left = node;
					else
						tmp_root->right = node;
				}
				return (iterator(node));
			}
			template <class InputIterator>
			void					insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}
			iterator find(const key_type &k)
			{
				BinaryTreeMap<Key, T> *ptr = this->root;

				while (ptr!=nullptr)
				{
					if (ptr->pair.first == k)
					{
						// std::cout << ptr->pair.first << " 값을 찾았습니다." << std::endl;
						return (iterator(ptr));
					}
					else if (ptr->pair.first > k)
						ptr = ptr->left;
					else
						ptr = ptr->right;
				}
				// std::cout << ptr->pair.first << " 값을 찾지 못했습니다." << std::endl;
				return (iterator(nullptr));
			}
	};
}

#endif
