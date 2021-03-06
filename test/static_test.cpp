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

    constexpr auto expr0 = []()
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
    static_assert([]() { set s = item(); return *s.lower_bound(0) == element{ 3, 1.0f }; }());
    static_assert([]() { set s = item(); return *s.lower_bound(3) == element{ 3, 1.0f }; }());
    static_assert([]() { set s = item(); return *s.lower_bound(4) == element{ 5, 0.8f }; }());
    static_assert([]() { set s = item(); return *s.lower_bound(5) == element{ 5, 0.8f }; }());
    static_assert([]() { set s = item(); return s.lower_bound(6) == s.end(); }());

    // lb on elements
    static_assert([]() { set s = item(); return *s.lower_bound(element{ 1, 0.0f }) == element{ 3, 1.0f }; }());
    static_assert([]() { set s = item(); return *s.lower_bound(element{ 3, 0.7f }) == element{ 3, 1.0f }; }());
    static_assert([]() { set s = item(); return *s.lower_bound(element{ 4, 1.0f }) == element{ 5, 0.8f }; }());
    static_assert([]() { set s = item(); return *s.lower_bound(element{ 5, 0.8f }) == element{ 5, 0.8f }; }());
    static_assert([]() { set s = item(); return s.lower_bound(element{ 6, 0.0f }) == s.end(); }());

    // lb on keys
    static_assert([]() { set const cs = item(); return *cs.lower_bound(0) == element{ 3, 1.0f }; }());
    static_assert([]() { set const cs = item(); return *cs.lower_bound(3) == element{ 3, 1.0f }; }());
    static_assert([]() { set const cs = item(); return *cs.lower_bound(4) == element{ 5, 0.8f }; }());
    static_assert([]() { set const cs = item(); return *cs.lower_bound(5) == element{ 5, 0.8f }; }());
    static_assert([]() { set const cs = item(); return cs.lower_bound(6) == cs.end(); }());

    // lb on elements
    static_assert([]() { set const cs = item(); return *cs.lower_bound(element{ 1, 0.0f }) == element{ 3, 1.0f }; }());
    static_assert([]() { set const cs = item(); return *cs.lower_bound(element{ 3, 0.7f }) == element{ 3, 1.0f }; }());
    static_assert([]() { set const cs = item(); return *cs.lower_bound(element{ 4, 1.0f }) == element{ 5, 0.8f }; }());
    static_assert([]() { set const cs = item(); return *cs.lower_bound(element{ 5, 0.8f }) == element{ 5, 0.8f }; }());
    static_assert([]() { set const cs = item(); return cs.lower_bound(element{ 6, 0.0f }) == cs.end(); }());
}
consteval void static_test_set_upperbound()
{
    constexpr auto item = []()
    {
        set s = { {3, 1.0f}, {5, 0.8f} };
        return s;
    };

    // lb on keys
    static_assert([]() { set s = item(); return *s.upper_bound(0) == element{ 3, 1.0f }; }());
    static_assert([]() { set s = item(); return *s.upper_bound(3) == element{ 5, 0.8f }; }());
    static_assert([]() { set s = item(); return *s.upper_bound(4) == element{ 5, 0.8f }; }());
    static_assert([]() { set s = item(); return s.upper_bound(5) == s.end(); }());
    static_assert([]() { set s = item(); return s.upper_bound(6) == s.end(); }());

    // lb on elements
    static_assert([]() { set s = item(); return *s.upper_bound(element{ 1, 0.0f }) == element{ 3, 1.0f }; }());
    static_assert([]() { set s = item(); return *s.upper_bound(element{ 3, 0.7f }) == element{ 5, 0.8f }; }());
    static_assert([]() { set s = item(); return *s.upper_bound(element{ 4, 1.0f }) == element{ 5, 0.8f }; }());
    static_assert([]() { set s = item(); return s.upper_bound(element{ 5, 0.8f }) == s.end(); }());
    static_assert([]() { set s = item(); return s.upper_bound(element{ 6, 0.0f }) == s.end(); }());

    // lb on keys
    static_assert([]() { set const cs = item(); return *cs.upper_bound(0) == element{ 3, 1.0f }; }());
    static_assert([]() { set const cs = item(); return *cs.upper_bound(3) == element{ 5, 0.8f }; }());
    static_assert([]() { set const cs = item(); return *cs.upper_bound(4) == element{ 5, 0.8f }; }());
    static_assert([]() { set const cs = item(); return cs.upper_bound(5) == cs.end(); }());
    static_assert([]() { set const cs = item(); return cs.upper_bound(6) == cs.end(); }());

    // lb on elements
    static_assert([]() { set const cs = item(); return *cs.upper_bound(element{ 1, 0.0f }) == element{ 3, 1.0f }; }());
    static_assert([]() { set const cs = item(); return *cs.upper_bound(element{ 3, 0.7f }) == element{ 5, 0.8f }; }());
    static_assert([]() { set const cs = item(); return *cs.upper_bound(element{ 4, 1.0f }) == element{ 5, 0.8f }; }());
    static_assert([]() { set const cs = item(); return cs.upper_bound(element{ 5, 0.8f }) == cs.end(); }());
    static_assert([]() { set const cs = item(); return cs.upper_bound(element{ 6, 0.0f }) == cs.end(); }());
}

