////////////////////////////////////////////////////////////
// A basic function library.
// Copyright (C) 2026  Myrrhe <email>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

#include "Logger.hpp"
#include "PathManager.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("PathManager", "[pathmanager]")
{
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
    segment01::Logger::setLevel(segment01::LogLevel::NONE);
    segment01::PathManager::read();
    segment01::Logger::setLevel(segment01::LogLevel::INFO);
}
