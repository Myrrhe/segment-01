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

#include "Mt1993764.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Mt19937", "[mt19937]")
{
    REQUIRE(segment01::Mt1993764::max() == UINT64_MAX);
    auto rng1 = segment01::Mt1993764();
    auto rng2 = segment01::Mt1993764(0);
    REQUIRE(rng1() == 4'620'546'740'167'642'908ULL);
    REQUIRE(rng1() == 13'109'570'281'517'897'720ULL);
    REQUIRE(rng2() == 18'301'848'765'998'365'067ULL);
    auto rng3 = segment01::Mt1993764(rng1);
    auto rng4 = rng1;
    auto rng5 = std::move(rng1);
    REQUIRE(rng3() == 17'462'938'647'148'434'322ULL);
    REQUIRE(rng4() == 17'462'938'647'148'434'322ULL);
    REQUIRE(rng5() == 17'462'938'647'148'434'322ULL);
}
