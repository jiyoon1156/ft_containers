#ifndef MAP_HPP
# define MAP_HPP

#include "BSTree.hpp"

namespace ft
{

	template <class pair, class Category = bidirectional_iterator_tag>
	class MapIterator : public iterator<bidirectional_iterator_tag, pair>
	{
		private:
			Node<pair>*	_node;
			Node<pair>*	_tail;
		public:
			MapIterator(void) : _node(nullptr), _tail(nullptr) {}
			virtual ~MapIterator() {}
			MapIterator(Node<pair>* node, Node<pair>* tail) : _node(node), _tail(tail) {}
			MapIterator(const MapIterator& copy) { *this = copy; }
			MapIterator&	operator=(const MapIterator& other)
			{
				_node = other._node;
				_tail = other._tail;
				return (*this);
			}
			MapIterator&	operator++(void)
			{
				if (_node == _tail)
					_node = nullptr;
				else if (_node->right)
				{
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
				}
				else
				{
					Node<pair>*	tmp = _node;
					_node = _node->parent;
					while (_node->left != tmp) //node->left != tmp이면 반복문 계속 수행
					{
						tmp = _node;
						_node = _node->parent;
					}
				}
				return (*this);
			}
			MapIterator	operator++(int)
			{
				MapIterator	tmp(*this);
				operator++();
				return (tmp);
			}
			MapIterator&	operator--(void)
			{
				if (_node == nullptr)
					_node = _tail;
				else if (_node->left)
				{
					_node = _node->left;
					while (_node->right)
						_node = _node->right;
				}
				else
				{
					Node<pair>*	tmp = _node;
					_node = _node->parent;
					while (_node->right != tmp)
					{
						tmp = _node;
						_node = _node->parent;
					}
				}
				return (*this);
			}
			MapIterator	operator--(int)
			{
				MapIterator	tmp(*this);
				operator--();
				return (tmp);
			}
			bool	operator==(const MapIterator &other) const
			{
				return (_node == other._node);
			}
			bool	operator!=(const MapIterator &other) const
			{
				return (_node != other._node);
			}
			pair&	operator*(void)
			{
				return (_node->data);
			}
			pair*	operator->(void)
			{
				return (&(_node->data));
			}
			Node<pair>*	getPtr(void)
			{
				return (_node);
			}
	};

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class Map
	{
		private:
			size_t													_size;
			Compare													_comp;
			Alloc														_alloc;
			BSTree<Key, T, Compare, Alloc>	_tree;
		public:
			typedef	Key																			key_type;
			typedef	T																				mapped_type;
			typedef std::pair<const key_type, mapped_type>	value_type;
			typedef Compare																	key_compare;
			class 	value_compare
			{
					friend class Map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool				result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef Alloc														allocator_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			typedef MapIterator<value_type> 				iterator;
			typedef MapIterator<value_type>					const_iterator;
			typedef ReverseIterator<iterator>				reverse_iterator;
			typedef ReverseIterator<const_iterator>	const_reverse_iterator;
			typedef std::ptrdiff_t									difference_type;
			typedef size_t													size_type;

			explicit Map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _size(0), _comp(comp), _alloc(alloc), _tree(comp, alloc) {}
			template <class InputIterator>
			Map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _size(0), _comp(comp), _alloc(alloc), _tree(comp, alloc)
			{
				insert(first, last);
			}
			Map(const Map& copy)
			: _size(0), _comp(copy._comp), _alloc(copy._alloc), _tree(copy._comp, copy._alloc)
			{
				*this = copy;
			}
			~Map()
			{
				clear();
			}
			Map& operator=(const Map& other)
			{
				clear();
				_comp = other._comp;
				_alloc = other._alloc;
				insert(other.begin(), other.end());
				return (*this);
			}
			iterator				begin(void)
			{
				return (iterator(_tree.begin(), _tree.end()));
			}
			const_iterator			begin(void) const
			{
				return (const_iterator(_tree.begin(), _tree.end()));
			}
			iterator				end(void)
			{
				return (iterator(nullptr, _tree.end()));
			}
			const_iterator			end(void) const
			{
				return (const_iterator(nullptr, _tree.end()));
			}
			reverse_iterator		rbegin(void)
			{
				return (reverse_iterator(end()));
			}
			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(end()));
			}
			reverse_iterator		rend(void)
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend(void) const
			{
				return (const_reverse_iterator(begin()));
			}
			bool		empty(void) const
			{
				return (_size == 0);
			}
			size_type	size(void) const
			{
				return (_size);
			}
			size_type	max_size(void) const
			{
				return (std::numeric_limits<size_type>::max()/sizeof(Node<value_type>));
			}

