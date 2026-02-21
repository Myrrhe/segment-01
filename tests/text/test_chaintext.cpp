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
#include "text/ChainText.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Chaintext", "[chaintext]")
{
    const auto chain1 = segment01::ChainText();
    auto chain2 = chain1;
    chain2 = chain1;
    REQUIRE(chain2.getSize() == 0);
    const auto chain3 = segment01::ChainText(
        UR"(<cSize=30></>alpha<cSize=30>beta</>gamma\<\\)");
    const auto chain4 =
        segment01::ChainText(R"(<cSize=30></>alpha<cSize=30>beta</>gamma\<\\)");
    REQUIRE(!chain3.isEmpty());
    REQUIRE(chain3[0]->getType() == segment01::NodeText::Type::BLOCKINFO);
    REQUIRE(chain3.getNbChar() == 16);
    REQUIRE(chain3.getNbChar(0) == 0);
    REQUIRE(chain3.getNbChar(2) == 5);
    REQUIRE(chain3.getStr() == U"alphabetagamma<\\");
    REQUIRE(chain3.toStr() == U"<cSize=30></>alpha<cSize=30>beta</>gamma<\\");
    REQUIRE(chain1 != chain3);
    REQUIRE(chain4 == chain4);
    REQUIRE(chain4 == chain3);
    REQUIRE(chain4 != segment01::ChainText(
                          UR"(<cSize=30></>alpha<cSize=30>beta</>delta\<\\)"));

    segment01::Logger::setLevel(segment01::LogLevel::NONE);
    const auto chain5 = segment01::ChainText(U"");
    const auto chain6 = segment01::ChainText("");
    const auto chain7 = segment01::ChainText(UR"(</>)");
    const auto chain8 = segment01::ChainText(R"(</>)");
    const auto chain9 = segment01::ChainText(UR"(<cSize=30>)");
    const auto chain10 = segment01::ChainText(R"(<cSize=30>)");
    segment01::Logger::setLevel(segment01::LogLevel::INFO);
}
