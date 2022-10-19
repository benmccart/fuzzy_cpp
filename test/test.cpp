#include "../include/fuzzy.hpp"
#include "./test.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>


using namespace fuzzy;

TEST_CASE("membership-bounds-check", "[boundscheck]")
{
    constexpr auto v0 = algabraic_product<>::apply(1.0f, 1.0f);
    constexpr auto v1 = algabraic_product<>::apply(0.0f, 0.0f);
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
    set item = { {4, 0.0f}, {8, 1.0f}, {std::numeric_limits<int>::max(), 1.0f} };
    REQUIRE(item.membership(2) == 0.0f);
    REQUIRE(item.membership(4) == 0.0f);
    REQUIRE(item.membership(6) == 0.5f);
    REQUIRE(item.membership(8) == 1.0f);
    REQUIRE(item.membership(12) == 1.0f);
    REQUIRE(item.membership(1200000) == 1.0f);

    REQUIRE(!item.empty());
    REQUIRE(item.size() == 3u);
    REQUIRE(all_ranges_valid(item));
    REQUIRE(item.find(element{ 0, 0.3f }) == item.cend());
    REQUIRE(item.find(element{ 8, 1.0f }) != item.cend());
    REQUIRE(!item.contains(0));
    REQUIRE(item.contains(4));
    REQUIRE(item.count(0) == 0);
    REQUIRE(item.count(4) == 1);
    REQUIRE(item.count(element{ std::numeric_limits<int>::max(), 0.3f }) == 0);
    REQUIRE(item.count(element{ std::numeric_limits<int>::max(), 1.0f }) == 1);
}

TEST_CASE("TR2-set", "[TR2_set]")
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

