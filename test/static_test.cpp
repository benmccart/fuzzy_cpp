#include "../include/fuzzy.hpp"
#include "./test.hpp"

using namespace fuzzy;

void static_test_boundscheck()
{
    [[maybe_unused]] constexpr auto v0 = algabraic_product<>::apply(1.0f, 1.0f);
    [[maybe_unused]] constexpr auto v1 = algabraic_product<>::apply(0.0f, 0.0f);
    // FAIL constexpr auto v2 = algabraic_product<>::apply(-0.01f, 1.0f);
    // FAIL constexpr auto v0 = algabraic_product<>::apply(1.01f, 1.0f);
    
    [[maybe_unused]] constexpr bool validate = []() constexpr
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
    static_assert(algabraic_product<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(algabraic_product<>::apply(0.00f, 0.50f) == 0.00f);
    static_assert(algabraic_product<>::apply(0.00f, 1.00f) == 0.00f);
    static_assert(algabraic_product<>::apply(0.50f, 1.00f) == 0.50f);
    static_assert(algabraic_product<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(algabraic_product<>::apply(0.50f, 0.50f) == 0.25f);

    static_assert(bounded_difference<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(bounded_difference<>::apply(0.00f, 0.50f) == 0.00f);
    static_assert(bounded_difference<>::apply(0.00f, 1.00f) == 0.00f);
    static_assert(bounded_difference<>::apply(0.50f, 1.00f) == 0.50f);
    static_assert(bounded_difference<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(bounded_difference<>::apply(0.50f, 0.50f) == 0.00f);
    static_assert(bounded_difference<>::apply(0.75f, 0.75f) == 0.50f);

    static_assert(drastic_product<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(drastic_product<>::apply(0.00f, 0.50f) == 0.00f);
    static_assert(drastic_product<>::apply(0.00f, 1.00f) == 0.00f);
    static_assert(drastic_product<>::apply(0.50f, 1.00f) == 0.50f);
    static_assert(drastic_product<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(drastic_product<>::apply(0.50f, 0.50f) == 0.00f);

    static_assert(einstein_product<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(einstein_product<>::apply(0.00f, 0.50f) == 0.00f);
    static_assert(einstein_product<>::apply(0.00f, 1.00f) == 0.00f);
    static_assert(einstein_product<>::apply(0.50f, 1.00f) == 0.50f);
    static_assert(einstein_product<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(einstein_product<>::apply(0.50f, 0.50f) == 0.20f);

    static_assert(hamacher_product<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(hamacher_product<>::apply(0.00f, 0.50f) == 0.00f);
    static_assert(hamacher_product<>::apply(0.00f, 1.00f) == 0.00f);
    static_assert(hamacher_product<>::apply(0.50f, 1.00f) == 0.50f);
    static_assert(hamacher_product<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(hamacher_product<>::apply(0.50f, 0.50f) == 0.33333333f);

    static_assert(minimum<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(minimum<>::apply(0.00f, 0.50f) == 0.00f);
    static_assert(minimum<>::apply(0.00f, 1.00f) == 0.00f);
    static_assert(minimum<>::apply(0.50f, 1.00f) == 0.50f);
    static_assert(minimum<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(minimum<>::apply(0.50f, 0.50f) == 0.50f);
}

void static_test_tconormtests()
{
    static_assert(algabraic_sum<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(algabraic_sum<>::apply(0.00f, 0.50f) == 0.50f);
    static_assert(algabraic_sum<>::apply(0.00f, 1.00f) == 1.00f);
    static_assert(algabraic_sum<>::apply(0.50f, 1.00f) == 1.00f);
    static_assert(algabraic_sum<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(algabraic_sum<>::apply(0.50f, 0.50f) == 0.75f);

    static_assert(bounded_sum<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(bounded_sum<>::apply(0.00f, 0.50f) == 0.50f);
    static_assert(bounded_sum<>::apply(0.00f, 1.00f) == 1.00f);
    static_assert(bounded_sum<>::apply(0.50f, 1.00f) == 1.00f);
    static_assert(bounded_sum<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(bounded_sum<>::apply(0.50f, 0.50f) == 1.00f);
    static_assert(bounded_sum<>::apply(0.25f, 0.25f) == 0.50f);

    static_assert(drastic_sum<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(drastic_sum<>::apply(0.00f, 0.50f) == 0.50f);
    static_assert(drastic_sum<>::apply(0.00f, 1.00f) == 1.00f);
    static_assert(drastic_sum<>::apply(0.50f, 1.00f) == 1.00f);
    static_assert(drastic_sum<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(drastic_sum<>::apply(0.50f, 0.50f) == 1.00f);

    static_assert(einstein_sum<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(einstein_sum<>::apply(0.00f, 0.50f) == 0.50f);
    static_assert(einstein_sum<>::apply(0.00f, 1.00f) == 1.00f);
    static_assert(einstein_sum<>::apply(0.50f, 1.00f) == 1.00f);
    static_assert(einstein_sum<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(einstein_sum<>::apply(0.50f, 0.50f) == 0.80f);

    static_assert(hamacher_sum<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(hamacher_sum<>::apply(0.00f, 0.50f) == 0.50f);
    static_assert(hamacher_sum<>::apply(0.00f, 1.00f) == 1.00f);
    static_assert(hamacher_sum<>::apply(0.50f, 1.00f) == 1.00f);
    static_assert(hamacher_sum<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(hamacher_sum<>::apply(0.50f, 0.50f) == 0.66666666f);

    static_assert(maximum<>::apply(0.00f, 0.00f) == 0.00f);
    static_assert(maximum<>::apply(0.00f, 0.50f) == 0.50f);
    static_assert(maximum<>::apply(0.00f, 1.00f) == 1.00f);
    static_assert(maximum<>::apply(0.50f, 1.00f) == 1.00f);
    static_assert(maximum<>::apply(1.00f, 1.00f) == 1.00f);
    static_assert(maximum<>::apply(0.50f, 0.50f) == 0.50f);
}

void static_test_basic_elementtests()
{
    constexpr element e1{ 1, 1.0f };
    static_assert(e1.membership() == 1.0f);
    static_assert(e1.value() == 1);

    constexpr element e0{ 0, 0.0f };
    static_assert(e0.membership() == 0.0f);
    static_assert(e0.value() == 0);
    static_assert(e0 < e1);

    constexpr element eol{ 3, 0.4f };
    constexpr element eor{ 5, 0.4f };
    constexpr element ea = [](element const l, element const r) constexpr
    {
        return element{ l.value() + r.value(), l.membership() + r.membership() };
    }(eol, eor);

    static_assert(ea.value() == 8);
    static_assert(ea.membership() == 0.8f);

    constexpr element ec{ e1 };
    static_assert(ec == e1);
    static_assert(ec != e0);

    constexpr auto expr0 = [=]()
    {
        element e{ 1, 0.1f };
        e = e0;
        return e;
    };
    constexpr element eca = expr0();
    static_assert(eca != e1);
    static_assert(eca == e0);

    constexpr auto expr1 = []()
    {
        element e0{ 0, 0.0f };
        element e{ std::move(e0) };
        return e;
    };
    constexpr element emc = expr1();
    static_assert(emc == element{ 0, 0.0f });
    static_assert(emc != element{ 1, 1.0f });

    constexpr auto expr2 = []()
    {
        element e{ 0, 0.0f };
        e = element{ 2, 0.2f };
        return e;
    };
    static_assert(expr2().value() == 2.0 && expr2().membership() == 0.2f);

    constexpr auto ema = element{ 2, 0.2f };
    static_assert(ema == element{ 2, 0.2f });
    static_assert(ema != element{ 2, 0.1f });

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


consteval void static_test_one_element_set()
{
    constexpr auto item = []()
    {
        set s = { {3, 1.0f} };
        return s;
    };
    static_assert(!item().empty());
    static_assert(item().size() == 1u);
    static_assert(all_ranges_valid(item()));
}

consteval void static_test_two_element_set()
{
    constexpr auto item = []()
    {
        set s2 = { {3, 1.0f}, {5, 1.0f} };
        return s2;
    };
    
    static_assert(!item().empty());
    static_assert(item().size() == 2u);
    static_assert(all_ranges_valid(item()));
}

consteval void static_test_set_equivalence()
{
    constexpr auto s1 = []() { return set{ { {3, 1.0f}, {5, 1.0f} } }; };
    constexpr auto s2 = []() { return set{ { {3, 1.0f}, {5, 1.0f} } }; };
    static_assert(s1() == s2());
    static_assert(s1() == set{{{3, 1.0f}, {5, 1.0f}}});
    static_assert(s1() != set{{{3, 1.0f}}});
    static_assert(s1() != set{{{5, 1.0f}}});
    static_assert(s1() != set{{{3, 0.999f}, {5, 1.0f}}});
    static_assert(s1() != set{{{3, 1.0f}, {5, 0.999f}}});
    static_assert(s1() != set{{{4, 1.0f}, {5, 1.0f}}});
    static_assert(s1() != set{{{3, 1.0f}, {4, 1.0f}}});
}

consteval void static_test_set_copy_construct()
{
    constexpr auto s1 = []() { return set{ { {3, 1.0f}, {5, 1.0f} } }; };
    constexpr auto s2 = []() 
    { 
        set s1{ {3, 1.0f}, {5, 1.0f} };
        set s2{ s1 };  return s2; 
    };
    static_assert(!s2().empty());
    static_assert(s2().size() == 2u);
    static_assert(all_ranges_valid(s2()));
    static_assert(s2() == s1());
    static_assert(s2() != set{{{3, 0.0f}, {4, 1.0f}}});
}

consteval void static_test_set_move_construct()
{
    constexpr auto s1 = []() { return set{ { {3, 1.0f}, {5, 1.0f} } }; };
    constexpr auto s2 = []()
    {
        set s1{ {3, 1.0f}, {5, 1.0f} };
        set s2{ std::move(s1) };  return s2;
    };
    static_assert(!s2().empty());
    static_assert(s2().size() == 2u);
    static_assert(all_ranges_valid(s2()));
    static_assert(s2() == s1());
    static_assert(s2() != set{ {{3, 0.0f}, {4, 1.0f}} });
}

consteval void static_test_set_assignment()
{
    constexpr auto s2 = []() 
    { 
        set s1{ {3, 1.0f}, {5, 1.0f} };
        set s2;
        s2 = s1;
        return s2;
    };
    static_assert(!s2().empty());
    static_assert(s2().size() == 2u);
    static_assert(all_ranges_valid(s2()));
    static_assert(s2() == set{{{3, 1.0f}, {5, 1.0f}}});

    constexpr auto s3 = []()
    {
        set s1{ {3, 1.0f}, {5, 1.0f} };
        set s3;
        s3 = std::move(s1);
        return s3;
    };
    static_assert(!s3().empty());
    static_assert(s3().size() == 2u);
    static_assert(all_ranges_valid(s3()));
    static_assert(s3() == set{{{3, 1.0f}, {5, 1.0f}}});

    constexpr auto s4 = []()
    {
        set s4;
        s4 = { {3, 1.0f}, {5, 1.0f} };
        return s4;
    };
    static_assert(!s4().empty());
    static_assert(s4().size() == 2u);
    static_assert(all_ranges_valid(s4()));
    static_assert(s4() == set{{{3, 1.0f}, {5, 1.0f}}});
}

consteval void static_test_set_lowerbound()
{
    constexpr auto item = []()
    {
        set s = { {3, 1.0f}, {5, 0.8f} };
        return s;
    };

    // lb on keys
    static_assert([&]() { set s = item(); return *s.lower_bound(0) == element{ 3, 1.0f }; }());
    static_assert([&]() { set s = item(); return *s.lower_bound(3) == element{ 3, 1.0f }; }());
    static_assert([&]() { set s = item(); return *s.lower_bound(4) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return *s.lower_bound(5) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return s.lower_bound(6) == s.end(); }());

    // lb on elements
    static_assert([&]() { set s = item(); return *s.lower_bound(element{ 1, 0.0f }) == element{ 3, 1.0f }; }());
    static_assert([&]() { set s = item(); return *s.lower_bound(element{ 3, 0.7f }) == element{ 3, 1.0f }; }());
    static_assert([&]() { set s = item(); return *s.lower_bound(element{ 4, 1.0f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return *s.lower_bound(element{ 5, 0.8f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return s.lower_bound(element{ 6, 0.0f }) == s.end(); }());

    // lb on keys
    static_assert([&]() { set const cs = item(); return *cs.lower_bound(0) == element{ 3, 1.0f }; }());
    static_assert([&]() { set const cs = item(); return *cs.lower_bound(3) == element{ 3, 1.0f }; }());
    static_assert([&]() { set const cs = item(); return *cs.lower_bound(4) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return *cs.lower_bound(5) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return cs.lower_bound(6) == cs.end(); }());

    // lb on elements
    static_assert([&]() { set const cs = item(); return *cs.lower_bound(element{ 1, 0.0f }) == element{ 3, 1.0f }; }());
    static_assert([&]() { set const cs = item(); return *cs.lower_bound(element{ 3, 0.7f }) == element{ 3, 1.0f }; }());
    static_assert([&]() { set const cs = item(); return *cs.lower_bound(element{ 4, 1.0f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return *cs.lower_bound(element{ 5, 0.8f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return cs.lower_bound(element{ 6, 0.0f }) == cs.end(); }());
}
consteval void static_test_set_upperbound()
{
    constexpr auto item = []()
    {
        set s = { {3, 1.0f}, {5, 0.8f} };
        return s;
    };

    // lb on keys
    static_assert([&]() { set s = item(); return *s.upper_bound(0) == element{ 3, 1.0f }; }());
    static_assert([&]() { set s = item(); return *s.upper_bound(3) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return *s.upper_bound(4) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return s.upper_bound(5) == s.end(); }());
    static_assert([&]() { set s = item(); return s.upper_bound(6) == s.end(); }());

    // lb on elements
    static_assert([&]() { set s = item(); return *s.upper_bound(element{ 1, 0.0f }) == element{ 3, 1.0f }; }());
    static_assert([&]() { set s = item(); return *s.upper_bound(element{ 3, 0.7f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return *s.upper_bound(element{ 4, 1.0f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return s.upper_bound(element{ 5, 0.8f }) == s.end(); }());
    static_assert([&]() { set s = item(); return s.upper_bound(element{ 6, 0.0f }) == s.end(); }());

    // lb on keys
    static_assert([&]() { set const cs = item(); return *cs.upper_bound(0) == element{ 3, 1.0f }; }());
    static_assert([&]() { set const cs = item(); return *cs.upper_bound(3) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return *cs.upper_bound(4) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return cs.upper_bound(5) == cs.end(); }());
    static_assert([&]() { set const cs = item(); return cs.upper_bound(6) == cs.end(); }());

    // lb on elements
    static_assert([&]() { set const cs = item(); return *cs.upper_bound(element{ 1, 0.0f }) == element{ 3, 1.0f }; }());
    static_assert([&]() { set const cs = item(); return *cs.upper_bound(element{ 3, 0.7f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return *cs.upper_bound(element{ 4, 1.0f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return cs.upper_bound(element{ 5, 0.8f }) == cs.end(); }());
    static_assert([&]() { set const cs = item(); return cs.upper_bound(element{ 6, 0.0f }) == cs.end(); }());
}

consteval void static_test_set_find()
{
    // find on keys
    constexpr auto item = []() { return set{ {3, 1.0f}, {5, 0.8f} }; };
    static_assert([&]() { set s = item(); return s.find(0) == s.end(); }());
    static_assert([&]() { set s = item(); return *s.find(3) == element{ 3, 1.0f }; }());
    static_assert([&]() { set s = item(); return s.find(4) == s.end(); }());
    static_assert([&]() { set s = item(); return *s.find(5) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return s.find(6) == s.end(); }());

    static_assert([&]() { set const cs = item(); return cs.find(0) == cs.end(); }());
    static_assert([&]() { set const cs = item(); return *cs.find(3) == element{ 3, 1.0f }; }());
    static_assert([&]() { set const cs = item(); return cs.find(4) == cs.end(); }());
    static_assert([&]() { set const cs = item(); return *cs.find(5) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return cs.find(6) == cs.end(); }());

    // find on elements
    static_assert([&]() { set s = item(); return s.find(element{ 0, 0.0f }) == s.end(); }());
    static_assert([&]() { set s = item(); return *s.find(element{ 3, 1.0f }) == element{ 3, 1.0f }; }());
    static_assert([&]() { set s = item(); return s.find(element{ 4, 0.0f }) == s.end(); }());
    static_assert([&]() { set s = item(); return *s.find(element{ 5, 0.8f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set s = item(); return s.find(element{ 6, 1.0f }) == s.end(); }());

    static_assert([&]() { set const cs = item(); return cs.find(element{ 0, 1.0f }) == cs.end(); }());
    static_assert([&]() { set const cs = item(); return *cs.find(element{ 3, 1.0f }) == element{ 3, 1.0f }; }());
    static_assert([&]() { set const cs = item(); return cs.find(element{ 4, 1.0f }) == cs.end(); }());
    static_assert([&]() { set const cs = item(); return *cs.find(element{ 5, 0.8f }) == element{ 5, 0.8f }; }());
    static_assert([&]() { set const cs = item(); return cs.find(element{ 6, 0.0f }) == cs.end(); }());
}

consteval void static_test_set_contains()
{
    // count on keys
    constexpr auto cs = []() { return set{ {3, 1.0f}, {5, 0.8f} }; };
    static_assert(!cs().contains(0));
    static_assert(cs().contains(3));
    static_assert(!cs().contains(4));
    static_assert(cs().contains(5));
    static_assert(!cs().contains(6));

    // count on elements
    static_assert(!cs().contains(element{ 0, 1.0f }));
    static_assert(cs().contains(element{ 3, 1.0f }));
    static_assert(!cs().contains(element{ 3, 0.7f }));
    static_assert(!cs().contains(element{ 4, 1.0f }));
    static_assert(cs().contains(element{ 5, 0.8f }));
    static_assert(!cs().contains(element{ 5, 1.0f }));
    static_assert(!cs().contains(element{ 6, 0.0f }));
}

consteval void static_test_set_count()
{
    // find on keys
    constexpr auto cs = []() { return set{ {3, 1.0f}, {5, 0.8f} }; };
    static_assert(cs().count(0) == 0u);
    static_assert(cs().count(3) == 1u);
    static_assert(cs().count(4) == 0u);
    static_assert(cs().count(5) == 1u);
    static_assert(cs().count(6) == 0u);

    // find on elements
    static_assert(cs().count(element{ 0, 1.0f }) == 0u);
    static_assert(cs().count(element{ 3, 1.0f }) == 1u);
    static_assert(cs().count(element{ 3, 0.7f }) == 0u);
    static_assert(cs().count(element{ 4, 1.0f }) == 0u);
    static_assert(cs().count(element{ 5, 0.8f }) == 1u);
    static_assert(cs().count(element{ 5, 1.0f }) == 0u);
    static_assert(cs().count(element{ 6, 0.0f }) == 0u);
}

consteval void static_set_insert()
{
    // insertion of elements.
    constexpr auto cs0 = []() 
    {
        set cs;
        cs.insert({ {3, 1.0f}, {5, 0.8f} });
        return cs;
    };

    static_assert(!cs0().contains(0));
    static_assert(cs0().contains(3));
    static_assert(!cs0().contains(4));
    static_assert(cs0().contains(5));
    static_assert(!cs0().contains(6));

    constexpr auto cs1 = [=]()
    {
        set cs = cs0();
        cs.insert({ {3, 1.0f}, {5, 0.8f} });
        return cs;
    };
    
    static_assert(cs1().count(0) == 0u);
    static_assert(cs1().count(3) == 1u);
    static_assert(cs1().count(4) == 0u);
    static_assert(cs1().count(5) == 1u);
    static_assert(cs1().count(6) == 0u);

    constexpr auto cs2 = [=]()
    {
        set cs = cs1();
        cs.insert(element{ 4, 0.4f });
        return cs;
    };
    static_assert(cs2().contains(4));

    constexpr auto cs3 = [=]()
    {
        set cs = cs2();
        cs.insert(cs.cend(), element{ 0, 0.3f });
        return cs;
    };
    static_assert(cs3().contains(0) == 1u);

    constexpr auto cs4 = [=]()
    {
        set cs = cs3();
        std::vector<element> const other = { {7, 1.0f}, {5, 0.0f}, {6, 0.6f} };
        cs.insert(cbegin(other), cend(other));
        return cs;
    };
    static_assert(cs4().contains(element{5, 0.8f}) && cs4().contains(element{6, 0.6f}) && cs4().contains(element{7, 1.0f}));

    constexpr auto cs5a = [=]()
    {
        set cs = cs4();
        auto pair1 = cs.insert(cs.begin(), element{ 4, 1.0f });
        return pair1.first != cs.end() && pair1.second == false;
    };
    static_assert(cs5a());
    
    constexpr auto cs5b = [=]()
    {
        set cs = cs4();
        auto pair2 = cs.insert(cs.end(), element{ -1, 0.1f });
        return pair2.first == cs.begin() && pair2.second == true;
    };
    static_assert(cs5b());
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

    static_assert(!item().empty());
    static_assert(item().size() == 3u);
    static_assert(all_ranges_valid(item()));
}

consteval void static_test_TR1_set()
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
}

consteval void static_test_SET_complement()
{
    // Default case.
    constexpr auto empty_c = []() { return ~set{}; };
    static_assert(empty_c().size() == 2u);
    static_assert(empty_c().membership(std::numeric_limits<int>::lowest()) == 1.0f);
    static_assert(empty_c().membership(0) == 1.0f);
    static_assert(empty_c().membership(std::numeric_limits<int>::max()) == 1.0f);

    // Common case.
    constexpr auto tri_c = []() { return ~make_triangle<float>(4, 8, 12); };
    static_assert(tri_c().membership(std::numeric_limits<int>::lowest()) == 1.0f);
    static_assert(tri_c().membership(4) == 1.0f);
    static_assert(tri_c().membership(6) == 0.5f);
    static_assert(tri_c().membership(8) == 0.0f);
    static_assert(tri_c().membership(10) == 0.5f);
    static_assert(tri_c().membership(12) == 1.0f);
    static_assert(tri_c().membership(std::numeric_limits<int>::max()) == 1.0f);

    //// Extreme boundary case
    constexpr auto eb_tri_c = []() { return ~make_triangle<float>(std::numeric_limits<int>::lowest(), 0, std::numeric_limits<int>::max()); };
    static_assert(eb_tri_c().membership(std::numeric_limits<int>::lowest()) == 1.0f);
    static_assert(eb_tri_c().membership(0) == 0.0f);
    static_assert(eb_tri_c().membership(std::numeric_limits<int>::max()) == 1.0f);

    //// Near extreme boundary case
    //set const neb_tri = make_triangle<float>(std::numeric_limits<int>::lowest() + 1, 0, std::numeric_limits<int>::max() - 1);
    constexpr auto neb_tri_c = []() { return ~make_triangle<float>(std::numeric_limits<int>::lowest() + 1, 0, std::numeric_limits<int>::max() - 1); };
    static_assert(neb_tri_c().membership(std::numeric_limits<int>::lowest()) == 1.0f);
    static_assert(neb_tri_c().membership(std::numeric_limits<int>::lowest() + 1) == 1.0f);
    static_assert(neb_tri_c().membership(0) == 0.0f);
    static_assert(neb_tri_c().membership(std::numeric_limits<int>::max() - 1) == 1.0f);
    static_assert(neb_tri_c().membership(std::numeric_limits<int>::max()) == 1.0f);
}

consteval void static_test_SET_intersection()
{
    // Common case left-right
    constexpr auto si_cc_lr = []() { return set_intersection(make_triangle<float>(3, 7, 11), make_triangle<float>(4, 8, 12)); };
    static_assert(si_cc_lr().membership(3) == 0.0f);
    static_assert(si_cc_lr().membership(4) == 0.0f);
    static_assert(si_cc_lr().membership(5) == 0.25f);
    static_assert(si_cc_lr().membership(6) == 0.50f);
    static_assert(si_cc_lr().membership(7) == 0.75f);
    static_assert(si_cc_lr().membership(8) == 0.75f);
    static_assert(si_cc_lr().membership(9) == 0.50f);
    static_assert(si_cc_lr().membership(10) == 0.25f);
    static_assert(si_cc_lr().membership(11) == 0.0f);
    static_assert(si_cc_lr().membership(12) == 0.0f);

    // Common case right-left
    constexpr auto si_cc_rl = []() { return set_intersection(make_triangle<float>(4, 8, 12), make_triangle<float>(3, 7, 11)); };
    static_assert(si_cc_rl().membership(3) == 0.0f);
    static_assert(si_cc_rl().membership(4) == 0.0f);
    static_assert(si_cc_rl().membership(5) == 0.25f);
    static_assert(si_cc_rl().membership(6) == 0.50f);
    static_assert(si_cc_rl().membership(7) == 0.75f);
    static_assert(si_cc_rl().membership(8) == 0.75f);
    static_assert(si_cc_rl().membership(9) == 0.50f);
    static_assert(si_cc_rl().membership(10) == 0.25f);
    static_assert(si_cc_rl().membership(11) == 0.0f);
    static_assert(si_cc_rl().membership(12) == 0.0f);

    // Boundary case left-right
    constexpr auto si_bc_lr = []() { return set_intersection(make_triangle<float>(4, 8, 12), make_triangle<float>(12, 16, 20)); };
    static_assert(si_bc_lr().membership(3) == 0.0f);
    static_assert(si_bc_lr().membership(4) == 0.0f);
    static_assert(si_bc_lr().membership(5) == 0.0f);
    static_assert(si_bc_lr().membership(11) == 0.0f);
    static_assert(si_bc_lr().membership(12) == 0.0f);
    static_assert(si_bc_lr().membership(13) == 0.0f);
    static_assert(si_bc_lr().membership(19) == 0.0f);
    static_assert(si_bc_lr().membership(20) == 0.0f);
    static_assert(si_bc_lr().membership(21) == 0.0f);

    constexpr auto si_bc_rl = []() { return set_intersection(make_triangle<float>(12, 16, 20), make_triangle<float>(4, 8, 12)); };
    static_assert(si_bc_rl().membership(3) == 0.0f);
    static_assert(si_bc_rl().membership(4) == 0.0f);
    static_assert(si_bc_rl().membership(5) == 0.0f);
    static_assert(si_bc_rl().membership(11) == 0.0f);
    static_assert(si_bc_rl().membership(12) == 0.0f);
    static_assert(si_bc_rl().membership(13) == 0.0f);
    static_assert(si_bc_rl().membership(19) == 0.0f);
    static_assert(si_bc_rl().membership(20) == 0.0f);
    static_assert(si_bc_rl().membership(21) == 0.0f);

    // Boundary past each-other case
    constexpr auto si_bp_lr = []() { return set_intersection(make_triangle<float>(-12, -8, -4), make_triangle<float>(12, 16, 20)); };
    static_assert(si_bp_lr().membership(-13) == 0.0f);
    static_assert(si_bp_lr().membership(-12) == 0.0f);
    static_assert(si_bp_lr().membership(-7) == 0.0f);
    static_assert(si_bp_lr().membership(-3) == 0.0f);
    static_assert(si_bp_lr().membership(11) == 0.0f);
    static_assert(si_bp_lr().membership(12) == 0.0f);
    static_assert(si_bp_lr().membership(17) == 0.0f);
    static_assert(si_bp_lr().membership(20) == 0.0f);
    static_assert(si_bp_lr().membership(21) == 0.0f);

    constexpr auto si_bp_rl = []() { return set_intersection(make_triangle<float>(12, 16, 20), make_triangle<float>(-12, -8, -4)); };
    static_assert(si_bp_rl().membership(-13) == 0.0f);
    static_assert(si_bp_rl().membership(-12) == 0.0f);
    static_assert(si_bp_rl().membership(-7) == 0.0f);
    static_assert(si_bp_rl().membership(-3) == 0.0f);
    static_assert(si_bp_rl().membership(11) == 0.0f);
    static_assert(si_bp_rl().membership(12) == 0.0f);
    static_assert(si_bp_rl().membership(17) == 0.0f);
    static_assert(si_bp_rl().membership(20) == 0.0f);
    static_assert(si_bp_rl().membership(21) == 0.0f);
}

consteval void static_test_SET_union()
{
    // Common case 
    constexpr auto su_cc_lr = []() { return set_union(make_triangle<float>(3, 7, 11), make_triangle<float>(4, 8, 12)); };
    static_assert(su_cc_lr().membership(3) == 0.0f);
    static_assert(su_cc_lr().membership(4) == 0.25f);
    static_assert(su_cc_lr().membership(5) == 0.50f);
    static_assert(su_cc_lr().membership(6) == 0.75f);
    static_assert(su_cc_lr().membership(7) == 1.0f);
    static_assert(su_cc_lr().membership(8) == 1.0f);
    static_assert(su_cc_lr().membership(9) == 0.75f);
    static_assert(su_cc_lr().membership(10) == 0.50f);
    static_assert(su_cc_lr().membership(11) == 0.25f);
    static_assert(su_cc_lr().membership(12) == 0.0f);

    constexpr auto su_cc_rl = []() { return set_union(make_triangle<float>(4, 8, 12), make_triangle<float>(3, 7, 11)); };
    static_assert(su_cc_rl().membership(3) == 0.0f);
    static_assert(su_cc_rl().membership(4) == 0.25f);
    static_assert(su_cc_rl().membership(5) == 0.50f);
    static_assert(su_cc_rl().membership(6) == 0.75f);
    static_assert(su_cc_rl().membership(7) == 1.0f);
    static_assert(su_cc_rl().membership(8) == 1.0f);
    static_assert(su_cc_rl().membership(9) == 0.75f);
    static_assert(su_cc_rl().membership(10) == 0.50f);
    static_assert(su_cc_rl().membership(11) == 0.25f);
    static_assert(su_cc_rl().membership(12) == 0.0f);

    // Boundary case
    constexpr auto su_bc_lr = [](){ return set_union(make_triangle<float>(4, 8, 12), make_triangle<float>(12, 16, 20)); };
    static_assert(su_bc_lr().membership(3) == 0.0f);
    static_assert(su_bc_lr().membership(4) == 0.0f);
    static_assert(su_bc_lr().membership(5) == 0.25f);
    static_assert(su_bc_lr().membership(11) == 0.25f);
    static_assert(su_bc_lr().membership(12) == 0.0f);
    static_assert(su_bc_lr().membership(13) == 0.25f);
    static_assert(su_bc_lr().membership(16) == 1.0f);
    static_assert(su_bc_lr().membership(20) == 0.0f);
    static_assert(su_bc_lr().membership(21) == 0.0f);

    // Boundaries past each-other case
    constexpr auto su_bp_lr = []() { return set_union(make_triangle<float>(-12, -8, -4), make_triangle<float>(12, 16, 20)); };
    static_assert(su_bp_lr().membership(-13) == 0.0f);
    static_assert(su_bp_lr().membership(-12) == 0.0f);
    static_assert(su_bp_lr().membership(-5) == 0.25f);
    static_assert(su_bp_lr().membership(-3) == 0.0f);
    static_assert(su_bp_lr().membership(11) == 0.0f);
    static_assert(su_bp_lr().membership(12) == 0.0f);
    static_assert(su_bp_lr().membership(16) == 1.0f);
    static_assert(su_bp_lr().membership(17) == 0.75f);
    static_assert(su_bp_lr().membership(20) == 0.0f);
    static_assert(su_bp_lr().membership(21) == 0.0f);

    constexpr auto su_bp_rl = []() { return set_union(make_triangle<float>(12, 16, 20), make_triangle<float>(-12, -8, -4)); };
    static_assert(su_bp_rl().membership(-13) == 0.0f);
    static_assert(su_bp_rl().membership(-12) == 0.0f);
    static_assert(su_bp_rl().membership(-5) == 0.25f);
    static_assert(su_bp_rl().membership(-3) == 0.0f);
    static_assert(su_bp_rl().membership(11) == 0.0f);
    static_assert(su_bp_rl().membership(12) == 0.0f);
    static_assert(su_bp_rl().membership(16) == 1.0f);
    static_assert(su_bp_rl().membership(17) == 0.75f);
    static_assert(su_bp_rl().membership(20) == 0.0f);
    static_assert(su_bp_rl().membership(21) == 0.0f);
}

consteval void static_test_Relation()
{
    constexpr auto rel = [](int d, int r)
    {
        set large = make_triangle<float>(1200, 1600, 2000);
        set strong = make_triangle<float>(1600, 2000, 2400);
        relation rel{ large, strong, minimum{} };
        return rel.membership(d, r);
    };

    static_assert(rel(1200, 1600) == 0.0f);
    static_assert(rel(1200, 2000) == 0.0f);
    static_assert(rel(1400, 1800) == 0.5f);
    static_assert(rel(1600, 2000) == 1.0f);
    static_assert(rel(1700, 1900) == 0.75f);
    static_assert(rel(1900, 2200) == 0.25f);
    static_assert(rel(1100, 1900) == 0.0f);
}





