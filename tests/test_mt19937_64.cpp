#include "Mt19937_64.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Mt19937", "[mt19937]")
{
    REQUIRE(segment01::Mt19937_64::max() == UINT64_MAX);
    auto rng1 = segment01::Mt19937_64();
    auto rng2 = segment01::Mt19937_64(0);
    REQUIRE(rng1() == 4'620'546'740'167'642'908ULL);
    REQUIRE(rng1() == 13'109'570'281'517'897'720ULL);
    REQUIRE(rng2() == 18'301'848'765'998'365'067ULL);
    auto rng3 = segment01::Mt19937_64(rng1);
    auto rng4 = rng1;
    auto rng5 = std::move(rng1);
    REQUIRE(rng3() == 17'462'938'647'148'434'322ULL);
    REQUIRE(rng4() == 17'462'938'647'148'434'322ULL);
    REQUIRE(rng5() == 17'462'938'647'148'434'322ULL);
}
