//  Copyright (c) 2022, Ben McCart
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

#define FUZZY_USE_TLS_DEF_OPERATOR // DEBUG REMOVEME

#ifndef FUZZY_ALGORITHM_HPP
#define FUZZY_ALGORITHM_HPP

#include <iterator>
#include <limits>
#include <stack>

#include <fuzzy/element.hpp>
#include <fuzzy/operator.hpp>
#include <fuzzy/set.hpp>
#include <fuzzy/traits.hpp>

namespace fuzzy
{
	namespace detail
	{
		template <class Operation>
			requires fuzzy::tnorm_type<Operation> || fuzzy::tconorm_type<Operation>
		struct operation
		{
			template <class V, class M, class Container>
			[[nodiscard]] constexpr static fuzzy::basic_set<V, M, Container> apply(fuzzy::basic_set<V, M, Container> const& lhs, fuzzy::basic_set<V, M, Container> const& rhs)
			{
				using op_t = Operation;
				using set_type = fuzzy::basic_set<V, M, Container>;
				using element_type = typename set_type::element_type;

				auto lhs_itr = cbegin(lhs);
				auto lhs_end = cend(lhs);
				auto rhs_itr = cbegin(rhs);
				auto rhs_end = cend(rhs);

				set_type result;
				for (; lhs_itr != lhs_end && rhs_itr != rhs_end;)
				{
					if (lhs_itr != lhs_end && rhs_itr != rhs_end)
					{
						V lhs_value = lhs_itr->value();
						V rhs_value = rhs_itr->value();
						if (lhs_value < rhs_value)
						{
							M m = op_t::apply(lhs_itr->membership(), rhs.membership(lhs_value));
							result.insert(element_type{ lhs_value, m });
							++lhs_itr;
						}
						else if (rhs_value < lhs_value)
						{
							M m = op_t::apply(lhs.membership(rhs_value), rhs_itr->membership());
							result.insert(element_type{ rhs_value, m });
							++rhs_itr;
						}
						else
						{
							M m = op_t::apply(lhs_itr->membership(), rhs_itr->membership());
							result.insert(element_type{ lhs_value, m });
							++lhs_itr;
							++rhs_itr;
						}
					}
					else if (lhs_itr != lhs_end)
					{
						V lhs_value = lhs_itr->value();
						M m = op_t::apply(lhs_itr->membership(), rhs.membership(lhs_value));
						result.insert(element_type{ lhs_value, m });
						++lhs_itr;
					}
					else if (rhs_itr != rhs_end)
					{
						V rhs_value = rhs_itr->value();
						M m = op_t::apply(lhs.membership(rhs_value), rhs_itr->membership());
						result.insert(element_type{ rhs_value, m });
						++rhs_itr;
					}
				}
			}
		};

		/* Triangular conorm function object.**/
		template <typename M = float>
		requires std::floating_point<M>
		class tconorm_binder
		{
		public:
			using tconorm = tconorm_tag;
			using value_type = M;
			using func_ptr = M(*)(M x, M y);

			tconorm_binder() { func_ = [](M, M) { return std::numeric_limits<M>::quiet_NaN(); }; }
			tconorm_binder(tconorm_binder<M> const&) = delete;
			tconorm_binder(tconorm_binder<M>&&) = delete;
			tconorm_binder<M>& operator=(tconorm_binder<M> const&) = delete;
			tconorm_binder<M>& operator=(tconorm_binder<M>&&) = delete;

			/** binds to a specific tconorm type */
			template <typename T>
			requires tconorm_type<T>
			constexpr void bind(T) noexcept
			{
				func_ = [](M x, M y) -> M { return T::apply(x, y); };
			}

			[[nodiscard]] constexpr M apply(M x, M y) noexcept
			{
				validate_range<M>(x, y);
				return func_(x, y);
			}

		private:
			func_ptr func_ = nullptr;
		};

		/* Triangular conorm function object.**/
		template <class M = float>
		requires std::floating_point<M>
		class tnorm_binder
		{
		public:
			using tnorm = tnorm_tag;
			using func_ptr = M(*)(M x, M y);

