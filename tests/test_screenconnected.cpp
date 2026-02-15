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

#include "ScreenConnected.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Screenconnected", "[screenconnected]")
{
    segment01::ScreenConnected::initialize();
    auto screen1 = segment01::ScreenConnected();
    auto screen2 = segment01::ScreenConnected(
        L"test",
        sf::Rect<segment01::float32_t>(
            sf::Vector2<segment01::float32_t>(1, 2),
            sf::Vector2<segment01::float32_t>(10, 10)),
        60, sf::Vector2<uint32_t>(96, 96));
    REQUIRE(screen1.name.empty());
    REQUIRE(screen2.name == L"test");
    screen1 = screen2;
    REQUIRE(screen1.name == L"test");
    screen2 = std::move(screen1);
    REQUIRE(screen2.name == L"test");
    auto screen3 = segment01::ScreenConnected(screen2);
    auto screen4 = std::move(screen2);
    REQUIRE(screen3.name == L"test");
    REQUIRE(screen4.name == L"test");
    segment01::ScreenConnected::deleteAll();
}
