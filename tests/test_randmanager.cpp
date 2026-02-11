#include "RandManager.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Randmanager", "[randmanager]")
{
    segment01::RandManager::setMain(0, false, 0);
    REQUIRE(segment01::RandManager::getMainSeed() != 0);
    segment01::RandManager::setMain(0, true, 0);
    REQUIRE(segment01::RandManager::getMainSeed() == 0);
    REQUIRE(segment01::RandManager::getMax() == UINT64_MAX);
    REQUIRE(segment01::RandManager::getRand(0) ==
            18'301'848'765'998'365'067ULL);
}
