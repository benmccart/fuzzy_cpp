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

#ifndef FUZZY_TRAITS_HPP
#define FUZZY_TRAITS_HPP

#include <array>
#include <type_traits>

#include <fuzzy/fwd.hpp>


namespace fuzzy 
{
	struct tnorm_tag {};
	struct tconorm_tag {};

	//template <class T>
	//concept empty_struct = std::is_empty_v<T>;

	//template <class T>
	//concept has_tnorm_tag = empty_struct<T> && requires (T)
	//{
	//	typename T::tnorm;
	//};

	//template <class T>
	//concept has_tconorm_tag = empty_struct<T> && requires (T)
	//{
	//	typename T::tconorm;
	//};

	template <class T>
	concept tnorm_typenames = requires (T)
	{
		typename T::tnorm;
		typename T::value_type;
	};

	template <class T>
	concept tnorm_type = tnorm_typenames<T> && std::is_same_v<typename T::tnorm, tnorm_tag> && std::is_floating_point_v<typename T::value_type> && requires (T)
	{
		T::apply(static_cast<typename T::value_type>(0), static_cast<typename T::value_type>(0));
	};

	template <class T>
	concept tconorm_typenames = requires (T)
	{
		typename T::tconorm;
		typename T::value_type;
	};

	template <class T>
	concept tconorm_type = tconorm_typenames<T> && std::is_same_v<typename T::tconorm, tconorm_tag> && std::is_floating_point_v<typename T::value_type> && requires (T)
	{
		T::apply(static_cast<typename T::value_type>(0), static_cast<typename T::value_type>(0));
	};

	
	namespace traits
	{
		// NOTE: At this point this trait is not useful, as even basic sized buffers without allocators wouldn't be garunteed not to crash?  Maybe later?
		//template <class Container>
		//struct has_allocator
		//{
		//	static const bool value = true;
		//};

		//template <class T, std::size_t N>
		//struct has_allocator<std::array<T, N>>
		//{
		//	static const bool value = false;
		//};



		//template <has_tnorm_tag T>
		//struct is_tnorm
		//{
		//	static const bool value = true;
		//};

		///** Default traits function for triangular norm classification. */
		//template <empty_struct T>
		//struct is_tnorm
		//{
		//	static const bool value = false;
		//};



		//template <>
		//struct is_tnorm<fuzzy::algabraic_product>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tnorm<fuzzy::bounded_difference>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tnorm<fuzzy::drastic_product>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tnorm<fuzzy::einstein_product>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tnorm<fuzzy::hamacher_product>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tnorm<fuzzy::minimum>
		//{
		//	static const bool value = true;
		//};

		/** Default traits function for triangular conorm classification. */
		//template <class T>
		//struct is_tconorm
		//{
		//	static const bool value = false;
		//};

		//template <has_tconorm_tag T>
		//struct is_cotnorm
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tconorm<fuzzy::algabraic_sum>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tconorm<fuzzy::bounded_sum>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tconorm<fuzzy::drastic_sum>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tconorm<fuzzy::einstein_sum>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tconorm<fuzzy::hamacher_sum>
		//{
		//	static const bool value = true;
		//};

		//template <>
		//struct is_tconorm<fuzzy::maximum>
		//{
		//	static const bool value = true;
		//};
	}

	//template <class T, typename M>
	//concept TNorm = requires  std::floating_point<M> && fuzzy::traits::is_tnorm<T>::value && (T t, M m)
	//{
	//	M mr = t(m, m);
	//};


	//template <class T, typename M>
	//concept TConorm = requires  std::floating_point<M> && fuzzy::traits::is_tconorm<T>::value && (T t, M m)
	//{
	//	M mr = t(m, m);
	//};
}

#endif //FUZZY__TRAITS_HPP