			tnorm_binder() { func_ = [](M, M) { return std::numeric_limits<M>::quiet_NaN(); }; }
			tnorm_binder(tnorm_binder<M> const&) = delete;
			tnorm_binder(tnorm_binder<M>&&) = delete;
			tnorm_binder<M>& operator=(tnorm_binder<M> const&) = delete;
			tnorm_binder<M>& operator=(tnorm_binder<M>&&) = delete;

			/** binds to a specific tconorm type */
			template <class T>
			requires tnorm_type<T>
			constexpr void bind(T) noexcept
			{
				func_ = [](M x, M y) -> M { return T::apply(x, y); };
			}

			[[nodiscard]] constexpr M apply(M x, M y) noexcept
			{
				validate_range<M>(x, y);
				return func_(x, y);
			}

		private:
			func_ptr func_;
		};

#ifdef FUZZY_USE_TLS_DEF_OPERATOR
		template <class M>
		requires std::floating_point<M>
		thread_local tconorm_binder<M> *current_tconorm = nullptr;

		template <class M>
		requires std::floating_point<M>
		thread_local tnorm_binder<M> *current_tnorm = nullptr;
#endif
	}


	/**
	* Version of std::set_intersection compatible with fuzzy set theory.
	* @param lhs The left hand side fuzzy set operand.
	* @param rhs The right hand side fuzzy set operand.
	* @return The intersection of the two fuzzy sets.
	*/
	template <class V, class M, class Operation = fuzzy::minimum<M>, class Container>
	requires std::integral<V> && std::floating_point<M> && tnorm_type<Operation>
	[[nodiscard]] constexpr fuzzy::basic_set<V, M, Container> set_intersection(fuzzy::basic_set<V, M, Container> const& lhs, fuzzy::basic_set<V, M, Container> const& rhs)
	{
		return fuzzy::detail::operation<Operation>::apply(lhs, rhs);
	}

	/**
	* Version of std::set_intersection compatible with fuzzy set theory.
	* @param lhs The left hand side fuzzy set operand.
	* @param rhs The right hand side fuzzy set operand.
	* @return The union of the two fuzzy sets.
	*/
	template <class V, class M, class Operation = fuzzy::maximum<M>, class Container>
	requires std::integral<V>&& std::floating_point<M>&& tconorm_type<Operation>
	[[nodiscard]] constexpr fuzzy::basic_set<V, M, Container> set_union(fuzzy::basic_set<V, M, Container> const& lhs, fuzzy::basic_set<V, M, Container> const& rhs)
	{
		return fuzzy::detail::operation<Operation>::apply(lhs, rhs);
	}



#ifdef FUZZY_USE_TLS_DEF_OPERATOR

	template <class T>
	requires tnorm_type<T> && std::floating_point<typename T::value_type>
	class use_tnorm_t
	{
	public:
		using value_type = typename T::value_type;

		use_tnorm_t() = delete;
		use_tnorm_t(use_tnorm_t<T> const&) = delete;
		use_tnorm_t(use_tnorm_t<T>&&) = delete;
		use_tnorm_t<T>& operator=(use_tnorm_t<T> const&) = delete;
		use_tnorm_t<T>& operator=(use_tnorm_t<T>&&) = delete;

		constexpr use_tnorm_t(T) noexcept
			: previous_(detail::current_tnorm<value_type>)
		{
			current_.bind(T{});
			detail::current_tnorm<value_type> = &current_;
		}

		constexpr ~use_tnorm_t() noexcept
		{
			assert(detail::current_tnorm<value_type> == &current_);
			detail::current_tnorm<value_type> = previous_;
		}

	private:
		detail::tnorm_binder<value_type> current_;
		detail::tnorm_binder<value_type> *previous_;
	};

	template<class T> use_tnorm_t(T) -> use_tnorm_t<T>;
	

	template <class T>
	requires tconorm_type<T>&& std::floating_point<typename T::value_type>
	class use_tconorm_t
	{
	public:
		using value_type = typename T::value_type;

