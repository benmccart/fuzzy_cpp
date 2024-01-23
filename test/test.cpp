#include "../include/fuzzy.hpp"
#include "./test.hpp"

#include <iostream>
#include <limits>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>


using namespace fuzzy;

TEST_CASE("membership-bounds-check", "[boundscheck]")
{
    [[maybe_unused]] constexpr auto v0 = algabraic_product<>::apply(1.0f, 1.0f);
    [[maybe_unused]] constexpr auto v1 = algabraic_product<>::apply(0.0f, 0.0f);
    // FAIL constexpr auto v2 = algabraic_product<>::apply(-0.01f, 1.0f);
    // FAIL constexpr auto v0 = algabraic_product<>::apply(1.01f, 1.0f);
    
    validate_range(0.0);
    validate_range(0.5);
    validate_range(1.0);
    // FAIL validate_range(-0.00001);
    // FAIL validate_range( 1.00001);
}

TEST_CASE("t-norm-tests", "[tnormtests]") 
{
    REQUIRE(algabraic_product<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(algabraic_product<>::apply(0.00f, 0.50f) == 0.00f);
    REQUIRE(algabraic_product<>::apply(0.00f, 1.00f) == 0.00f);
    REQUIRE(algabraic_product<>::apply(0.50f, 1.00f) == 0.50f);
    REQUIRE(algabraic_product<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(algabraic_product<>::apply(0.50f, 0.50f) == 0.25f);

    REQUIRE(bounded_difference<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(bounded_difference<>::apply(0.00f, 0.50f) == 0.00f);
    REQUIRE(bounded_difference<>::apply(0.00f, 1.00f) == 0.00f);
    REQUIRE(bounded_difference<>::apply(0.50f, 1.00f) == 0.50f);
    REQUIRE(bounded_difference<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(bounded_difference<>::apply(0.50f, 0.50f) == 0.00f);
    REQUIRE(bounded_difference<>::apply(0.75f, 0.75f) == 0.50f);

    REQUIRE(drastic_product<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(drastic_product<>::apply(0.00f, 0.50f) == 0.00f);
    REQUIRE(drastic_product<>::apply(0.00f, 1.00f) == 0.00f);
    REQUIRE(drastic_product<>::apply(0.50f, 1.00f) == 0.50f);
    REQUIRE(drastic_product<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(drastic_product<>::apply(0.50f, 0.50f) == 0.00f);

    REQUIRE(einstein_product<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(einstein_product<>::apply(0.00f, 0.50f) == 0.00f);
    REQUIRE(einstein_product<>::apply(0.00f, 1.00f) == 0.00f);
    REQUIRE(einstein_product<>::apply(0.50f, 1.00f) == 0.50f);
    REQUIRE(einstein_product<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(einstein_product<>::apply(0.50f, 0.50f) == 0.20f);

    REQUIRE(hamacher_product<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(hamacher_product<>::apply(0.00f, 0.50f) == 0.00f);
    REQUIRE(hamacher_product<>::apply(0.00f, 1.00f) == 0.00f);
    REQUIRE(hamacher_product<>::apply(0.50f, 1.00f) == 0.50f);
    REQUIRE(hamacher_product<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(hamacher_product<>::apply(0.50f, 0.50f) == 0.33333333f);

    REQUIRE(minimum<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(minimum<>::apply(0.00f, 0.50f) == 0.00f);
    REQUIRE(minimum<>::apply(0.00f, 1.00f) == 0.00f);
    REQUIRE(minimum<>::apply(0.50f, 1.00f) == 0.50f);
    REQUIRE(minimum<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(minimum<>::apply(0.50f, 0.50f) == 0.50f);
}

TEST_CASE("t-conorm-tests", "[tconormtests]")
{
    REQUIRE(algabraic_sum<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(algabraic_sum<>::apply(0.00f, 0.50f) == 0.50f);
    REQUIRE(algabraic_sum<>::apply(0.00f, 1.00f) == 1.00f);
    REQUIRE(algabraic_sum<>::apply(0.50f, 1.00f) == 1.00f);
    REQUIRE(algabraic_sum<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(algabraic_sum<>::apply(0.50f, 0.50f) == 0.75f);

    REQUIRE(bounded_sum<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(bounded_sum<>::apply(0.00f, 0.50f) == 0.50f);
    REQUIRE(bounded_sum<>::apply(0.00f, 1.00f) == 1.00f);
    REQUIRE(bounded_sum<>::apply(0.50f, 1.00f) == 1.00f);
    REQUIRE(bounded_sum<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(bounded_sum<>::apply(0.50f, 0.50f) == 1.00f);
    REQUIRE(bounded_sum<>::apply(0.25f, 0.25f) == 0.50f);

    REQUIRE(drastic_sum<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(drastic_sum<>::apply(0.00f, 0.50f) == 0.50f);
    REQUIRE(drastic_sum<>::apply(0.00f, 1.00f) == 1.00f);
    REQUIRE(drastic_sum<>::apply(0.50f, 1.00f) == 1.00f);
    REQUIRE(drastic_sum<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(drastic_sum<>::apply(0.50f, 0.50f) == 1.00f);

    REQUIRE(einstein_sum<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(einstein_sum<>::apply(0.00f, 0.50f) == 0.50f);
    REQUIRE(einstein_sum<>::apply(0.00f, 1.00f) == 1.00f);
    REQUIRE(einstein_sum<>::apply(0.50f, 1.00f) == 1.00f);
    REQUIRE(einstein_sum<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(einstein_sum<>::apply(0.50f, 0.50f) == 0.80f);

    REQUIRE(hamacher_sum<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(hamacher_sum<>::apply(0.00f, 0.50f) == 0.50f);
    REQUIRE(hamacher_sum<>::apply(0.00f, 1.00f) == 1.00f);
    REQUIRE(hamacher_sum<>::apply(0.50f, 1.00f) == 1.00f);
    REQUIRE(hamacher_sum<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(hamacher_sum<>::apply(0.50f, 0.50f) == 0.66666666f);

    REQUIRE(maximum<>::apply(0.00f, 0.00f) == 0.00f);
    REQUIRE(maximum<>::apply(0.00f, 0.50f) == 0.50f);
    REQUIRE(maximum<>::apply(0.00f, 1.00f) == 1.00f);
    REQUIRE(maximum<>::apply(0.50f, 1.00f) == 1.00f);
    REQUIRE(maximum<>::apply(1.00f, 1.00f) == 1.00f);
    REQUIRE(maximum<>::apply(0.50f, 0.50f) == 0.50f);
}

TEST_CASE("basic_element-tests", "[basic_elementtests]")
{
    element e1{ 1, 1.0f };
    REQUIRE(e1.membership() == 1.0f);
    REQUIRE(e1.value() == 1);

    element e0{ 0, 0.0f };
    REQUIRE(e0.membership() == 0.0f);
    REQUIRE(e0.value() == 0);
    REQUIRE(e0 < e1);

    element eol{ 3, 0.4f };
    element eor{ 5, 0.4f };
    element ea = [](element const l, element const r) constexpr
    {
        return element{ l.value() + r.value(), l.membership() + r.membership() };
    }(eol, eor);
    REQUIRE(ea.value() == 8);
    REQUIRE(ea.membership() == 0.8f);

    REQUIRE(eol == element{ 3, 0.4f });
    REQUIRE(eol != element{ 3, 0.3999f });
    REQUIRE(eol != element{ -3, 0.4f });
    
    element ec{ e1 };
    REQUIRE(ec == e1);
    REQUIRE(ec != e0);
    ec = e0;
    REQUIRE(ec != e1);
    REQUIRE(ec == e0);

    element em{ std::move(ec) };
    REQUIRE(em == element{ 0, 0.0f });
    REQUIRE(em != element{ 1, 1.0f });

    em = element{ 2, 0.2f };
    REQUIRE(em == element{ 2, 0.2f });
    REQUIRE(em != element{ 2, 0.1f });

    // FAIL element em1{ -1, -1.0f };
    // FAIL element em1{ -1, -1.0001f };
    // FAIL element einf{ 1, std::numeric_limits<float>::infinity() };
    // FAIL element eninf{ -1, -std::numeric_limits<float>::infinity() };
}

TEST_CASE("empty-set", "[empty_set]")
{
    set empty;
    REQUIRE(empty.empty());
    REQUIRE(empty.size() == 0u);
    REQUIRE(all_ranges_valid(empty));
}

TEST_CASE("one-element-set", "[one_element_set]")
{
    set s1 = { {3, 1.0f} };
    REQUIRE(!s1.empty());
    REQUIRE(s1.size() == 1u);
    REQUIRE(all_ranges_valid(s1));
}

TEST_CASE("two-element-set", "[two_element_set]")
{
    set s2 = { {3, 1.0f}, {5, 1.0f} };
    REQUIRE(!s2.empty());
    REQUIRE(s2.size() == 2u);
    REQUIRE(all_ranges_valid(s2));
}

TEST_CASE("set-equivalence", "[set_equivalence]")
{
    set s1 = { {3, 1.0f}, {5, 1.0f} };
    set s2 = { {3, 1.0f}, {5, 1.0f} };
    REQUIRE(s1 == s2);
    REQUIRE(s1 == set{ { {3, 1.0f}, { 5, 1.0f } } });
    REQUIRE(s1 != set{ { {3, 1.0f} } });
    REQUIRE(s1 != set{ { { 5, 1.0f } } });
    REQUIRE(s1 != set{ { {3, 0.999f}, { 5, 1.0f } } });
    REQUIRE(s1 != set{ { {3, 1.0f}, { 5, 0.999f } } });
    REQUIRE(s1 != set{ { {4, 1.0f}, { 5, 1.0f } } });
    REQUIRE(s1 != set{ { {3, 1.0f}, { 4, 1.0f } } });
}

TEST_CASE("set-copy-construct", "[set_copy_construct]")
{
    set s1 = { {3, 1.0f}, {5, 1.0f} };
    set s2{ s1 };
    REQUIRE(!s2.empty());
    REQUIRE(s2.size() == 2u);
    REQUIRE(all_ranges_valid(s2));
    REQUIRE(s2 == s1);

    REQUIRE(s2 != set{ { {3, 0.0f}, { 4, 1.0f } } });
}

TEST_CASE("set-move-construct", "[set_move_construct]")
{
    set s1 = { {3, 1.0f}, {5, 1.0f} };
    set s2{ std::move(s1) };
    REQUIRE(!s2.empty());
    REQUIRE(s2.size() == 2u);
    REQUIRE(all_ranges_valid(s2));
    REQUIRE(s1.empty());
    REQUIRE(s2 == set{ { {3, 1.0f}, { 5, 1.0f } } });
}

TEST_CASE("set-assignment", "[set_assignment]")
{
    set s1 = { {3, 1.0f}, {5, 1.0f} };
    set s2;
    s2 = s1;
    REQUIRE(!s2.empty());
    REQUIRE(s2.size() == 2u);
    REQUIRE(all_ranges_valid(s2));
    REQUIRE(s2 == set{ { {3, 1.0f}, { 5, 1.0f } } });

    set s3;
    s3 = std::move(s1);
    REQUIRE(!s3.empty());
    REQUIRE(s3.size() == 2u);
    REQUIRE(all_ranges_valid(s3));
    REQUIRE(s3 == set{ { {3, 1.0f}, { 5, 1.0f } } });

    set s4;
    s4 = { {3, 1.0f}, { 5, 1.0f } };
    REQUIRE(!s4.empty());
    REQUIRE(s4.size() == 2u);
    REQUIRE(all_ranges_valid(s4));
    REQUIRE(s4 == set{ { {3, 1.0f}, { 5, 1.0f } } });
}

TEST_CASE("set-lowerbound", "[set_lowerbound]")
{
    set s = { {3, 1.0f}, {5, 0.8f} };

    // lb on keys
    REQUIRE(*s.lower_bound(0) == element{ 3, 1.0f });
    REQUIRE(*s.lower_bound(3) == element{ 3, 1.0f });
    REQUIRE(*s.lower_bound(4) == element{ 5, 0.8f });
    REQUIRE(*s.lower_bound(5) == element{ 5, 0.8f });
    REQUIRE(s.lower_bound(6) == s.end());

    // lb on elements
    REQUIRE(*s.lower_bound(element{ 1, 0.0f }) == element{ 3, 1.0f });
    REQUIRE(*s.lower_bound(element{ 3, 0.7f }) == element{ 3, 1.0f });
    REQUIRE(*s.lower_bound(element{ 4, 1.0f }) == element{ 5, 0.8f });
    REQUIRE(*s.lower_bound(element{ 5, 0.8f }) == element{ 5, 0.8f });
    REQUIRE(s.lower_bound(element{ 6, 0.0f }) == s.end());

    set const cs = { {3, 1.0f}, {5, 0.8f} };
    
    // lb on keys
    REQUIRE(*cs.lower_bound(0) == element{ 3, 1.0f });
    REQUIRE(*cs.lower_bound(3) == element{ 3, 1.0f });
    REQUIRE(*cs.lower_bound(4) == element{ 5, 0.8f });
    REQUIRE(*cs.lower_bound(5) == element{ 5, 0.8f });
    REQUIRE(cs.lower_bound(6) == cs.end());

    // lb on elements
    REQUIRE(*cs.lower_bound(element{ 1, 0.0f }) == element{ 3, 1.0f });
    REQUIRE(*cs.lower_bound(element{ 3, 0.7f }) == element{ 3, 1.0f });
    REQUIRE(*cs.lower_bound(element{ 4, 1.0f }) == element{ 5, 0.8f });
    REQUIRE(*cs.lower_bound(element{ 5, 0.8f }) == element{ 5, 0.8f });
    REQUIRE(cs.lower_bound(element{ 6, 0.0f }) == cs.end());

}

TEST_CASE("set-upperbound", "[set_upperbound]")
{
    set s = { {3, 1.0f}, {5, 0.8f} };

    // ub on keys
    REQUIRE(*s.upper_bound(0) == element{ 3, 1.0f });
    REQUIRE(*s.upper_bound(3) == element{ 5, 0.8f });
    REQUIRE(*s.upper_bound(4) == element{ 5, 0.8f });
    REQUIRE(s.upper_bound(5) == s.end());
    REQUIRE(s.upper_bound(6) == s.end());

    // ub on elements
    REQUIRE(*s.upper_bound(element{ 1, 0.0f }) == element{ 3, 1.0f });
    REQUIRE(*s.upper_bound(element{ 3, 0.7f }) == element{ 5, 0.8f });
    REQUIRE(*s.upper_bound(element{ 4, 1.0f }) == element{ 5, 0.8f });
    REQUIRE(s.upper_bound(element{ 5, 0.8f }) == s.end());
    REQUIRE(s.upper_bound(element{ 6, 0.0f }) == s.end());

    set const cs = { {3, 1.0f}, {5, 0.8f} };

    // ub on keys
    REQUIRE(*cs.upper_bound(0) == element{ 3, 1.0f });
    REQUIRE(*cs.upper_bound(3) == element{ 5, 0.8f });
    REQUIRE(*cs.upper_bound(4) == element{ 5, 0.8f });
    REQUIRE(cs.upper_bound(5) == cs.end());
    REQUIRE(cs.upper_bound(6) == cs.end());

    // ub on elements
    REQUIRE(*cs.upper_bound(element{ 1, 0.0f }) == element{ 3, 1.0f });
    REQUIRE(*cs.upper_bound(element{ 3, 0.7f }) == element{ 5, 0.8f });
    REQUIRE(*cs.upper_bound(element{ 4, 1.0f }) == element{ 5, 0.8f });
    REQUIRE(cs.upper_bound(element{ 5, 0.8f }) == cs.end());
    REQUIRE(cs.upper_bound(element{ 6, 0.0f }) == cs.end());
}

TEST_CASE("set-find", "[set_find]")
{
    // find on keys
    set s = { {3, 1.0f}, {5, 0.8f} };
    REQUIRE(s.find(0) == s.end());
    REQUIRE(*s.find(3) == element{ 3, 1.0f });
    REQUIRE(s.find(4) == s.end());
    REQUIRE(*s.find(5) == element{ 5, 0.8f });
    REQUIRE(s.find(6) == s.end());

    set const cs = { {3, 1.0f}, {5, 0.8f} };
    REQUIRE(cs.find(0) == cs.end());
    REQUIRE(*cs.find(3) == element{ 3, 1.0f });
    REQUIRE(cs.find(4) == cs.end());
    REQUIRE(*cs.find(5) == element{ 5, 0.8f });
    REQUIRE(cs.find(6) == cs.end());

    // find on elements
    REQUIRE(s.find(element{ 0, 0.0f }) == s.end());
    REQUIRE(*s.find(element{ 3, 1.0f }) == element{ 3, 1.0f });
    REQUIRE(s.find(element{ 3, 0.0f }) == s.end());
    REQUIRE(s.find(element{ 4, 0.0f }) == s.end());
    REQUIRE(*s.find(element{ 5, 0.8f }) == element{ 5, 0.8f });
    REQUIRE(s.find(element{ 6, 1.0f }) == s.end());

    REQUIRE(cs.find(element{ 0, 1.0f }) == cs.end());
    REQUIRE(*cs.find(element{ 3, 1.0f }) == element{ 3, 1.0f });
    REQUIRE(cs.find(element{ 4, 1.0f }) == cs.end());
    REQUIRE(*cs.find(element{ 5, 0.8f }) == element{ 5, 0.8f });
    REQUIRE(cs.find(element{ 5, 0.7f }) == cs.end());
    REQUIRE(cs.find(element{ 6, 0.0f }) == cs.end());
}

TEST_CASE("set-contains", "[set_contains]")
{
    // find on keys
    set const cs = { {3, 1.0f}, {5, 0.8f} };
    REQUIRE(!cs.contains(0));
    REQUIRE(cs.contains(3));
    REQUIRE(!cs.contains(4));
    REQUIRE(cs.contains(5));
    REQUIRE(!cs.contains(6));

    // find on elements
    REQUIRE(!cs.contains(element{ 0, 1.0f }));
    REQUIRE(cs.contains(element{ 3, 1.0f }));
    REQUIRE(!cs.contains(element{ 3, 0.7f }));
    REQUIRE(!cs.contains(element{ 4, 1.0f }));
    REQUIRE(cs.contains(element{ 5, 0.8f }));
    REQUIRE(!cs.contains(element{ 5, 1.0f }));
    REQUIRE(!cs.contains(element{ 6, 0.0f }));
}

TEST_CASE("set-count", "[set_count]")
{
    // count on keys
    set const cs = { {3, 1.0f}, {5, 0.8f} };
    REQUIRE(cs.count(0) == 0u);
    REQUIRE(cs.count(3) == 1u);
    REQUIRE(cs.count(4) == 0u);
    REQUIRE(cs.count(5) == 1u);
    REQUIRE(cs.count(6) == 0u);

    // count on elements
    REQUIRE(cs.count(element{ 0, 1.0f }) == 0u);
    REQUIRE(cs.count(element{ 3, 1.0f }) == 1u);
    REQUIRE(cs.count(element{ 3, 0.7f }) == 0u);
    REQUIRE(cs.count(element{ 4, 1.0f }) == 0u);
    REQUIRE(cs.count(element{ 5, 0.8f }) == 1u);
    REQUIRE(cs.count(element{ 5, 1.0f }) == 0u);
    REQUIRE(cs.count(element{ 6, 0.0f }) == 0u);
}


TEST_CASE("set-insert", "[set_insert]")
{
    // insertion of elements.
    set cs;
    cs.insert({ {3, 1.0f}, {5, 0.8f} });
    REQUIRE(cs.count(0) == 0u);
    REQUIRE(cs.count(3) == 1u);
    REQUIRE(cs.count(4) == 0u);
    REQUIRE(cs.count(5) == 1u);
    REQUIRE(cs.count(6) == 0u);

    cs.insert(element{ 4, 0.4f });
    REQUIRE(cs.contains(4));
    cs.insert(cs.cend(), element{ 0, 0.3f });
    REQUIRE(cs.contains(0));

    std::vector<element> const other = { {7, 1.0f}, {5, 0.0f}, {6, 0.6f} };
    cs.insert(other.begin(), other.end());
    REQUIRE(cs.contains(element{ 5, 0.8f }));
    REQUIRE(cs.contains(element{ 6, 0.6f }));
    REQUIRE(cs.contains(element{ 7, 1.0f }));

    auto pair1 = cs.insert(cs.begin(), element{ 4, 1.0f });
    REQUIRE(pair1.second == false);
    REQUIRE(pair1.first != cs.end());

    auto pair2 = cs.insert(cs.end(), element{ -1, 0.1f });
    REQUIRE(pair2.second == true);
    REQUIRE(pair2.first == cs.begin());
}


TEST_CASE("TR0-set", "[TR0_set]")
{
    set item = make_triangle<float>(4, 8, 12);
    REQUIRE(item.membership(2) == 0.0f);
    REQUIRE(item.membership(4) == 0.0f);
    REQUIRE(item.membership(6) == 0.5f);
    REQUIRE(item.membership(8) == 1.0f);
    REQUIRE(item.membership(10) == 0.5f);
    REQUIRE(item.membership(12) == 0.0f);
    REQUIRE(item.membership(14) == 0.0f);

    REQUIRE(!item.empty());
    REQUIRE(item.size() == 3u);
    REQUIRE(all_ranges_valid(item));
    REQUIRE(item.find(element{ 0, 0.3f }) == item.cend());
    REQUIRE(item.find(element{ 8, 1.0f }) != item.cend());
    REQUIRE(!item.contains(0));
    REQUIRE(item.contains(4));
    REQUIRE(item.count(0) == 0);
    REQUIRE(item.count(4) == 1);
    REQUIRE(item.count(element{ 0, 0.3f }) == 0);
    REQUIRE(item.count(element{ 12, 0.0f }) == 1);
}

TEST_CASE("TR1-set", "[TR1_set]")
{
    set item = make_trapezoid<float>(4, 8, 12, 16);
    REQUIRE(item.membership(2) == 0.0f);
    REQUIRE(item.membership(4) == 0.0f);
    REQUIRE(item.membership(6) == 0.5f);
    REQUIRE(item.membership(8) == 1.0f);
    REQUIRE(item.membership(10) == 1.0f);
    REQUIRE(item.membership(12) == 1.0f);
    REQUIRE(item.membership(14) == 0.5f);
    REQUIRE(item.membership(16) == 0.0f);
    REQUIRE(item.membership(18) == 0.0f);

    REQUIRE(!item.empty());
    REQUIRE(item.size() == 4u);
    REQUIRE(all_ranges_valid(item));
    REQUIRE(item.find(element{ 0, 0.3f }) == item.cend());
    REQUIRE(item.find(element{ 8, 1.0f }) != item.cend());
    REQUIRE(*item.find(element{ 8, 1.0f }) == element{ 8, 1.0f });
    REQUIRE(!item.contains(0));
    REQUIRE(item.contains(4));
    REQUIRE(item.count(0) == 0);
    REQUIRE(item.count(4) == 1);
    REQUIRE(item.count(element{ 8, 1.0f }) == 1);
    REQUIRE(item.count(element{ std::numeric_limits<int>::max(), 0.3f }) == 0);
    REQUIRE(item.count(element{ std::numeric_limits<int>::max(), 0.0f }) == 0);
}

TEST_CASE("SET-complement", "[SET_complement]")
{
    // Default case.
    set const empty;
    set const empty_c = ~empty;
    REQUIRE(empty_c.size() == 2u);
    REQUIRE(empty_c.membership(std::numeric_limits<int>::lowest()) == 1.0f);
    REQUIRE(empty_c.membership(0) == 1.0f);
    REQUIRE(empty_c.membership(std::numeric_limits<int>::max()) == 1.0f);
    
    // Common case.
    set const tri = make_triangle<float>(4,8,12);
    set const tri_c = ~tri;
    REQUIRE(tri_c.membership(std::numeric_limits<int>::lowest()) == 1.0f);
    REQUIRE(tri_c.membership(4) == 1.0f);
    REQUIRE(tri_c.membership(6) == 0.5f);
    REQUIRE(tri_c.membership(8) == 0.0f);
    REQUIRE(tri_c.membership(10) == 0.5f);
    REQUIRE(tri_c.membership(12) == 1.0f);
    REQUIRE(tri_c.membership(std::numeric_limits<int>::max()) == 1.0f);

    // Extreme boundary case
    set const eb_tri = make_triangle<float>(std::numeric_limits<int>::lowest(), 0, std::numeric_limits<int>::max());
    set const eb_tri_c = ~eb_tri;
    REQUIRE(eb_tri_c.membership(std::numeric_limits<int>::lowest()) == 1.0f);
    REQUIRE(eb_tri_c.membership(0) == 0.0f);
    REQUIRE(eb_tri_c.membership(std::numeric_limits<int>::max()) == 1.0f);

    // Near extreme boundary case
    set const neb_tri = make_triangle<float>(std::numeric_limits<int>::lowest() + 1, 0, std::numeric_limits<int>::max() - 1);
    set const neb_tri_c = ~neb_tri;
    REQUIRE(neb_tri_c.membership(std::numeric_limits<int>::lowest()) == 1.0f);
    REQUIRE(neb_tri_c.membership(std::numeric_limits<int>::lowest() + 1) == 1.0f);
    REQUIRE(neb_tri_c.membership(0) == 0.0f);
    REQUIRE(neb_tri_c.membership(std::numeric_limits<int>::max() - 1) == 1.0f);
    REQUIRE(neb_tri_c.membership(std::numeric_limits<int>::max()) == 1.0f);
}

TEST_CASE("SET-intersection", "[SET_intersection]")
{
    // Common case left-right
    set si_cc_lr = set_intersection(make_triangle<float>(3, 7, 11), make_triangle<float>(4, 8, 12));
    REQUIRE(si_cc_lr.membership(3) == 0.0f);
    REQUIRE(si_cc_lr.membership(4) == 0.0f);
    REQUIRE(si_cc_lr.membership(5) == 0.25f);
    REQUIRE(si_cc_lr.membership(6) == 0.50f);
    REQUIRE(si_cc_lr.membership(7) == 0.75f);
    REQUIRE(si_cc_lr.membership(8) == 0.75f);
    REQUIRE(si_cc_lr.membership(9) == 0.50f);
    REQUIRE(si_cc_lr.membership(10) == 0.25f);
    REQUIRE(si_cc_lr.membership(11) == 0.0f);
    REQUIRE(si_cc_lr.membership(12) == 0.0f);

    // Common case right-left
    set si_cc_rl = set_intersection(make_triangle<float>(4, 8, 12), make_triangle<float>(3, 7, 11));
    REQUIRE(si_cc_rl.membership(3) == 0.0f);
    REQUIRE(si_cc_rl.membership(4) == 0.0f);
    REQUIRE(si_cc_rl.membership(5) == 0.25f);
    REQUIRE(si_cc_rl.membership(6) == 0.50f);
    REQUIRE(si_cc_rl.membership(7) == 0.75f);
    REQUIRE(si_cc_rl.membership(8) == 0.75f);
    REQUIRE(si_cc_rl.membership(9) == 0.50f);
    REQUIRE(si_cc_rl.membership(10) == 0.25f);
    REQUIRE(si_cc_rl.membership(11) == 0.0f);
    REQUIRE(si_cc_rl.membership(12) == 0.0f);

    // Boundary case left-right
    set si_bc_lr = set_intersection(make_triangle<float>(4, 8, 12), make_triangle<float>(12, 16, 20));
    REQUIRE(si_bc_lr.membership(3) == 0.0f);
    REQUIRE(si_bc_lr.membership(4) == 0.0f);
    REQUIRE(si_bc_lr.membership(5) == 0.0f);
    REQUIRE(si_bc_lr.membership(11) == 0.0f);
    REQUIRE(si_bc_lr.membership(12) == 0.0f);
    REQUIRE(si_bc_lr.membership(13) == 0.0f);
    REQUIRE(si_bc_lr.membership(19) == 0.0f);
    REQUIRE(si_bc_lr.membership(20) == 0.0f);
    REQUIRE(si_bc_lr.membership(21) == 0.0f);

    set si_bc_rl = set_intersection(make_triangle<float>(12, 16, 20), make_triangle<float>(4, 8, 12));
    REQUIRE(si_bc_rl.membership(3) == 0.0f);
    REQUIRE(si_bc_rl.membership(4) == 0.0f);
    REQUIRE(si_bc_rl.membership(5) == 0.0f);
    REQUIRE(si_bc_rl.membership(11) == 0.0f);
    REQUIRE(si_bc_rl.membership(12) == 0.0f);
    REQUIRE(si_bc_rl.membership(13) == 0.0f);
    REQUIRE(si_bc_rl.membership(19) == 0.0f);
    REQUIRE(si_bc_rl.membership(20) == 0.0f);
    REQUIRE(si_bc_rl.membership(21) == 0.0f);

    // Boundary past each-other case
    set si_bp_lr = set_intersection(make_triangle<float>(-12, -8, -4), make_triangle<float>(12, 16, 20));
    REQUIRE(si_bp_lr.membership(-13) == 0.0f);
    REQUIRE(si_bp_lr.membership(-12) == 0.0f);
    REQUIRE(si_bp_lr.membership(-7) == 0.0f);
    REQUIRE(si_bp_lr.membership(-3) == 0.0f);
    REQUIRE(si_bp_lr.membership(11) == 0.0f);
    REQUIRE(si_bp_lr.membership(12) == 0.0f);
    REQUIRE(si_bp_lr.membership(17) == 0.0f);
    REQUIRE(si_bp_lr.membership(20) == 0.0f);
    REQUIRE(si_bp_lr.membership(21) == 0.0f);

    set si_bp_rl = set_intersection(make_triangle<float>(12, 16, 20), make_triangle<float>(-12, -8, -4));
    REQUIRE(si_bp_rl.membership(-13) == 0.0f);
    REQUIRE(si_bp_rl.membership(-12) == 0.0f);
    REQUIRE(si_bp_rl.membership(-7) == 0.0f);
    REQUIRE(si_bp_rl.membership(-3) == 0.0f);
    REQUIRE(si_bp_rl.membership(11) == 0.0f);
    REQUIRE(si_bp_rl.membership(12) == 0.0f);
    REQUIRE(si_bp_rl.membership(17) == 0.0f);
    REQUIRE(si_bp_rl.membership(20) == 0.0f);
    REQUIRE(si_bp_rl.membership(21) == 0.0f);
}

TEST_CASE("SET-union", "[SET_union]")
{
    // Common case 
    set su_cc_lr = set_union(make_triangle<float>(3, 7, 11), make_triangle<float>(4, 8, 12));
    REQUIRE(su_cc_lr.membership(3) == 0.0f);
    REQUIRE(su_cc_lr.membership(4) == 0.25f);
    REQUIRE(su_cc_lr.membership(5) == 0.50f);
    REQUIRE(su_cc_lr.membership(6) == 0.75f);
    REQUIRE(su_cc_lr.membership(7) == 1.0f);
    REQUIRE(su_cc_lr.membership(8) == 1.0f);
    REQUIRE(su_cc_lr.membership(9) == 0.75f);
    REQUIRE(su_cc_lr.membership(10) == 0.50f);
    REQUIRE(su_cc_lr.membership(11) == 0.25f);
    REQUIRE(su_cc_lr.membership(12) == 0.0f);

    set su_cc_rl = set_union(make_triangle<float>(4, 8, 12), make_triangle<float>(3, 7, 11));
    REQUIRE(su_cc_rl.membership(3) == 0.0f);
    REQUIRE(su_cc_rl.membership(4) == 0.25f);
    REQUIRE(su_cc_rl.membership(5) == 0.50f);
    REQUIRE(su_cc_rl.membership(6) == 0.75f);
    REQUIRE(su_cc_rl.membership(7) == 1.0f);
    REQUIRE(su_cc_rl.membership(8) == 1.0f);
    REQUIRE(su_cc_rl.membership(9) == 0.75f);
    REQUIRE(su_cc_rl.membership(10) == 0.50f);
    REQUIRE(su_cc_rl.membership(11) == 0.25f);
    REQUIRE(su_cc_rl.membership(12) == 0.0f);

    // Boundary case
    set su_bc_lr = set_union(make_triangle<float>(4, 8, 12), make_triangle<float>(12, 16, 20));
    REQUIRE(su_bc_lr.membership(3) == 0.0f);
    REQUIRE(su_bc_lr.membership(4) == 0.0f);
    REQUIRE(su_bc_lr.membership(5) == 0.25f);
    REQUIRE(su_bc_lr.membership(11) == 0.25f);
    REQUIRE(su_bc_lr.membership(12) == 0.0f);
    REQUIRE(su_bc_lr.membership(13) == 0.25f);
    REQUIRE(su_bc_lr.membership(16) == 1.0f);
    REQUIRE(su_bc_lr.membership(20) == 0.0f);
    REQUIRE(su_bc_lr.membership(21) == 0.0f);

    // Boundaries past each-other case
    set su_bp_lr = set_union(make_triangle<float>(-12, -8, -4), make_triangle<float>(12, 16, 20));
    REQUIRE(su_bp_lr.membership(-13) == 0.0f);
    REQUIRE(su_bp_lr.membership(-12) == 0.0f);
    REQUIRE(su_bp_lr.membership(-5) == 0.25f);
    REQUIRE(su_bp_lr.membership(-3) == 0.0f);
    REQUIRE(su_bp_lr.membership(11) == 0.0f);
    REQUIRE(su_bp_lr.membership(12) == 0.0f);
    REQUIRE(su_bp_lr.membership(16) == 1.0f);
    REQUIRE(su_bp_lr.membership(17) == 0.75f);
    REQUIRE(su_bp_lr.membership(20) == 0.0f);
    REQUIRE(su_bp_lr.membership(21) == 0.0f);

    set su_bp_rl = set_union(make_triangle<float>(12, 16, 20), make_triangle<float>(-12, -8, -4));
    REQUIRE(su_bp_rl.membership(-13) == 0.0f);
    REQUIRE(su_bp_rl.membership(-12) == 0.0f);
    REQUIRE(su_bp_rl.membership(-5) == 0.25f);
    REQUIRE(su_bp_rl.membership(-3) == 0.0f);
    REQUIRE(su_bp_rl.membership(11) == 0.0f);
    REQUIRE(su_bp_rl.membership(12) == 0.0f);
    REQUIRE(su_bp_rl.membership(16) == 1.0f);
    REQUIRE(su_bp_rl.membership(17) == 0.75f);
    REQUIRE(su_bp_rl.membership(20) == 0.0f);
    REQUIRE(su_bp_rl.membership(21) == 0.0f);
}

#ifdef FUZZY_USE_TLS_DEF_OPERATOR
TEST_CASE("current-tnorm")
{
    REQUIRE(detail::current_tnorm<float> == nullptr);
	{
		use_tnorm_t use_minimum{ minimum{} };
		auto minimum_binder = detail::current_tnorm<float>;
		REQUIRE(minimum_binder != nullptr);
		{
			use_tnorm_t use_hamacher_product{ hamacher_product{} };
			auto hamacher_product_binder = detail::current_tnorm<float>;
			REQUIRE(hamacher_product_binder != minimum_binder);
			{
				use_tnorm_t use_einstein_product{ einstein_product{} };
				auto einstein_product_binder = detail::current_tnorm<float>;
				REQUIRE(einstein_product_binder != hamacher_product_binder);
				{
					use_tnorm_t use_drastic_product{ drastic_product{} };
					auto drastic_product_binder = detail::current_tnorm<float>;
					REQUIRE(drastic_product_binder != einstein_product_binder);
				}
				REQUIRE(einstein_product_binder == detail::current_tnorm<float>);
			}
			REQUIRE(hamacher_product_binder == detail::current_tnorm<float>);
		}
		REQUIRE(minimum_binder == detail::current_tnorm<float>);
	}
	REQUIRE(detail::current_tnorm<float> == nullptr);
}

TEST_CASE("current-tconorm")
{
    REQUIRE(detail::current_tnorm<float> == nullptr);
    {
        use_tconorm_t use_maximum{ maximum{} };
        auto maximum_binder = detail::current_tconorm<float>;
        REQUIRE(maximum_binder != nullptr);
        {
            use_tconorm_t use_hamacher_sum{ hamacher_sum{} };
            auto hamacher_sum_binder = detail::current_tconorm<float>;
            REQUIRE(hamacher_sum_binder != maximum_binder);
            {
                use_tconorm_t use_einstein_sum{ einstein_sum{} };
                auto einstein_sum_binder = detail::current_tconorm<float>;
                REQUIRE(einstein_sum_binder != hamacher_sum_binder);
                {
                    use_tconorm_t use_drastic_sum{ drastic_sum{} };
                    auto drastic_sum_binder = detail::current_tconorm<float>;
                    REQUIRE(drastic_sum_binder != einstein_sum_binder);
                }
                REQUIRE(einstein_sum_binder == detail::current_tconorm<float>);
            }
            REQUIRE(hamacher_sum_binder == detail::current_tconorm<float>);
        }
        REQUIRE(maximum_binder == detail::current_tconorm<float>);
    }
    REQUIRE(detail::current_tconorm<float> == nullptr);
}

TEST_CASE("SET-somewhat", "[SET_somewhat]")
{
    // Common case 
    set cc = somewhat(make_triangle<float>(4, 12, 20));
    REQUIRE(cc.membership(4) == 0.0f);
    REQUIRE(cc.membership(6) == 0.5f);
    REQUIRE(cc.membership(8) == 0.70710678f);
    REQUIRE(cc.membership(10) == 0.8660254f);
    REQUIRE(cc.membership(12) == 1.0f);
    REQUIRE(cc.membership(14) == 0.8660254f);
    REQUIRE(cc.membership(16) == 0.70710678f);
    REQUIRE(cc.membership(18) == 0.5f);
    REQUIRE(cc.membership(20) == 0.0f);

    // Compact case
    set cpc = somewhat(make_triangle<float>(4, 8, 12));
    REQUIRE(cpc.membership(4) == 0.0f);
    REQUIRE(cpc.membership(5) == 0.5f);
    REQUIRE(cpc.membership(6) == 0.70710678f);
    REQUIRE(cpc.membership(7) == 0.8660254f);
    REQUIRE(cpc.membership(8) == 1.0f);
    REQUIRE(cpc.membership(9) == 0.8660254f);
    REQUIRE(cpc.membership(10) == 0.70710678f);
    REQUIRE(cpc.membership(11) == 0.5f);
    REQUIRE(cpc.membership(12) == 0.0f);

    // Constrained case
    set csc = somewhat(make_triangle<float>(4, 6, 8));
    REQUIRE(csc.membership(4) == 0.0f);
    REQUIRE(csc.membership(5) == 0.70710678f);
    REQUIRE(csc.membership(6) == 1.0f);
    REQUIRE(csc.membership(7) == 0.70710678f);
    REQUIRE(csc.membership(8) == 0.0f);

    // Extreme case
    set ec = somewhat(make_triangle<float>(4, 5, 6));
    REQUIRE(ec.membership(4) == 0.0f);
    REQUIRE(ec.membership(5) == 1.0f);
    REQUIRE(ec.membership(6) == 0.0f);

    // Non-uniform case.
    set nu = somewhat(set{ element{ 0, 0.0f },element{ 4, 0.25f },element{ 8, 0.5f },element{ 12, 0.75f },element{ 16, 0.4f },element{ 18, 0.0f } });
    REQUIRE(nu.membership(0) == 0.0f);
    REQUIRE(nu.membership(4) == 0.5f);
    REQUIRE(nu.membership(8) == 0.70710678f);
    REQUIRE(nu.membership(12) == 0.8660254f);
    REQUIRE(nu.membership(16) == 0.63245553f);
    REQUIRE(nu.membership(18) == 0.0f);
}

TEST_CASE("SET-verry", "[SET_verry]")
{
    // Common case 
    set cc = very(make_triangle<float>(4, 12, 20));
    REQUIRE(cc.membership(4) == 0.0f);
    REQUIRE(cc.membership(6) == 0.0625f);
    REQUIRE(cc.membership(8) == 0.25f);
    REQUIRE(cc.membership(10) == 0.5625f);
    REQUIRE(cc.membership(12) == 1.0f);
    REQUIRE(cc.membership(14) == 0.5625f);
    REQUIRE(cc.membership(16) == 0.25f);
    REQUIRE(cc.membership(18) == 0.0625f);
    REQUIRE(cc.membership(20) == 0.0f);

    // Compact case
    set cpc = very(make_triangle<float>(4, 8, 12));
    REQUIRE(cpc.membership(4) == 0.0f);
    REQUIRE(cpc.membership(5) == 0.0625f);
    REQUIRE(cpc.membership(6) == 0.25f);
    REQUIRE(cpc.membership(7) == 0.5625f);
    REQUIRE(cpc.membership(8) == 1.0f);
    REQUIRE(cpc.membership(9) == 0.5625f);
    REQUIRE(cpc.membership(10) == 0.25f);
    REQUIRE(cpc.membership(11) == 0.0625f);
    REQUIRE(cpc.membership(12) == 0.0f);

    // Constrained case
    set csc = very(make_triangle<float>(4, 6, 8));
    REQUIRE(csc.membership(4) == 0.0f);
    REQUIRE(csc.membership(5) == 0.25f);
    REQUIRE(csc.membership(6) == 1.0f);
    REQUIRE(csc.membership(7) == 0.25f);
    REQUIRE(csc.membership(8) == 0.0f);

    // Extreme case
    set ec = very(make_triangle<float>(4, 5, 6));
    REQUIRE(ec.membership(4) == 0.0f);
    REQUIRE(ec.membership(5) == 1.0f);
    REQUIRE(ec.membership(6) == 0.0f);

    // Non-uniform case.
    set nu = very(set{ element{ 0, 0.0f },element{ 4, 0.25f },element{ 8, 0.5f },element{ 12, 0.75f },element{ 16, 0.4f },element{ 18, 0.0f } });
    REQUIRE(nu.membership(0) == 0.0f);
    REQUIRE(nu.membership(4) == 0.0625f);
    REQUIRE(nu.membership(8) == 0.25f);
    REQUIRE(nu.membership(12) == 0.5625f);
    REQUIRE(nu.membership(16) == 0.16000001f);
    REQUIRE(nu.membership(18) == 0.0f);
}


#endif // FUZZY_USE_TLS_DEF_OPERATOR
