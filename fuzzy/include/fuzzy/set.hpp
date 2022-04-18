//  Copyright (c) 2018, Ben McCart
//  Boost Software License - Version 1.0 - August 17th, 2003
//
//  Permission is hereby granted, free of charge, to any person or organization
//  obtaining a copy of the software and accompanying documentation covered by
//  this license (the "Software") to use, reproduce, display, distribute,
//  execute, and transmit the Software, and to prepare derivative works of the
//  Software, and to permit third-parties to whom the Software is furnished to
//  do so, all subject to the following:
//
//  The copyright notices in the Software and this entire statement, including
//  the above license grant, this restriction and the following disclaimer,
//  must be included in all copies of the Software, in whole or in part, and
//  all derivative works of the Software, unless such copies or derivative
//  works are solely in the form of machine-executable object code generated by
//  a source language processor.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//  FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#ifndef FUZZY_COLLECTION_HPP
#define FUZZY_COLLECTION_HPP

#include <algorithm>
#include <cassert>
#include <vector>

#include <fuzzy/element.hpp>

namespace fuzzy
{
	/** 
	* basic_set is an associative container that contains an ordered set of unique basic_elements.  It is
	* largely an analog to std::set with the addition of a membership(key_type) function that determines the membership for
	* a specific key, using linear interpolation if the key is between elements.  By default it is implemented using a
	* std::vector as a default storage contianer as sets are expected to remain relatively small for the overwelming majory of
	* use cases. Alternate storage container types (with custom allocators) may be used for constrained environments.
	*/
	template <class V, class M, class Container = std::vector<basic_element<V,M>>>
	requires std::integral<V> && std::floating_point<M>
	class basic_set
	{
	public:
		using container_type = Container;
		using self_type = basic_set<V, M, Container>;
		using key_type = V;
		using element_type = basic_element<V, M>;
		using membership_type = M;
		using value_type = element_type;
		using container_type = container_type;
		using size_type = typename container_type::size_type;
		using difference_type = typename container_type::difference_type;
		using key_compare = std::less<key_type>;
		using value_compare = std::less<element_type>;
		using allocator_type = typename container_type::allocator_type;
		using reference = element_type&;
		using const_reference = element_type const&;
		using pointer = typename container_type::pointer;
		using const_pointer = typename container_type::const_pointer;
		using iterator = typename container_type::iterator;
		using const_iterator = typename container_type::const_iterator;
		using reverse_iterator = typename container_type::reverse_iterator;
		using const_reverse_iterator = typename container_type::const_reverse_iterator;

		constexpr explicit basic_set(allocator_type const& = allocator_type());

		template <class InputIt>
		constexpr basic_set(InputIt, InputIt, allocator_type const& = allocator_type());

		/** Copy constructor.  Constructs the container with the copy of the contents of other.  Allocator is obtained
		*   by calling std::allocator_traits<allocator_type>::select_on_container_copy_construction(other.get_allocator())
		* @param other The other basic_set to copy.*/
		constexpr basic_set(self_type const&) = default;
		constexpr basic_set(self_type const&, allocator_type const&);

		/** Move constructor.Constructs the container with the contents of other using move semantics. Allocator is
		*   obtained by move - construction from the allocator belonging to other.*/
		constexpr basic_set(self_type&&) = default;
		constexpr basic_set(self_type&&, allocator_type const& = allocator_type());
		constexpr basic_set(std::initializer_list<element_type>, allocator_type const& = allocator_type());

		constexpr self_type& operator=(self_type const&) = default;
		constexpr self_type& operator=(self_type&&) = default;
		constexpr basic_set& operator=(std::initializer_list<element_type>);

		constexpr allocator_type get_allocator() const noexcept(std::is_nothrow_copy_constructible<allocator_type>::value);

		/** Returns an iterator to the first element of the container. If the container is empty, the returned iterator
		*   will be equal to end().
		* @return Iterator to beginning of set if non-empty, iterator to end otherwise. */
		constexpr iterator begin() noexcept                                    { return container_.begin();            }

