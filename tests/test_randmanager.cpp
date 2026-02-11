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
