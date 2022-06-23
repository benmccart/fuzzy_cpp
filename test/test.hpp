#ifndef FUZZY_TEST_TEST_HPP_
#define FUZZY_TEST_TEST_HPP_

#include "../include/fuzzy.hpp"

namespace fuzzy
{
	constexpr bool all_ranges_valid(set const& s)
	{
		size_t size = s.size();
		if (s.end() - s.begin() != size)
			return false;

		if (s.cend() - s.cbegin() != size)
			return false;

		if (s.rend() - s.rbegin() != size)
			return false;

		if (s.crend() - s.crbegin() != size)
			return false;

		return true;
	}
}



#endif