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

#include "text/BlockText.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Blocktext", "[blocktext]")
{
    const auto block1 = segment01::BlockText();
    REQUIRE(block1.getType() == segment01::NodeText::Type::BLOCK);
    segment01::BlockText block2 = block1;
    block2 = block1;
    const auto block3 = segment01::BlockText(U"");
    const auto block4 = segment01::BlockText(U"test");
    REQUIRE(block1.isEqual(block2));
    REQUIRE(block1.getStr() == U"");
    REQUIRE(block1.toStr() == U"");
    REQUIRE(block1 == block2);
    REQUIRE(!(block1 != block2));
    block2.release();
}