			mapped_type&	operator[] (const key_type& k)
			{
				std::pair<iterator, bool> res = insert(std::make_pair(k, mapped_type()));
				return (res.first->second);
			}

			std::pair<iterator,bool> insert(const value_type& val)
			{
				Node<value_type>*	node =_tree.find(val.first);
				if (node)
					return (std::make_pair(iterator(node, _tree.end()), false));
				node = _tree.insert(_tree.root(), val);
				++_size;
				return (std::make_pair(iterator(node, _tree.end()), true));
			}
			iterator	insert(iterator position, const value_type& val)
			{
				Node<value_type>*	node = position.getPtr();
				node = _tree.insert(node, val);
				++_size;
				return (iterator(node, _tree.end()));
			}
			template <class InputIterator>
			void		insert(InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
				{
					_tree.insert(_tree.root(), *first);
					++_size;
				}
			}
			void		erase(iterator position)
			{
				Node<value_type>*	node = position.getPtr();
				_tree.erase(node);
				--_size;
			}
			size_type	erase(const key_type& k)
			{
				Node<value_type>*	node;
				if ((node = _tree.find(k)))
				{
					_tree.erase(node);
					--_size;
					return (1);
				}
				return (0);
			}
			void		erase(iterator first, iterator last)
			{
				iterator it = first;
				key_type key, tmp, last_key;

				if (last != end())
					last_key = last->first;
				else
					last_key = 0;
				if (first != last)
					key = first->first;
				else
					return ;
				while (key != last_key && it != last)
				{
					++it;
					if (it != end())
						tmp = it->first;
					else
						tmp = 0;
					erase(key);
					it = find(tmp);
					key = tmp;
				}
			}
			void		swap(Map& x)
			{
				std::swap(_tree, x._tree);
				std::swap(_size, x._size);
				std::swap(_comp, x._comp);
				std::swap(_alloc, x._alloc);
			}
			void		clear()
			{
				erase(begin(), end());
			}

			key_compare key_comp() const
			{
				//returns the same as operator<
				return (_comp);
			}
			value_compare value_comp() const
			{
				return (value_compare(_comp));
			}

			iterator find(const key_type& k)
			{
				return (iterator(_tree.find(k), _tree.end()));
			}
			const_iterator find(const key_type& k) const
			{
				return (const_iterator(_tree.find(k), _tree.end()));
			}
			size_type count(const key_type& k) const
			{
				//return 1 (if the element is found) or zero (otherwise).
				return (find(k) != end());
			}
			iterator lower_bound(const key_type& k) //k랑 같은값 있으면 k 지목
			{
				iterator it = begin();
				while (it != end())
				{
					if (_comp(it->first, k) <= 0)
						return (it);
					++it;
				}
				return (end());
			}
			const_iterator lower_bound(const key_type& k) const
			{
				const_iterator it = begin();
				while (it != end())
				{
					if (_comp(it->first, k) <= 0)
						return (it);
					++it;
				}
				return (end());
			}
			iterator upper_bound(const key_type& k)// k랑 같은 값있으면 k보다 하나 더 큰거 지목
			{
				iterator it = begin();
				while (it != end())
				{
					if (_comp(it->first, k) <=0 && it->first != k)
						return (it);
					++it;
				}
				return (end());
			}
			const_iterator upper_bound(const key_type& k) const
			{
				const_iterator it = begin();
				while (it != end())
				{
					if (_comp(it->first, k) <=0 && it->first != k)
						return (it);
					++it;
				}
				return (end());
			}
			//Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
			std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{
				return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}
			std::pair<iterator,iterator>             equal_range(const key_type& k)
			{
				return (std::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}
	};

}

#endif
