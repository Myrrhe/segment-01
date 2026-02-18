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

#include "text/BlockClosingText.hpp"
#include "text/LeafText.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Leaftext", "[leaftext]")
{
    const auto leaf1 = segment01::LeafText();
    auto leaf2 = segment01::LeafText(U"Hello world");
    auto leaf3 = segment01::LeafText(leaf2);
    leaf2 = leaf1;
    REQUIRE(leaf1.getType() == segment01::NodeText::Type::LEAF);
    REQUIRE(leaf1.isEmpty());
    REQUIRE(!leaf3.isEmpty());
    REQUIRE(leaf3.getStr() == U"Hello world");
    REQUIRE(leaf3.toStr() == U"Hello world");
    REQUIRE(leaf3.getSize() == 11);
    REQUIRE(leaf1.isEqual(leaf2));
    REQUIRE(!leaf1.isEqual(leaf3));
    const auto block1 = segment01::BlockClosingText();
    REQUIRE(!leaf1.isEqual(block1));
    REQUIRE(leaf1 == leaf2);
    REQUIRE(!(leaf1 == leaf3));
    REQUIRE(leaf1 != leaf3);
    leaf3.release();
}
