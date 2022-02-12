//  Copyright (c) 2021, Ben McCart
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

#ifndef FUZZY_ELEMENT_HPP
#define FUZZY_ELEMENT_HPP

#include <cassert>
#include <concepts>

#include <fuzzy/operator.hpp>

namespace fuzzy
{
	/**  A basic_element is the fundemental building block(as in element of a set) for fuzzy variablesand fuzzy sets. */
	template <class V, class M>
	requires std::integral<V> && std::floating_point<M>
	class basic_element
	{
	public:
		using value_type = V;
		using membership_type = M;
		using self_type = basic_element<V, M>;

		constexpr basic_element(value_type, membership_type = static_cast<membership_type>(0))
			: value_(value)
			, membership_(membership)
		{
			validate_range(membership_);
		}

		value_type operator<=>(self_type const &other) const = default;

		constexpr membership_type const& membership() const noexcept    { return membership_;   }
		membership_type& membership() noexcept                          { return membership_;   }
		void membership(membership_type m)                              { membership_ = m;      }

		constexpr value_type const& value() const noexcept              { return value_;        }
		value_type& value() noexcept                                    { return value_;        }
		void value(value_type v)                                        { value_ = v;           }

	private:
		value_type value_;
		membership_type membership_;
	};

	/** Convenience defintion for common use cases. */
	using element = basic_element<int, float>;
}

#endif  // FUZZY_ELEMENT_HPP
