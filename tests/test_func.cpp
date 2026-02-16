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

#include "Constant.hpp"
#include "Func.hpp"
#include "Logger.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Func", "[func]")
{
    static constexpr LONG biWidth = 200;
    static constexpr LONG biHeight = 200;
    static constexpr LONG biBitCount = 32;
    static constexpr uint64_t str32HexToLuiTest1 = 65424;

    REQUIRE(segment01::Func::printVideoMode(sf::VideoMode({800, 600}, 32)) ==
            "(800 px, 600 px, 32 bpp)");

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = biWidth;
    bmi.bmiHeader.biHeight = biHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = biBitCount;
    bmi.bmiHeader.biCompression = BI_RGB;
    void *bits = nullptr;
    const HDC hdc = ::GetDC(nullptr);
    const HBITMAP hBitmap =
        ::CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    static_cast<void>(::ReleaseDC(nullptr, hdc));
    // BGRA
    auto *const pixels = static_cast<uint8_t *const>(bits);
    std::size_t colorIndex = 0;
    pixels[colorIndex++] = 0;                             // B
    pixels[colorIndex++] = 0;                             // G
    pixels[colorIndex++] = segment01::Constant::MaxColor; // R
    pixels[colorIndex] = segment01::Constant::MaxColor;   // A
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

    REQUIRE(!segment01::Func::isFloat(""));
    REQUIRE(!segment01::Func::isFloat("-"));
    REQUIRE(!segment01::Func::isFloat("é"));
    REQUIRE(!segment01::Func::isFloat("."));
    REQUIRE(!segment01::Func::isFloat(","));
    REQUIRE(segment01::Func::isFloat(".0"));
    REQUIRE(!segment01::Func::isFloat(",0"));
    REQUIRE(segment01::Func::isFloat("1.2"));
    REQUIRE(segment01::Func::isFloat("-1.2"));
    REQUIRE(!segment01::Func::isFloat("1,2"));
    REQUIRE(segment01::Func::isFloat("1"));

    REQUIRE(!segment01::Func::isFloat(U""));
    REQUIRE(!segment01::Func::isFloat(U"-"));
    REQUIRE(!segment01::Func::isFloat(U"é"));
    REQUIRE(!segment01::Func::isFloat(U"."));
    REQUIRE(!segment01::Func::isFloat(U","));
    REQUIRE(segment01::Func::isFloat(U".0"));
    REQUIRE(!segment01::Func::isFloat(U",0"));
    REQUIRE(segment01::Func::isFloat(U"1.2"));
    REQUIRE(segment01::Func::isFloat(U"-1.2"));
    REQUIRE(!segment01::Func::isFloat(U"1,2"));
    REQUIRE(segment01::Func::isFloat(U"1"));

    REQUIRE(segment01::Func::power(2, 0) == 1);
    REQUIRE(segment01::Func::power(2, 10) == 1024);

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

    REQUIRE(segment01::Func::str32ToLui(U"error") == 0);
    REQUIRE(segment01::Func::str32ToLui(U"10") == 10);

    REQUIRE(segment01::Func::str32HexToLui(U"fF9z") == str32HexToLuiTest1);
    REQUIRE(segment01::Func::str32HexToLui(U"fF9.") == str32HexToLuiTest1);
    REQUIRE(segment01::Func::str32HexToLui(U"fF9:") == str32HexToLuiTest1);

    REQUIRE_THAT(
        segment01::Func::str32ToF(U"error"),
        Catch::Matchers::WithinRel(0.0f, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        segment01::Func::str32ToF(U"1"),
        Catch::Matchers::WithinRel(1.0f, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        segment01::Func::str32ToF(U"1.2"),
        Catch::Matchers::WithinRel(1.2f, segment01::Constant::m_epsilon_f));
    REQUIRE_THAT(
        segment01::Func::str32ToF(U"-1.2"),
        Catch::Matchers::WithinRel(-1.2f, segment01::Constant::m_epsilon_f));

    REQUIRE(segment01::Func::luiTo32Str(11) == U"11");

    // std::u32string test = segment01::Func::fTo32Str(12.3f);
    // std::string str8 = "";
    // static_cast<void>(segment01::Func::utf32ToUtf8(test.begin(), test.end(),
    //                                                std::back_inserter(str8)));
    // segment01::Logger().info(str8);
    // segment01::Logger().info(std::to_string(12.3f));

    REQUIRE(segment01::Func::luiTo32StrHex(0xF9) == U"f9");

    REQUIRE(segment01::Func::fTo32Str(12.3) == U"12");

    REQUIRE(segment01::Func::getKeyValueLine("error").first == "");
    REQUIRE(segment01::Func::getKeyValueLine("error").second == "");
    REQUIRE(segment01::Func::getKeyValueLine("a=b").first == "a");
    REQUIRE(segment01::Func::getKeyValueLine("a=b").second == "b");

    REQUIRE(segment01::Func::getKeyValueLine(U"error").first == U"");
    REQUIRE(segment01::Func::getKeyValueLine(U"error").second == U"");
    REQUIRE(segment01::Func::getKeyValueLine(U"a=b").first == U"a");
    REQUIRE(segment01::Func::getKeyValueLine(U"a=b").second == U"b");

    REQUIRE(segment01::Func::split("a,b", ',').size() == 2);
    REQUIRE(segment01::Func::split("a,b", ",").size() == 2);
    REQUIRE(segment01::Func::split(U"a,b", U',').size() == 2);
    REQUIRE(segment01::Func::split(U"a,b", U",").size() == 2);

    std::string s1 = "abcéàù";
    std::u32string us1 = U"";
    static_cast<void>(segment01::Func::utf8ToUtf32(s1.begin(), s1.end(),
                                                   std::back_inserter(us1)));
    REQUIRE(us1 == U"abcéàù");

    std::u32string us2 = U"abcéàù";
    std::string s2 = "";
    static_cast<void>(segment01::Func::utf32ToUtf8(us2.begin(), us2.end(),
                                                   std::back_inserter(s2)));
    REQUIRE(s2 == "abcéàù");

    REQUIRE(segment01::Func::str8Tostr32("abcéàù") == U"abcéàù");

    REQUIRE(segment01::Func::str32Tostr8(U"abcéàù") == "abcéàù");
}
