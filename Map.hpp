#ifndef MAP_HPP
# define MAP_HPP

#include "Iterator.hpp"
#include <iostream>

namespace ft
{
	template <class T>
	class MapIterator: public iterator<bidrectional_iterator_tag, T>
	{
		private:

		public:
			MapIterator(){}
			virtual ~MapIterator(){}
			MapIterator(const MapIterator& other)
			{
				*this = other;
			}
			MapIterator&	operator=(const MapIterator& other){}
			MapIterator&	operator++(void){}
			MapIterator	operator++(int){}
			MapIterator&	operator--(void){}
			MapIterator	operator--(int){}
			bool	operator==(const MapIterator &other) const{}
			bool	operator!=(const MapIterator &other) const{}

	};
	template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
           >
	class Map
	{
		private:

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
	};
}

#endif