		/** Returns an iterator to the first element of the container. If the container is empty, the returned iterator
		*   will be equal to end().
		* @return Iterator to beginning of set if non-empty, iterator to end otherwise. */
		constexpr const_iterator begin() const noexcept                        { return container_.begin();            }

		/** Returns an iterator to the first element of the container. If the container is empty, the returned iterator
		*   will be equal to end().
		* @return Iterator to beginning of set if non-empty, iterator to end otherwise. */
		constexpr const_iterator cbegin() const noexcept                       { return container_.cbegin();           }

		/** Returns an iterator to the element following the last element of the container.  This element acts as a
		*   placeholder; attempting to access it results in undefined behavior.
		* @return Iterator to one past the last element of the set. */
		constexpr iterator end() noexcept                                      { return container_.end();              }

		/** Returns an iterator to the element following the last element of the container.  This element acts as a
		*   placeholder; attempting to access it results in undefined behavior.
		* @return Iterator to one past the last element of the set. */
		constexpr const_iterator end() const noexcept                          { return container_.end();              }

		/** Returns an iterator to the element following the last element of the container.  This element acts as a
		*   placeholder; attempting to access it results in undefined behavior.
		* @return Iterator to one past the last element of the set. */
		constexpr const_iterator cend() const noexcept                         { return container_.cend();             }

		/** Returns a reverse iterator to the first element of the reversed container. It corresponds to the last element of the
		*   non-reversed container.
		* @return A reverse iterator to the last element of the set if non-empty, an iterator to rend() otherwise. */
		constexpr reverse_iterator rbegin() noexcept                           { return container_.rbegin();           }

		/** Returns a reverse iterator to the first element of the reversed container. It corresponds to the last element of the
		*   non-reversed container.
		* @return A reverse iterator to the last element of the set if non-empty, an iterator to rend() otherwise. */
		constexpr const_reverse_iterator rbegin() const noexcept               { return container_.rbegin();           }

		/** Returns a reverse iterator to the first element of the reversed container. It corresponds to the last element of the
		*   non-reversed container.
		* @return A reverse iterator to the last element of the set if non-empty, an iterator to rend() otherwise. */
		constexpr const_reverse_iterator crbegin() const noexcept              { return container_.crbegin();          }

		/** Returns a reverse iterator to the element following the last element of the reversed container.It corresponds to the
		*   element preceding the first element of the non - reversed container.This element acts as a placeholder, attempting
		*   to access it results in undefined behavior.
		* @return A reverse iterator to one past the last element of the reversed set. */
		constexpr reverse_iterator rend() noexcept                             { return container_.rend();             }

		/** Returns a reverse iterator to the element following the last element of the reversed container.It corresponds to the
		*   element preceding the first element of the non - reversed container.This element acts as a placeholder, attempting
		*   to access it results in undefined behavior.
		* @return A reverse iterator to one past the last element of the reversed set. */
		constexpr const_reverse_iterator rend() const noexcept                 { return container_.rend();             }

		/** Returns a reverse iterator to the element following the last element of the reversed container.It corresponds to the
		*   element preceding the first element of the non - reversed container.This element acts as a placeholder, attempting
		*   to access it results in undefined behavior.
		* @return A reverse iterator to one past the last element of the reversed set. */
		constexpr const_reverse_iterator crend() const noexcept                { return container_.crend();            }

		/** Checks if the container has no elements. 
		* @return True if the container is empty, false otherwise. */
		constexpr bool empty() const noexcept                                  { return container_.empty();            }

		/** Returns the number of elements in the container.
		* @return The number of elements in the container. */
		constexpr size_type size() const noexcept                              { return container_.size();             }

		/** Returns the maximum number of elements the container is able to hold due to system or library implementation
		*   limitations.
		* @return Maximum number of elements. */
		constexpr size_type max_size() const noexcept                          { return container_.max_size();         }

		/** Removes all elements from the container.  Invalidates any references, pointers, or iterators referring to contained
		*   elements. */
		constexpr void clear() noexcept                                        { container_.clear();                   }

		constexpr std::pair<iterator, bool> insert(element_type);
		constexpr std::pair<iterator, bool> insert(const_iterator, element_type);

