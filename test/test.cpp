#include "../include/fuzzy.hpp"

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
