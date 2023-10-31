#ifndef FUZZY_MATH_HPP
#define FUZZY_MATH_HPP

#include <cassert>
#include <fuzzy/element.hpp>

namespace fuzzy { namespace math 
{
	/**
	* Used for unsigned integer promotion where differences (max value - min value) in set values can result in
	* exceeding the total range/ of the underlying type.
	*/
	template <class V>
	requires std::integral<V>
	constexpr auto promote(V v)
	{
		if constexpr (std::is_floating_point_v<V> || std::is_unsigned_v<V>)
			return v;
		else if constexpr (sizeof(int) > sizeof(V))
			return static_cast<int>(v);
		else if constexpr (sizeof(long) > sizeof(V))
			return static_cast<long>(v);
		else if constexpr (sizeof(long long) > sizeof(V))
			return static_cast<long long>(v);
		else
			return v;
	}

	/**
	* Strict linear interpolation based on line segment from two points at the point 'key', which must be 
	* in in the range [lhs, rhs].
	* @param lhs Element with lower value.
	* @param key The value at which to interpolate a membership value.
	* @param rhs Element with greater value.
	* @return The linear interpolated membership.
	*/
	template <class V, class M>
	requires std::integral<V>&& std::floating_point<M>
	constexpr M linear_interpolate(basic_element<V, M> lhs, V key, basic_element<V, M> rhs) noexcept
	{
		M dy = rhs.membership() - lhs.membership();
		M dx = static_cast<M>(promote(rhs.value()) - promote(lhs.value()));
		M x_offset = static_cast<M>(promote(key) - promote(lhs.value()));
		M ratio = x_offset / dx;
		return lhs.membership() + (ratio * dy);
	}

}}


#endif // FUZZY_MATH_HPP