		template< class InputIt >
		constexpr void insert(InputIt first, InputIt last);
		constexpr void insert(std::initializer_list<element_type> ilist);

		template <class... Args>
		constexpr std::pair<iterator, bool> emplace(Args&& ...args);

		template <class... Args>
		constexpr std::pair<iterator, bool> emplace_hint(const_iterator, Args&& ...args);
		
		/** Removes the element at pos.
		* @param pos Iterator to the element to remove
		* @return Iterator following the last removed element. */
		constexpr iterator erase(const_iterator pos)                           { return container_.erase(pos);         }

		/** Removes the elements in the range [first, last).
		* @param first Iterator to the first element in the range to remove.
		* @param last Iterator to one past the last element in the range to remove.
		* @return Iterator following the last removed element. */
		constexpr void erase(const_iterator first, const_iterator last)        { container_.erase(first, last);        }
		constexpr bool erase(element_type);
		constexpr bool erase(key_type);

		/** Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations
		*   on individual elements. All iterators and references remain valid. The past-the-end iterator is invalidated.
		* @param other container to exchange the contents with. */
		constexpr void swap(basic_set &other) noexcept                         { container_.swap(other.container_);    }

		/** Returns the number of elements with key that compares equivalent to the specified argument, which is either 1
		*   or 0 since this container does not allow duplicates.
		* @param key - key of the element to count */
		constexpr size_type count(key_type key) const                          { return contains(key) ? 1u : 0u;       }

		/** Returns the number of elements with key that compares equivalent to the specified argument, which is either 1
		*   or 0 since this container does not allow duplicates.
		* @param elem - element to count */
		constexpr size_type count(element_type elem) const                     { return contains(elem) ? 1u : 0u;       }

		constexpr membership_type membership(key_type) const;
		
		constexpr iterator find(key_type);
		constexpr const_iterator find(key_type) const;
		constexpr iterator find(element_type);
		constexpr const_iterator find(element_type) const;

		constexpr bool contains(key_type) const;
		constexpr bool contains(element_type) const;

		constexpr std::pair<iterator, iterator> equal_range(key_type);
		constexpr std::pair<const_iterator, const_iterator> equal_range(key_type) const;
		constexpr std::pair<iterator, iterator> equal_range(element_type);
		constexpr std::pair<const_iterator, const_iterator> equal_range(element_type) const;

		constexpr iterator lower_bound(key_type);
		constexpr const_iterator lower_bound(key_type) const;
		constexpr iterator lower_bound(element_type);
		constexpr const_iterator lower_bound(element_type) const;

		constexpr iterator upper_bound(key_type);
		constexpr const_iterator upper_bound(key_type) const;
		constexpr iterator upper_bound(element_type);
		constexpr const_iterator upper_bound(element_type) const;

	private:

		constexpr membership_type linear_interpolate(element_type, key_type, element_type) const noexcept;

		struct element_less
		{
			constexpr bool operator()(element_type lhs, element_type rhs) const noexcept
			{
				return lhs.value() < rhs.value();
			}
		};

		template <class V2, class M2, class Container2>
		friend key_type operator<=>(self_type const&, self_type const&);

		template <class Predicate>
		friend size_type erase_if(self_type&, Predicate);

		container_type container_;
	};

	/** 
	* Compares the contents of lhs and rhs lexicographically. The comparison is performed as if by calling
	* std::lexicographical_compare_three_way on two sets with a function object performing synthesized three-way
	* comparison
	* @param lhs - 	sets whose contents to compare
	* @param rhs - 	sets whose contents to compare
	*/
	template <class V, class M, class Container>
	constexpr V operator<=>(basic_set<V, M, Container> const& lhs, basic_set<V, M, Container> const& rhs)
	{
		return lhs.container_ <=> rhs.container_;
	}

