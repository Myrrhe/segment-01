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

#include "text/BlockInfoText.hpp"
#include "text/InfoText.hpp"
#include "Logger.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Blockinfotext", "[blockinfotext]")
{
    const auto block1 = segment01::BlockInfoText();
    REQUIRE(block1.getType() == segment01::NodeText::Type::BLOCKINFO);
    segment01::BlockInfoText block2 = block1;
    block2 = block1;
    REQUIRE(block1.isEqual(block2));
    REQUIRE(block1.getStr() == U"");
    REQUIRE(block1.toStr() == U"");
    REQUIRE(block1 == block2);
    REQUIRE(!(block1 != block2));
    const auto block3 =
        segment01::BlockInfoText(segment01::InfoText(nullptr, 30));
    auto block4 =
        segment01::BlockInfoText(U"cSize=30,leSpace=1;1,leSpaceFix=1,liSpace=1,"
                                 U"style=0,fColor=0,oColor=0,thick=0,error");
    // REQUIRE(!block4.isEqual(block2));
    REQUIRE(block4.getFont() == nullptr);
    REQUIRE(block4.getCharSize() == 30);
    REQUIRE(!std::get<0>(block4.getLetterSpacing()));
    REQUIRE_THAT(
        std::get<1>(block4.getLetterSpacing()),
        Catch::Matchers::WithinRel(1.0f, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        block4.getLineSpacingFactor(),
        Catch::Matchers::WithinRel(1.0f, segment01::Constant::m_epsilon_f));
    REQUIRE(block4.getStyle() == segment01::InfoText::Style::REGULAR);
    REQUIRE(block4.getFillColor() == sf::Color(0, 0, 0, 0));
    REQUIRE(block4.getOutlineColor() == sf::Color(0, 0, 0, 0));
    REQUIRE_THAT(
        block4.getThickness(),
        Catch::Matchers::WithinRel(0, segment01::Constant::m_epsilon_f));
    REQUIRE(
        !block4.isUsed(static_cast<uint64_t>(segment01::InfoText::Info::FONT)));
    REQUIRE(block4.getInfoText().getFont() == nullptr);
    REQUIRE(block4.isUseful());
    block4 += segment01::BlockInfoText();
    block4 += block4;
    // segment01::Logger().info(block4.toStr());
    block2.release();
}
