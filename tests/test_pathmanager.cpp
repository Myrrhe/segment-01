#include "Logger.hpp"
#include "PathManager.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("PathManager", "[pathmanager]")
{
    segment01::PathManager::setPath("build/debug.exe");
    REQUIRE(segment01::PathManager::getPath(
                segment01::PathManager::Dir::ROOT) == "");
    REQUIRE(segment01::PathManager::getPath(segment01::PathManager::Dir::DAT) ==
            "assets");
    REQUIRE(segment01::PathManager::getPath(segment01::PathManager::Dir::IMG) ==
            "assets\\img");
    REQUIRE(segment01::PathManager::getPath(
                segment01::PathManager::Dir::SHADER) == "assets\\shaders");
    REQUIRE(segment01::PathManager::getPath(
                segment01::PathManager::Dir::SHADER_FRAG) ==
            "assets\\shaders\\frag");
    REQUIRE(segment01::PathManager::getPath(
                segment01::PathManager::Dir::SHADER_VERT) ==
            "assets\\shaders\\vert");
    REQUIRE(segment01::PathManager::getPath(
                segment01::PathManager::Dir::SOUND) == "assets\\sound");
    REQUIRE(segment01::PathManager::getPath(
                segment01::PathManager::Dir::FONT) == "assets\\font");
    REQUIRE(segment01::PathManager::getPath(
                segment01::PathManager::Dir::SCREENSHOT) ==
            "assets\\screenshot");
//     segment01::Logger::setLevel(segment01::LogLevel::NONE);
//     segment01::PathManager::read();
//     segment01::Logger::setLevel(segment01::LogLevel::INFO);
}