	/**
	* Erases all elements that satisfy the predicate pred from the set.
	* @param set - set from which to erase
	* @param pred - predicate that returns true if the element should be erased
	* @return The number of erased elements.
	*/
	template <class V, class M, class Container, class Predicate>
	constexpr typename basic_set<V,M,Container>::size_type erase_if(basic_set<V, M, Container> &set, Predicate pred)
	{
		using self_type = basic_set<V, M, Container>;
		using iterator = typename self_type::iterator;
		iterator endi = end(set);
		iterator itr = std::remove_if(begin(set), endi, pred);
		typename self_type::size_type count = endi - itr;
		set.container_.erase(itr, endi);
		return count;
	}

	/** Constructs an empty basic_set using the supplied allocator.
	 * @param alloc - allocator to use for all memory allocations of this container
	 */
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr basic_set<V, M, Container>::basic_set(allocator_type const &alloc)
		: container_(alloc) {}

	/** Range constructor. Constructs the container with the contents of the range [first, last). If multiple
	* elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
	* @param first - first element in the range to copy from.
	* @param last - first element past the range to copy from.
	* @param alloc - allocator to use for all memory allocations of this container
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	template <class InputIt>
	constexpr basic_set<V, M, Container>::basic_set(InputIt first, InputIt last, allocator_type const &alloc)
		: container_(first, last, alloc)
	{
		std::sort(begin(container_), end(container_), element_less{});
	}

	/** Copy constructor.  Constructs the container with the copy of the contents of other.  The supplied allocator
	*   is used.
	* @param other - another container to be used as source to initialize the elements of the container with
	* @param alloc - allocator to use for all memory allocations of this container
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr basic_set<V, M, Container>::basic_set(self_type const &other, allocator_type const &alloc)
		: container_(other.container_, alloc) {}

	/** Move constructor.Constructs the container with the contents of other using move semantics.  The supplied
	*   allocator is used.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr basic_set<V, M, Container>::basic_set(self_type &&other, allocator_type const &alloc)
		: container_(std::move(other.container_), alloc) {}

	/**  Initializer-list constructor. Constructs the container with the contents of the initializer list init. if
	*    multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
	* @param ilist - initializer list to use as data source
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr basic_set<V, M, Container>::basic_set(std::initializer_list<element_type> ilist, allocator_type const &alloc)
		: container_(std::move(ilist), alloc)
	{
		std::sort(std::begin(container_), std::end(container_), element_less{});
	}

	/** 
	* Replaces the contents with those identified by initializer list ilist.
	* @param init - initializer list to use as data source
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr basic_set<V, M, Container>& basic_set<V, M, Container>::operator=(std::initializer_list<element_type> ilist)
	{
		container_ = std::move(ilist);
		std::sort(begin(container_), end(container_), element_less{});

		return *this;
	}

	/**
	* Returns the allocator associated with the container.
	* @return The associated allocator.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::allocator_type basic_set<V, M, Container>::get_allocator() const noexcept(std::is_nothrow_copy_constructible<allocator_type>::value)
	{
		return container_.get_allocator();
	}

	/**
	* Inserts the element.  If the element exists in the set it will not be inserted.
	* @param elem - the element to be inserted.
	* @return A pair containing an interator to the position where the element either was inserted, or would have been inserted if
	*         the same element didn't already exist in the set, and a bool indicating whether the element was successfully inserted.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr std::pair<typename basic_set<V, M, Container>::iterator, bool> basic_set<V, M, Container>::insert(element_type elem)
	{
		iterator itr = lower_bound(elem);
		if (*itr == elem)
		{
			return std::make_pair(itr, false);
		}

		iterator result = container_.insert(itr, elem);
		return std::make_pair(result, true);
	}

	/**
	* Inserts the element.  If the element exists in the set it will not be inserted.
	* @param hint - the hint is unused
	* @param elem - the element to be inserted.
	* @return A pair containing an interator to the position where the element either was inserted, or would have been inserted
	*          if the same element didn't already exist in the set, and a bool indicating whether the element was successfully inserted.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr std::pair<typename basic_set<V, M, Container>::iterator, bool> basic_set<V, M, Container>::insert([[maybe_unused]] const_iterator hint, element_type elem)
	{
		return insert(elem);
	}


	/** Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
	* @param first The first element in the range to insert.
	* @param last One past the last element in the range to insert.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	template< class InputIt >
	constexpr void basic_set<V, M, Container>::insert(InputIt first, InputIt last)
	{
		std::for_each(first, last, [&](element_type element) -> void
		{
			insert(element);
		});
	}

	/** Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
	* @param initializer List containing elements to insert.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr void basic_set<V, M, Container>::insert(std::initializer_list<element_type> ilist)
	{
		for (element_type & element : ilist)
		{
			insert(element);
		}
	}

	/** Emplaces a new element into the container constructed in-place with the given args if there is no element with the
	 *  key in the container. 
	 * @param args - arguments to forward to the constructor of the element
	 * @return A pair containing an interator to the position where the element either was emplaced, or would have been emplaced
	 *         if the same element didn't already exist in the set, and a bool indicating whether the element was successfully emplaced.
	 */
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	template <class... Args>
	constexpr std::pair<typename basic_set<V, M, Container>::iterator, bool> basic_set<V, M, Container>::emplace(Args&& ...args)
	{
		element_type elem{ std::forward<Args>(args)... };
		iterator itr = lower_bound(elem);
		if (*itr == elem)
		{
			return std::make_pair(itr, false);
		}

		iterator result = container_.insert(itr, std::move(elem));
		return std::make_pair(result, true);
	}

