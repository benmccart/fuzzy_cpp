#include "../include/fuzzy.hpp"

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

    // FAIL constexpr element em1{ -1, -1.0f };
    // FAIL constexpr element em1{ -1, -1.0001f };
    // FAIL constexpr element einf{ 1, std::numeric_limits<float>::infinity() };
    // FAIL constexprelement eninf{ -1, -std::numeric_limits<float>::infinity() };
}