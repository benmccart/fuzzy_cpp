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
    REQUIRE(empty.find(element{ 0, 0.3f }) == empty.cend());
    REQUIRE(!empty.contains(0));
    REQUIRE(empty.count(0) == 0);
    REQUIRE(empty.count(element{ 0, 0.3f }) == 0);
    

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