	/** Inserts a new element into the container constructed in-place with the given args if there is no element with the
	*  key in the container.
	* @param hint - not used
	* @param args - arguments to forward to the constructor of the element
	* @return A pair containing an interator to the position where the element either was emplaced, or would have been emplaced
	 *         if the same element didn't already exist in the set, and a bool indicating whether the element was successfully emplaced.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	template <class... Args>
	constexpr std::pair<typename basic_set<V, M, Container>::iterator, bool> basic_set<V, M, Container>::emplace_hint([[maybe_unused]] const_iterator hint, Args&& ...args)
	{
		return emplace(std::forward<Args>(args)...);
	}

	/** Removes the element (if one exists).
	 * @param elem - element to remove. 
	 * @return Number of elements removed.
	 */
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr bool basic_set<V, M, Container>::erase(element_type elem)
	{
		iterator itr = lower_bound(elem);
		if (*itr == elem)
		{
			container_.erase(itr);
			return true;
		}
			
		return false;
	}

	/** Removes the element (if one exists) with a key equivalent to supplied key.
	 * @param key -  key of the element to remove.
	 * @return Number of elements removed.
	 */
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr bool basic_set<V, M, Container>::erase(key_type key)
	{
		iterator itr = lower_bound(element_type{ key, static_cast<M>(0) });
		if (itr != end() && itr->value == key)
		{
			container_.erase(itr);
			return true;
		}

		return false;
	}

	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::membership_type basic_set<V, M, Container>::membership(key_type key) const
	{
		const_iterator lb = lower_bound(key);
		if (lb == end())
			return static_cast<M>(0);

		if (lb->value() == key)
			return lb->membership();

		if (lb == begin())
			return static_cast<M>(0);

		const_iterator prev{ lb };
		return linear_interpolate(*(--prev), key, *lb);
	}

