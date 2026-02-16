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
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Blockclosingtext", "[blockclosingtext]")
{
    const auto block1 = segment01::BlockClosingText();
    REQUIRE(block1.getType() == segment01::NodeText::Type::BLOCKCLOSING);
    segment01::BlockClosingText block2 = block1;
    block2 = block1;
    REQUIRE(block1.isEqual(block2));
    REQUIRE(block1.getStr() == U"");
    REQUIRE(block1.toStr() == U"</>");
    block2.release();
}