consteval void static_test_set_find()
{
    // find on keys
    constexpr auto item = []() { return set{ {3, 1.0f}, {5, 0.8f} }; };
    static_assert([]() { set s = item(); return s.find(0) == s.end(); });
    static_assert([]() { set s = item(); return *s.find(3) == element{ 3, 1.0f }; });
    static_assert([]() { set s = item(); return s.find(4) == s.end(); });
    static_assert([]() { set s = item(); return *s.find(5) == element{ 5, 0.8f }; });
    static_assert([]() { set s = item(); return s.find(6) == s.end(); });

    static_assert([]() { set const cs = item(); return cs.find(0) == cs.end(); });
    static_assert([]() { set const cs = item(); return *cs.find(3) == element{ 3, 1.0f }; });
    static_assert([]() { set const cs = item(); return cs.find(4) == cs.end(); });
    static_assert([]() { set const cs = item(); return *cs.find(5) == element{ 5, 0.8f }; });
    static_assert([]() { set const cs = item(); return cs.find(6) == cs.end(); });

    // find on elements
    static_assert([]() { set s = item(); return s.find(element{ 0, 0.0f }) == s.end(); });
    static_assert([]() { set s = item(); return *s.find(element{ 3, 0.0f }) == element{ 3, 1.0f }; });
    static_assert([]() { set s = item(); return s.find(element{ 4, 0.0f }) == s.end(); });
    static_assert([]() { set s = item(); return *s.find(element{ 5, 0.8f }) == element{ 5, 0.8f }; });
    static_assert([]() { set s = item(); return s.find(element{ 6, 1.0f }) == s.end(); });

    static_assert([]() { set const cs = item(); return cs.find(element{ 0, 1.0f }) == cs.end(); });
    static_assert([]() { set const cs = item(); return *cs.find(element{ 3, 1.0f }) == element{ 3, 1.0f }; });
    static_assert([]() { set const cs = item(); return cs.find(element{ 4, 1.0f }) == cs.end(); });
    static_assert([]() { set const cs = item(); return *cs.find(element{ 5, 0.2f }) == element{ 5, 0.8f }; });
    static_assert([]() { set const cs = item(); return cs.find(element{ 6, 0.0f }) == cs.end(); });
}

consteval void static_test_set_contains()
{
    // find on keys
    constexpr auto cs = []() { return set{ {3, 1.0f}, {5, 0.8f} }; };
    static_assert(!cs().contains(0));
    static_assert(cs().contains(3));
    static_assert(!cs().contains(4));
    static_assert(cs().contains(5));
    static_assert(!cs().contains(6));

    // find on elements
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

