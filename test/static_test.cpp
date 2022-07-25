#include "../include/fuzzy.hpp"
#include "./test.hpp"

using namespace fuzzy;

void static_test_boundscheck()
{
    constexpr auto v0 = algabraic_product<>::apply(1.0f, 1.0f);
    constexpr auto v1 = algabraic_product<>::apply(0.0f, 0.0f);
    // FAIL constexpr auto v2 = algabraic_product<>::apply(-0.01f, 1.0f);
    // FAIL constexpr auto v0 = algabraic_product<>::apply(1.01f, 1.0f);
    
    constexpr bool validate = []() constexpr
    {
        validate_range(0.0);
        validate_range(0.5);
        validate_range(1.0);
        // FAIL validate_range(-0.00001);
        // FAIL validate_range( 1.00001);
        return true;
    }();
}

void static_test_tnormtests() 
{
    static_assert(algabraic_product<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(algabraic_product<>::apply(0.00f, 0.50f) == 0.00f, "");
    static_assert(algabraic_product<>::apply(0.00f, 1.00f) == 0.00f, "");
    static_assert(algabraic_product<>::apply(0.50f, 1.00f) == 0.50f, "");
    static_assert(algabraic_product<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(algabraic_product<>::apply(0.50f, 0.50f) == 0.25f, "");

    static_assert(bounded_difference<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(bounded_difference<>::apply(0.00f, 0.50f) == 0.00f, "");
    static_assert(bounded_difference<>::apply(0.00f, 1.00f) == 0.00f, "");
    static_assert(bounded_difference<>::apply(0.50f, 1.00f) == 0.50f, "");
    static_assert(bounded_difference<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(bounded_difference<>::apply(0.50f, 0.50f) == 0.00f, "");
    static_assert(bounded_difference<>::apply(0.75f, 0.75f) == 0.50f, "");

    static_assert(drastic_product<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(drastic_product<>::apply(0.00f, 0.50f) == 0.00f, "");
    static_assert(drastic_product<>::apply(0.00f, 1.00f) == 0.00f, "");
    static_assert(drastic_product<>::apply(0.50f, 1.00f) == 0.50f, "");
    static_assert(drastic_product<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(drastic_product<>::apply(0.50f, 0.50f) == 0.00f, "");

    static_assert(einstein_product<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(einstein_product<>::apply(0.00f, 0.50f) == 0.00f, "");
    static_assert(einstein_product<>::apply(0.00f, 1.00f) == 0.00f, "");
    static_assert(einstein_product<>::apply(0.50f, 1.00f) == 0.50f, "");
    static_assert(einstein_product<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(einstein_product<>::apply(0.50f, 0.50f) == 0.20f, "");

    static_assert(hamacher_product<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(hamacher_product<>::apply(0.00f, 0.50f) == 0.00f, "");
    static_assert(hamacher_product<>::apply(0.00f, 1.00f) == 0.00f, "");
    static_assert(hamacher_product<>::apply(0.50f, 1.00f) == 0.50f, "");
    static_assert(hamacher_product<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(hamacher_product<>::apply(0.50f, 0.50f) == 0.33333333f, "");

    static_assert(minimum<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(minimum<>::apply(0.00f, 0.50f) == 0.00f, "");
    static_assert(minimum<>::apply(0.00f, 1.00f) == 0.00f, "");
    static_assert(minimum<>::apply(0.50f, 1.00f) == 0.50f, "");
    static_assert(minimum<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(minimum<>::apply(0.50f, 0.50f) == 0.50f, "");
}

void static_test_tconormtests()
{
    static_assert(algabraic_sum<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(algabraic_sum<>::apply(0.00f, 0.50f) == 0.50f, "");
    static_assert(algabraic_sum<>::apply(0.00f, 1.00f) == 1.00f, "");
    static_assert(algabraic_sum<>::apply(0.50f, 1.00f) == 1.00f, "");
    static_assert(algabraic_sum<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(algabraic_sum<>::apply(0.50f, 0.50f) == 0.75f, "");

    static_assert(bounded_sum<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(bounded_sum<>::apply(0.00f, 0.50f) == 0.50f, "");
    static_assert(bounded_sum<>::apply(0.00f, 1.00f) == 1.00f, "");
    static_assert(bounded_sum<>::apply(0.50f, 1.00f) == 1.00f, "");
    static_assert(bounded_sum<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(bounded_sum<>::apply(0.50f, 0.50f) == 1.00f, "");
    static_assert(bounded_sum<>::apply(0.25f, 0.25f) == 0.50f, "");

    static_assert(drastic_sum<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(drastic_sum<>::apply(0.00f, 0.50f) == 0.50f, "");
    static_assert(drastic_sum<>::apply(0.00f, 1.00f) == 1.00f, "");
    static_assert(drastic_sum<>::apply(0.50f, 1.00f) == 1.00f, "");
    static_assert(drastic_sum<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(drastic_sum<>::apply(0.50f, 0.50f) == 1.00f, "");

    static_assert(einstein_sum<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(einstein_sum<>::apply(0.00f, 0.50f) == 0.50f, "");
    static_assert(einstein_sum<>::apply(0.00f, 1.00f) == 1.00f, "");
    static_assert(einstein_sum<>::apply(0.50f, 1.00f) == 1.00f, "");
    static_assert(einstein_sum<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(einstein_sum<>::apply(0.50f, 0.50f) == 0.80f, "");

    static_assert(hamacher_sum<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(hamacher_sum<>::apply(0.00f, 0.50f) == 0.50f, "");
    static_assert(hamacher_sum<>::apply(0.00f, 1.00f) == 1.00f, "");
    static_assert(hamacher_sum<>::apply(0.50f, 1.00f) == 1.00f, "");
    static_assert(hamacher_sum<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(hamacher_sum<>::apply(0.50f, 0.50f) == 0.66666666f, "");

    static_assert(maximum<>::apply(0.00f, 0.00f) == 0.00f, "");
    static_assert(maximum<>::apply(0.00f, 0.50f) == 0.50f, "");
    static_assert(maximum<>::apply(0.00f, 1.00f) == 1.00f, "");
    static_assert(maximum<>::apply(0.50f, 1.00f) == 1.00f, "");
    static_assert(maximum<>::apply(1.00f, 1.00f) == 1.00f, "");
    static_assert(maximum<>::apply(0.50f, 0.50f) == 0.50f, "");
}

void static_test_basic_elementtests()
{
    constexpr element e1{ 1, 1.0f };
    static_assert(e1.membership() == 1.0f, "");
    static_assert(e1.value() == 1, "");

    constexpr element e0{ 0, 0.0f };
    static_assert(e0.membership() == 0.0f, "");
    static_assert(e0.value() == 0, "");
    static_assert(e0 < e1, "");

    constexpr element eol{ 3, 0.4f };
    constexpr element eor{ 5, 0.4f };
    constexpr element ea = [](element const l, element const r) constexpr
    {
        return element{ l.value() + r.value(), l.membership() + r.membership() };
    }(eol, eor);

    static_assert(ea.value() == 8, "");
    static_assert(ea.membership() == 0.8f, "");

    // FAIL constexpr element em1{ -1, -1.0f };
    // FAIL constexpr element em1{ -1, -1.0001f };
    // FAIL constexpr element einf{ 1, std::numeric_limits<float>::infinity() };
    // FAIL constexprelement eninf{ -1, -std::numeric_limits<float>::infinity() };
}

consteval void static_test_empty_set()
{
    constexpr auto empty = []() { return set{}; };
    static_assert(empty().empty());
    static_assert(empty().size() == 0u);
    static_assert(all_ranges_valid(empty()));
}
 
consteval void static_test_TR0_test()
{
    constexpr auto item = []() { return make_triangle<float>(4, 8, 12); };
    static_assert(item().size() == 3);
    static_assert(all_ranges_valid(item()));
    static_assert(item().membership(4) == 0.0f);
    static_assert(item().membership(6) == 0.5f);
    static_assert(item().membership(8) == 1.0f);
    static_assert(item().membership(10) == 0.5f);
    static_assert(item().membership(12) == 0.0f);
}

consteval void static_test_TR1_set()
{
    constexpr auto item = []() 
    {
        set s = { {4, 0.0f}, {8, 1.0f}, {std::numeric_limits<int>::max(), 1.0f} };
        return s;
    };
    static_assert(item().membership(4) == 0.0f);
    static_assert(item().membership(6) == 0.5f);
    static_assert(item().membership(8) == 1.0f);
    static_assert(item().membership(12) == 1.0f);
    static_assert(item().membership(1200000) == 1.0f);
}

consteval void static_test_TR2_set()
{
    constexpr auto item = []() { return make_trapezoid<float>(4, 8, 12, 16); };
    static_assert(item().membership(2) == 0.0f);
    static_assert(item().membership(4) == 0.0f);
    static_assert(item().membership(6) == 0.5f);
    static_assert(item().membership(8) == 1.0f);
    static_assert(item().membership(10) == 1.0f);
    static_assert(item().membership(12) == 1.0f);
    static_assert(item().membership(14) == 0.5f);
    static_assert(item().membership(16) == 0.0f);
    static_assert(item().membership(18) == 0.0f);

    static_assert(!item().empty());
    static_assert(item().size() == 4u);
    static_assert(all_ranges_valid(item()));

    constexpr auto expr01 = []() 
    { 
        auto itm = item();
        return itm.find(element{ 0, 0.3f }) == itm.cend(); 
    };
    static_assert(expr01());

    constexpr auto expr02 = []() 
    {
        auto itm = item();
        return itm.find(element{8, 1.0f}) != itm.cend(); 
    };
    static_assert(expr02());

    constexpr auto expr03 = []()
    {
        auto itm = item();
        return *itm.find(element{ 8, 1.0f }) == element{ 8, 1.0f };
    };
    static_assert(expr03());

    static_assert(!item().contains(0));
    static_assert(item().contains(4));
    static_assert(item().count(0) == 0);
    static_assert(item().count(4) == 1);
    static_assert(item().count(element{8, 1.0f}) == 1);
    static_assert(item().count(element{std::numeric_limits<int>::max(), 0.3f}) == 0);
    static_assert(item().count(element{std::numeric_limits<int>::max(), 0.0f}) == 0);
}