	/** Finds an element with key that compares equivalent to the supplied key.
	* @param key - key to compare elements against for equivalence.
	* @return Const iterator to an element with the supplied key. If no such element is found, past-the-end iterator is returned.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::iterator basic_set<V, M, Container>::find(key_type key)
	{
		return find(element_type{ key, static_cast<M>(0) });
	}

	/** Finds an element with key that compares equivalent to the supplied key.
	* @param key - key to compare elements against for equivalence.
	* @return Const iterator to an element with the supplied key. If no such element is found, past-the-end iterator is returned.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::const_iterator basic_set<V, M, Container>::find(key_type key) const
	{
		return find(element_type{ key, static_cast<M>(0) });
	}

	/** Finds an element with key that compares equivalent to the key of the supplied element.
	* @param elem - element to compare elements against for equivalence.
	* @return Iterator to an element equivalent to supplied element. If no such element is found, past-the-end iterator is returned.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::iterator basic_set<V, M, Container>::find(element_type elem)
	{
		iterator itr = lower_bound(elem);
		if (itr == end() || *itr != elem)
			return end();

		return itr;
	}

	/** Finds an element with key that compares equivalent to the key of the supplied element.
	* @param elem - element to compare elements against for equivalence.
	* @return Iterator to an element equivalent to supplied element. If no such element is found, past-the-end iterator is returned.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::const_iterator basic_set<V, M, Container>::find(element_type elem) const
	{
		const_iterator itr = lower_bound(elem);
		if (itr == cend() || *itr != elem)
			return cend();

		return itr;
	}

	/** Determines whether the set contains an element that compares equal with the supplied key.
	* @param key - key to compare against
	* @return Iterator to an element equivalent to supplied element. If no such element is found, past-the-end iterator is returned.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr bool basic_set<V, M, Container>::contains(key_type key) const
	{
		return find(key) != end();
	}

	/** Determines whether the set contains an element with a key that compares equal with the key of the supplied element.
	* @param elem - element with key to search for.
	* @return Iterator to an element equivalent to supplied element. If no such element is found, past-the-end iterator is returned.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr bool basic_set<V, M, Container>::contains(element_type elem) const
	{
		return find(elem) != cend();
	}


	/**
	* Returns a range containing all elements with the given key in the container. The range is defined by two iterators, 
	* one pointing to the first element that is not less than key and another pointing to the first element greater than
	* the key.  In all cases the range will never exceed a single element, which if present is equivelant to calling find(key);
	* @param key - key to compare elements to
	* @return std::pair containing a pair of iterators defining the wanted range.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr std::pair<typename basic_set<V, M, Container>::iterator, typename basic_set<V, M, Container>::iterator>
	basic_set<V, M, Container>::equal_range(key_type key)
	{
		return std::make_pair(lower_bound(key), upper_bound(key));
	}

	/**
	* Returns a range containing all elements with the given key in the container. The range is defined by two iterators,
	* one pointing to the first element that is not less than key and another pointing to the first element greater than
	* the key.  In all cases the range will never exceed a single element, which if present is equivelant to calling find(key);
	* @param key - key to compare elements to
	* @return std::pair containing a pair of iterators defining the wanted range.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr std::pair<typename basic_set<V, M, Container>::const_iterator, typename basic_set<V, M, Container>::const_iterator>
	basic_set<V, M, Container>::equal_range(key_type key) const
	{
		return std::make_pair(lower_bound(key), upper_bound(key));
	}

	/**
	* Returns a range containing all elements with the given key in the container. The range is defined by two iterators,
	* one pointing to the first element that is not less than key and another pointing to the first element with a key
	* greater than the key of the supplied elment.  In all cases the range will never exceed a single element, which if
	* present is equivelant to calling find(element);
	* @param element - element with key to compare against
	* @return std::pair containing a pair of iterators defining the wanted range.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr std::pair<typename basic_set<V, M, Container>::iterator, typename basic_set<V, M, Container>::iterator>
	basic_set<V, M, Container>::equal_range(element_type elem)
	{
		return std::make_pair(lower_bound(elem), upper_bound(elem));
	}

	/**
	* Returns a range containing all elements with the given key in the container. The range is defined by two iterators,
	* one pointing to the first element that is not less than key and another pointing to the first element with a key
	* greater than the key of the supplied elment.  In all cases the range will never exceed a single element, which if
	* present is equivelant to calling find(element);
	* @param element - element with key to compare against
	* @return std::pair containing a pair of iterators defining the wanted range.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr std::pair<typename basic_set<V, M, Container>::const_iterator, typename basic_set<V, M, Container>::const_iterator>
	basic_set<V, M, Container>::equal_range(element_type elem) const
	{
		return std::make_pair(lower_bound(elem), upper_bound(elem));
	}

	/** Returns an iterator pointing to the first element that compares not less to supplied element.
	* @param elem - element to compare against.
	* @return Iterator pointing to the first element that is not less than the supplied element, or last if no such element is found.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::iterator basic_set<V, M, Container>::lower_bound(element_type elem)
	{
		return std::lower_bound(begin(), end(), elem, element_less{});
	}

	/** Returns an iterator pointing to the first element that compares not less to supplied element.
	* @param elem - element to compare against.
	* @return Iterator pointing to the first element that is not less than the supplied element, or last if no such element is found.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::const_iterator basic_set<V, M, Container>::lower_bound(element_type elem) const
	{
		return std::lower_bound(cbegin(), cend(), elem, element_less{});
	}

	/** Returns an iterator pointing to the first element that compares not less to the key.
	* @param  - key to compare the element to.
	* @return Iterator pointing to the first element that is not less than key, or last if no such element is found.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::iterator basic_set<V, M, Container>::lower_bound(key_type key)
	{
		return lower_bound(element_type{ key, static_cast<M>(0) });
	}

	/** Returns an iterator pointing to the first element that compares not less to the key.
	* @param  - key to compare the element to.
	* @return Iterator pointing to the first element that is not less than key, or last if no such element is found.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr basic_set<V, M, Container>::const_iterator basic_set<V, M, Container>::lower_bound(key_type key) const
	{
		return lower_bound(element_type{ key, static_cast<M>(0) });
	}

	/** Returns an iterator pointing to the first element in the range [first, last) that is greater than supplied,
	*   element or last if no such element is found.
	* @param elem - element to compare to.
	* @return iterator pointing to the first element that is greater than key, or last if no such element is found.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::iterator basic_set<V, M, Container>::upper_bound(element_type elem)
	{
		return std::upper_bound(begin(), end(), elem, element_less{});
	}

	/** Returns an iterator pointing to the first element in the range [first, last) that is greater than supplied,
	*   element or last if no such element is found.
	* @param elem - element to compare to.
	* @return iterator pointing to the first element that is greater than the supplied key, or last if no such element is found.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::const_iterator basic_set<V, M, Container>::upper_bound(element_type elem) const
	{
		return std::upper_bound(cbegin(), cend(), elem, element_less{});
	}

	/** Returns an iterator pointing to the first element in the range [first, last) that has a key that is greater than,
	*   the supplied key or last if no such element is found.
	* @param key - key to compare the elements to.
	* @return iterator pointing to the first element that has a key greater than value, or last if no such element is found.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::iterator basic_set<V, M, Container>::upper_bound(key_type key)
	{
		return upper_bound(element_type{ key, static_cast<M>(0) });
	}

	/** Returns an iterator pointing to the first element in the range [first, last) that has a key that is greater than,
	*   the supplied key or last if no such element is found.
	* @param key - key to compare the elements to.
	* @return iterator pointing to the first element that has a key greater than value, or last if no such element is found.
	*/
	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::const_iterator basic_set<V, M, Container>::upper_bound(key_type key) const
	{
		return upper_bound(element_type{ key, static_cast<M>(0) });
	}

	template <class V, class M, class Container>
	requires std::integral<V>&& std::floating_point<M>
	constexpr typename basic_set<V, M, Container>::membership_type basic_set<V, M, Container>::linear_interpolate(
		element_type lhs,
		key_type key,
		element_type rhs) const noexcept
	{
		membership_type dy = rhs.membership() - lhs.membership();
		membership_type dx = static_cast<membership_type>(rhs.value() - lhs.value());
		membership_type ratio = static_cast<membership_type>(key - lhs.value()) / dx;
		return lhs.membership() + (ratio * dy);
	}


	template <class M, class V, class Container = std::vector<basic_element<V, M>>>
	requires std::integral<V>&& std::floating_point<M>
	constexpr basic_set<V, M, Container> make_triangle(V v1, V v2, V v3)
	{
		if (std::is_constant_evaluated())
		{
			if (!(v1 < v2 && v2 < v3))
				std::terminate();
		}
		else
		{
			assert((v1 < v2&& v2 < v3));
		}

		return { {v1, static_cast<M>(0)}, {v2, static_cast<M>(1)}, {v3, static_cast<M>(0)} };
	}


	/** Convenience defintion for common use cases. */
	typedef basic_set<int, float> set;

}
#endif