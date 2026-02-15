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

#include "Func.hpp"
#include "Logger.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Func", "[func]")
{
    REQUIRE(segment01::Func::printVideoMode(sf::VideoMode({800, 600}, 32)) ==
            "(800 px, 600 px, 32 bpp)");

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 200;
    bmi.bmiHeader.biHeight = 200;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    void *bits = nullptr;
    const HDC hdc = ::GetDC(nullptr);
    const HBITMAP hBitmap =
        ::CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    static_cast<void>(::ReleaseDC(nullptr, hdc));
    // BGRA
    auto *const pixels = static_cast<uint8_t *const>(bits);
    pixels[0] = 0x00; // B
    pixels[1] = 0x00; // G
    pixels[2] = 0xFF; // R
    pixels[3] = 0xFF; // A
    const sf::Image image = segment01::Func::hBITMAPToImage(hBitmap);
    REQUIRE(image.getSize() == sf::Vector2<uint32_t>(200, 200));

    REQUIRE(segment01::Func::colorBalance(sf::Color(0, 0, 0, 255),
                                          sf::Color(255, 255, 255, 255), 0.5) ==
            sf::Color(127, 127, 127, 255));
    REQUIRE(segment01::Func::colorDistanceSquared(
                sf::Color(0, 0, 0, 255), sf::Color(255, 255, 255, 255)) ==
            195'075);

    segment01::Logger::setLevel(segment01::LogLevel::NONE);
    REQUIRE(segment01::Func::getDir("error").size() == 0);
    segment01::Logger::setLevel(segment01::LogLevel::INFO);
    REQUIRE(segment01::Func::getDir(".").size() > 0);
    REQUIRE(!segment01::Func::fileExist("error.txt"));

    REQUIRE(segment01::Func::getKeyWordLine("error") == "");
    REQUIRE(segment01::Func::getKeyWordLine("key=value") == "key");
    REQUIRE(segment01::Func::getKeyWordLine(U"error") == U"");
    REQUIRE(segment01::Func::getKeyWordLine(U"key=value") == U"key");

    const std::array<std::string, 3> fontExtensions = {
        {".ttf", ".otf", ".woff"}};
    REQUIRE(segment01::Func::hasSuffixInList("font.otf", fontExtensions.begin(),
                                             fontExtensions.end()));
    REQUIRE(!segment01::Func::hasSuffixInList(
        "font.woff2", fontExtensions.begin(), fontExtensions.end()));

    REQUIRE(!segment01::Func::isPosInt(""));
    REQUIRE(!segment01::Func::isPosInt("-"));
    REQUIRE(segment01::Func::isPosInt("1"));
    REQUIRE(!segment01::Func::isPosInt("1.2"));
    REQUIRE(!segment01::Func::isPosInt("1,2"));
    REQUIRE(!segment01::Func::isPosInt("-1"));

    REQUIRE(!segment01::Func::isPosInt(U""));
    REQUIRE(!segment01::Func::isPosInt(U"-"));
    REQUIRE(segment01::Func::isPosInt(U"1"));
    REQUIRE(!segment01::Func::isPosInt(U"1.2"));
    REQUIRE(!segment01::Func::isPosInt(U"1,2"));
    REQUIRE(!segment01::Func::isPosInt(U"-1"));
}