		use_tconorm_t() = delete;
		use_tconorm_t(use_tconorm_t<T> const&) = delete;
		use_tconorm_t(use_tconorm_t<T>&&) = delete;
		use_tconorm_t<T>& operator=(use_tconorm_t<T> const&) = delete;
		use_tconorm_t<T>& operator=(use_tconorm_t<T>&&) = delete;

		constexpr use_tconorm_t(T) noexcept
			: previous_(detail::current_tconorm<value_type>)
		{
			current_.bind(T{});
			detail::current_tconorm<value_type> = &current_;
		}

		constexpr ~use_tconorm_t() noexcept
		{
			assert(detail::current_tconorm<value_type> == &current_);
			detail::current_tconorm<value_type> = previous_;
		}

	private:
		detail::tconorm_binder<value_type> current_;
		detail::tconorm_binder<value_type>* previous_;
	};

	template<class T> use_tconorm_t(T) -> use_tconorm_t<T>;





#endif

	/**
	* Complement of fuzzy set.
	* @param aset The lhs set to intersect.
	* @return The complement of the set.
	*/
	template <class V, class M, class Operation = fuzzy::maximum<M>, class Container>
	requires std::integral<V>&& std::floating_point<M>
	[[nodiscard]] constexpr fuzzy::basic_set<V, M, Container> operator&(fuzzy::basic_set<V, M, Container> const& lhs, fuzzy::basic_set<V, M, Container> const& rhs)
	{
		return set_intersection<V, M, Operation, Container>(lhs, rhs);
	}

	/**
	* Complement of fuzzy set.
	* @param aset The set to complement.
	* @return The complement of the set.
	*/
	template <class V, class M, class Operation = fuzzy::maximum<M>, class Container>
	requires std::integral<V>&& std::floating_point<M>
	[[nodiscard]] constexpr fuzzy::basic_set<V, M, Container> set_complement(fuzzy::basic_set<V, M, Container> const& aset)
	{
		using set_type = fuzzy::basic_set<V, M, Container>;
		using element_type = typename set_type::element_type;
		set_type result;

		constexpr V v_min = std::numeric_limits<V>::lowest();
		constexpr V v_max = std::numeric_limits<V>::max();
		constexpr V v_offset = static_cast<V>(1);
		constexpr M m_max = static_cast<M>(1.0);
		constexpr M m_min = static_cast<M>(0.0);
		constexpr complement<M> comp;

		if (aset.empty())
		{
			result.insert(element_type{ v_min, m_max });
			result.insert(element_type{ v_max, m_max });
			return result;
		}

		M const m_front = comp.apply(aset.front().membership());
		if (m_front != m_min && aset.front().value() != v_min)
		{
			V const v_prefix = aset.front().value() - v_offset;
			if (v_prefix != v_min)
				result.insert(element_type{ v_min, m_max });

			if (m_front != m_min)
				result.insert(element_type{ v_prefix, m_max });
		}

		for (auto& element : aset)
		{
			result.insert(fuzzy::basic_element<V, M>{ element.value(), comp.apply(element.membership()) });
		}

		M const m_back = result.back().membership();
		if (m_back != m_min && aset.back().value() != v_max)
		{
			V const v_postfix = aset.back().value() + v_offset;
			if (v_postfix != v_max)
				result.insert(element_type{ v_max, m_max });

			if (m_back != m_min)
				result.insert(element_type{ v_postfix, m_max });
		}

		return result;
	}

	/**
	* Complement of fuzzy set.
	* @param aset The set to complement.
	* @return The complement of the set.
	*/
	template <class V, class M, class Operation = fuzzy::maximum<M>, class Container>
	requires std::integral<V>&& std::floating_point<M>
	[[nodiscard]] constexpr fuzzy::basic_set<V, M, Container> operator~(fuzzy::basic_set<V, M, Container> const& aset)
	{
		return set_complement<V,M,Operation, Container>(aset);
	}


}

#endif // FUZZY_ALGORITHM_HPP