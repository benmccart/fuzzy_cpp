#include "../include/fuzzy.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>


using namespace fuzzy;

TEST_CASE("t-norms", "[tnorms]") 
{
    algabraic_sum s;
    s.apply(0.0, 1.0);
    REQUIRE(algabraic_product<float>::apply(0.0, 1.0) == 0.0);
    REQUIRE(algabraic_sum<>::apply(0.0, 1.0) == 1.0);
}
