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

#include "text/InfoText.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Infotext", "[infotext]")
{
    const auto info1 = segment01::InfoText();
    auto info2 = info1;
    info2 = info1;
    const auto info3 = segment01::InfoText(nullptr, 30);
    auto info4 = segment01::InfoText(
        U"cSize=30,leSpace=1;1,leSpaceFix=1,liSpace=1,style="
        U"0,fColor=0,oColor=0,thick=0,error");

    REQUIRE(info4.getFont() == nullptr);
    REQUIRE(info4.getCharSize() == segment01::InfoText::DefaultSize);
    REQUIRE(!std::get<0>(info4.getLetterSpacing()));
    REQUIRE_THAT(
        std::get<1>(info4.getLetterSpacing()),
        Catch::Matchers::WithinRel(1.0f, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        info4.getLineSpacingFactor(),
        Catch::Matchers::WithinRel(1.0f, segment01::Constant::m_epsilon_f));
    REQUIRE(info4.getStyle() == segment01::InfoText::Style::REGULAR);
    REQUIRE(info4.getFillColor() == sf::Color(0, 0, 0, 0));
    REQUIRE(info4.getOutlineColor() == sf::Color(0, 0, 0, 0));
    REQUIRE_THAT(
        info4.getThickness(),
        Catch::Matchers::WithinRel(0, segment01::Constant::m_epsilon_f));

    info4.setFont(nullptr);
    info4.setCharSize(segment01::InfoText::DefaultSize);
    info4.setLetterSpacing({true, 0});
    info4.setLineSpacingFactor(1);
    info4.setStyle(segment01::InfoText::Style::BOLD);
    info4.setFillColor(sf::Color(segment01::Constant::MaxColor, 0, 0,
                                 segment01::Constant::MaxColor));
    info4.setOutlineColor(sf::Color(0, segment01::Constant::MaxColor, 0,
                                    segment01::Constant::MaxColor));
    info4.setThickness(1);

    REQUIRE(info4.getFont() == nullptr);
    REQUIRE(info4.getCharSize() == segment01::InfoText::DefaultSize);
    REQUIRE(std::get<0>(info4.getLetterSpacing()));
    REQUIRE_THAT(
        std::get<1>(info4.getLetterSpacing()),
        Catch::Matchers::WithinRel(0, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        info4.getLineSpacingFactor(),
        Catch::Matchers::WithinRel(1.0f, segment01::Constant::m_epsilon_f));
    REQUIRE(info4.getStyle() == segment01::InfoText::Style::BOLD);
    REQUIRE(info4.getFillColor() == sf::Color(segment01::Constant::MaxColor, 0,
                                              0,
                                              segment01::Constant::MaxColor));
    REQUIRE(info4.getOutlineColor() ==
            sf::Color(0, segment01::Constant::MaxColor, 0,
                      segment01::Constant::MaxColor));
    REQUIRE_THAT(
        info4.getThickness(),
        Catch::Matchers::WithinRel(1.0f, segment01::Constant::m_epsilon_f));

    info4.setInfo<segment01::InfoText::Info::FONT>(nullptr);
    info4.setInfo<segment01::InfoText::Info::CHAR_SIZE>(
        segment01::InfoText::DefaultSize - 1);
    info4.setInfo<segment01::InfoText::Info::LETTER_SPACING>({false, 1});
    info4.setInfo<segment01::InfoText::Info::LINE_SPACING_FACTOR>(0);
    info4.setInfo<segment01::InfoText::Info::STYLE>(
        segment01::InfoText::Style::ITALIC);
    info4.setInfo<segment01::InfoText::Info::FILL_COLOR>(sf::Color(
        0, segment01::Constant::MaxColor, 0, segment01::Constant::MaxColor));
    info4.setInfo<segment01::InfoText::Info::OUTLINE_COLOR>(sf::Color(
        segment01::Constant::MaxColor, 0, 0, segment01::Constant::MaxColor));
    info4.setInfo<segment01::InfoText::Info::THICKNESS>(0);

    REQUIRE(info4.getInfo<segment01::InfoText::Info::FONT>() == nullptr);
    REQUIRE(info4.getInfo<segment01::InfoText::Info::CHAR_SIZE>() ==
            segment01::InfoText::DefaultSize - 1);
    REQUIRE(!std::get<0>(
        info4.getInfo<segment01::InfoText::Info::LETTER_SPACING>()));
    REQUIRE_THAT(
        std::get<1>(info4.getInfo<segment01::InfoText::Info::LETTER_SPACING>()),
        Catch::Matchers::WithinRel(1, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        info4.getInfo<segment01::InfoText::Info::LINE_SPACING_FACTOR>(),
        Catch::Matchers::WithinRel(0, segment01::Constant::m_epsilon_f));
    REQUIRE(info4.getInfo<segment01::InfoText::Info::STYLE>() ==
            segment01::InfoText::Style::ITALIC);
    REQUIRE(info4.getInfo<segment01::InfoText::Info::FILL_COLOR>() ==
            sf::Color(0, segment01::Constant::MaxColor, 0,
                      segment01::Constant::MaxColor));
    REQUIRE(info4.getInfo<segment01::InfoText::Info::OUTLINE_COLOR>() ==
            sf::Color(segment01::Constant::MaxColor, 0, 0,
                      segment01::Constant::MaxColor));
    REQUIRE_THAT(
        info4.getInfo<segment01::InfoText::Info::THICKNESS>(),
        Catch::Matchers::WithinRel(0, segment01::Constant::m_epsilon_f));

    REQUIRE(info4.getValStr(segment01::InfoText::Info::FONT) == U"");
    REQUIRE(info4.getValStr(segment01::InfoText::Info::CHAR_SIZE) == U"29");
    REQUIRE(info4.getValStr(segment01::InfoText::Info::LETTER_SPACING) ==
            U"0;1");
    REQUIRE(info4.getValStr(segment01::InfoText::Info::LINE_SPACING_FACTOR) ==
            U"0");
    REQUIRE(info4.getValStr(segment01::InfoText::Info::STYLE) == U"2");
    REQUIRE(info4.getValStr(segment01::InfoText::Info::FILL_COLOR) ==
            U"ff00ff");
    REQUIRE(info4.getValStr(segment01::InfoText::Info::OUTLINE_COLOR) ==
            U"ff0000ff");
    REQUIRE(info4.getValStr(segment01::InfoText::Info::THICKNESS) == U"0");

    REQUIRE(segment01::InfoText::getKeyStr32(segment01::InfoText::Info::FONT) ==
            U"font");
    REQUIRE(segment01::InfoText::getKeyStr32(
                segment01::InfoText::Info::CHAR_SIZE) == U"cSize");
    REQUIRE(segment01::InfoText::getKeyStr32(
                segment01::InfoText::Info::LETTER_SPACING) == U"leSpace");
    REQUIRE(segment01::InfoText::getKeyStr32(
                segment01::InfoText::Info::LINE_SPACING_FACTOR) == U"liSpace");
    REQUIRE(segment01::InfoText::getKeyStr32(
                segment01::InfoText::Info::STYLE) == U"style");
    REQUIRE(segment01::InfoText::getKeyStr32(
                segment01::InfoText::Info::FILL_COLOR) == U"fColor");
    REQUIRE(segment01::InfoText::getKeyStr32(
                segment01::InfoText::Info::OUTLINE_COLOR) == U"oColor");
    REQUIRE(segment01::InfoText::getKeyStr32(
                segment01::InfoText::Info::THICKNESS) == U"thick");

    segment01::InfoText::Info infoType = segment01::InfoText::Info::CHAR_SIZE;
    REQUIRE(++infoType == segment01::InfoText::Info::LETTER_SPACING);
    REQUIRE(infoType++ == segment01::InfoText::Info::LETTER_SPACING);
    REQUIRE(infoType == segment01::InfoText::Info::LINE_SPACING_FACTOR);

    REQUIRE((segment01::InfoText::Style::BOLD |
             segment01::InfoText::Style::ITALIC) == 3);
    REQUIRE((segment01::InfoText::Style::BOLD |
             segment01::InfoText::Style::ITALIC |
             segment01::InfoText::Style::UNDERLINED) == 7);
    REQUIRE((segment01::InfoText::Style::BOLD &
             segment01::InfoText::Style::BOLD) == 1);
    REQUIRE((segment01::InfoText::Style::BOLD &
             segment01::InfoText::Style::ITALIC) == 0);

    std::ostringstream oss;
    oss << segment01::InfoText::Style::BOLD;
    REQUIRE(oss.str() == "1");

    info4 = info3;
    REQUIRE(info4 == info3);
    info4.setCharSize(info3.getCharSize() - 1);
    REQUIRE(info4 != info3);
    info4.setCharSize(info3.getCharSize());
    info4.setLetterSpacing({false, 1});
    REQUIRE(info4 != info3);
    info4.setLetterSpacing({true, 0});
    REQUIRE(info4 != info3);
    info4.setLetterSpacing(info3.getLetterSpacing());
    info4.setLineSpacingFactor(0);
    REQUIRE(info4 != info3);
    info4.setLineSpacingFactor(info3.getLineSpacingFactor());
    info4.setStyle(segment01::InfoText::Style::ITALIC);
    REQUIRE(info4 != info3);
    info4.setStyle(info3.getStyle());
    info4.setFillColor(sf::Color(0, segment01::Constant::MaxColor, 0,
                                 segment01::Constant::MaxColor));
    REQUIRE(info4 != info3);
    info4.setFillColor(info3.getFillColor());
    info4.setOutlineColor(sf::Color(segment01::Constant::MaxColor, 0, 0,
                                    segment01::Constant::MaxColor));
    REQUIRE(info4 != info3);
    info4.setOutlineColor(info3.getOutlineColor());
    info4.setThickness(1);
    REQUIRE(info4 != info3);
}
