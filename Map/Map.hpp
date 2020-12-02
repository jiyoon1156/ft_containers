#ifndef MAP_HPP
# define MAP_HPP

#include "Tree_mine.hpp"

namespace ft
{

	template <class pair>//, class Category = bidirectional_iterator_tag>
	class MapIterator : public iterator<bidirectional_iterator_tag, pair>
	{
		private:
			Node<pair>*	_ptr;
			Node<pair>*	_tail;
		public:
			MapIterator(void) : _ptr(nullptr), _tail(nullptr) {}
			virtual ~MapIterator() {}
			MapIterator(Node<pair>* ptr, Node<pair>* tail) : _ptr(ptr), _tail(tail) {}
			MapIterator(const MapIterator& copy) { *this = copy; }
			MapIterator&	operator=(const MapIterator& other)
			{
				_ptr = other._ptr;
				_tail = other._tail;
				return (*this);
			}
			MapIterator&	operator++(void)
			{
				//successor
				if (_ptr == _tail)
					_ptr = nullptr;
				else if (_ptr->right)
				{
					_ptr = _ptr->right;
					while (_ptr->left)
						_ptr = _ptr->left;
				}
				else
				{
					Node<pair>*	tmp = _ptr;
					_ptr = _ptr->parent;
					while (_ptr->left != tmp)
					{
						tmp = _ptr;
						_ptr = _ptr->parent;
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
				//predecessor
				if (_ptr == nullptr)
					_ptr = _tail;
				else if (_ptr->left)
				{
					_ptr = _ptr->left;
					while (_ptr->right)
						_ptr = _ptr->right;
				}
				else
				{
					Node<pair>*	tmp = _ptr;
					_ptr = _ptr->parent;
					while (_ptr->right != tmp)
					{
						tmp = _ptr;
						_ptr = _ptr->parent;
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
				return (_ptr == other._ptr);
			}
			bool	operator!=(const MapIterator &other) const
			{
				return (_ptr != other._ptr);
			}
			pair&	operator*(void)
			{
				return (_ptr->data);
			}
			pair*	operator->(void)
			{
				return (&(_ptr->data));
			}
			Node<pair>*	getPtr(void)
			{
				return (_ptr);
			}
	};

	template <class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<std::pair<const Key,T> > >
	class Map
	{
		private:
			size_t	_size;
			Compare	_comp;
			Alloc	_alloc;
			BSTree<Key, T, Compare, Alloc>	_tree;
		public:
			typedef	Key									key_type;
			typedef	T									mapped_type;
			typedef std::pair<const key_type, mapped_type>	value_type;
			typedef Compare								key_compare;
			class 	value_compare
			{
					friend class Map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef Alloc								allocator_type;
			typedef typename Alloc::reference			reference;
			typedef typename Alloc::const_reference		const_reference;
			typedef typename Alloc::pointer				pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			typedef MapIterator<value_type> 		iterator;
			typedef MapIterator<value_type>		const_iterator;
			typedef ReverseIterator<iterator>			reverse_iterator;
			typedef ReverseIterator<const_iterator>	const_reverse_iterator;
			typedef std::ptrdiff_t						difference_type;
			typedef size_t								size_type;

			explicit Map(const key_compare& comp = key_compare(),
            	const allocator_type& alloc = allocator_type())
			: _size(0), _comp(comp), _alloc(alloc), _tree(comp, alloc) {}
			template <class InputIterator>
			Map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: _size(0), _comp(comp), _alloc(alloc), _tree(comp, alloc)
			{
				insert(first, last);
			}
			Map(const Map& x)
			: _size(0), _comp(x._comp), _alloc(x._alloc), _tree(x._comp, x._alloc)
			{
				*this = x;
			}
			~Map()
			{
				clear();
			}
			Map& operator=(const Map& x)
			{
				clear();
				_comp = x._comp;
				_alloc = x._alloc;

				insert(x.begin(), x.end());
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
			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(end()));
			}
			reverse_iterator		rend(void)
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const
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
				// value_type = (k, mapped_type())인 새로운 쌍
				std::pair<iterator, bool> ret = insert(std::make_pair(k, mapped_type()));
				return (ret.first->second);
			}

			std::pair<iterator,bool> insert(const value_type& val)
			{
				Node<value_type>*	node =_tree.find(val.first);
				if (node) //만들어야할 것이 이미 존재하므로 false
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
				// std::cout << "here erase\n";
				if ((node = _tree.find(k)))
				{
					_tree.erase(node);
					// --_size;
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
				return (find(k) != end());
			}
			iterator lower_bound(const key_type& k)
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
			iterator upper_bound(const key_type& k)
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
