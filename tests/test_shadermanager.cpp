#include "ShaderManager.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("ShaderManager", "[shadermanager]")
{
    segment01::ShaderManager::initialize();
    segment01::ShaderManager::terminate();
}
