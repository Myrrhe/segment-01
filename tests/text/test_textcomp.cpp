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

#include "FontManager.hpp"
#include "Logger.hpp"
#include "PathManager.hpp"
#include "text/TextComp.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Textcomp", "[textcomp]")
{
    const auto text1 = segment01::TextComp();
    auto text2 = text1;
    text2 = text1;
    text2.setCharacterSize(segment01::InfoText::DefaultSize);
    text2.setCharacterSize(segment01::InfoText::DefaultSize - 1);
    text2.setLetterSpacing(false, 0);
    text2.setLetterSpacing(false, 0);
    text2.setLineSpacing(0);
    text2.setLineSpacing(0);
    text2.setStyle(segment01::InfoText::Style::BOLD);
    text2.setStyle(segment01::InfoText::Style::BOLD);
    text2.setFillColor(sf::Color(0, 0, 0, segment01::Constant::MaxColor));
    text2.setFillColor(sf::Color(0, 0, 0, segment01::Constant::MaxColor));
    text2.setOutlineColor(sf::Color(0, 0, 0, 0));
    text2.setOutlineColor(sf::Color(0, 0, 0, 0));
    text2.setOutlineThickness(1);
    text2.setOutlineThickness(1);
    text2.setWidthWrap(1);
    text2.setWidthWrap(1);
    REQUIRE(text2.getChainText().empty());
    REQUIRE(text2.getFont() == nullptr);
    REQUIRE(text2.getCharacterSize() == segment01::InfoText::DefaultSize - 1);
    REQUIRE(!std::get<0>(text2.getLetterSpacing()));
    REQUIRE_THAT(
        std::get<1>(text2.getLetterSpacing()),
        Catch::Matchers::WithinRel(0, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        text2.getLineSpacing(),
        Catch::Matchers::WithinRel(0, segment01::Constant::m_epsilon_f));
    REQUIRE(text2.getStyle() == segment01::InfoText::Style::BOLD);
    REQUIRE(text2.getFillColor() ==
            sf::Color(0, 0, 0, segment01::Constant::MaxColor));
    REQUIRE(text2.getOutlineColor() == sf::Color(0, 0, 0, 0));
    REQUIRE_THAT(
        text2.getOutlineThickness(),
        Catch::Matchers::WithinRel(1, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        text2.getWidthWrap(),
        Catch::Matchers::WithinRel(1, segment01::Constant::m_epsilon_f));

    segment01::PathManager::setPath(segment01::Func::str16Tostr8(
        segment01::OsManager::getExecutablePath()));
    segment01::FontManager::initialize();

    const auto chain1 = segment01::ChainText(
        UR"(<cSize=30></>alpha<cSize=30>beta</>gamma\<\\)");
    const auto text3 = segment01::TextComp(
        std::vector<const segment01::ChainText *>{&chain1},
        *segment01::FontManager::getFont("LinBiolinum_RI.ttf"),
        segment01::InfoText::DefaultSize);
    static_cast<void>(text3.getLocalBounds());
    static_cast<void>(text3.findCharacterPos(1));
}
