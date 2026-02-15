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

#ifndef FUNC_HPP
#define FUNC_HPP
#include "OsManager.hpp"
#include "StaticObject.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <windows.h>

namespace segment01
{
class Func final : public StaticObject
{
public:
    static std::string printVideoMode(const sf::VideoMode &videoMode);

    static sf::Image hBITMAPToImage(const HBITMAP hBitmap);

    [[nodiscard]] ATTR_PURE static sf::Color
    colorBalance(const sf::Color &lhs, const sf::Color &rhs,
                 const float64_t coeff);

    [[nodiscard]] ATTR_PURE static float64_t
    colorDistanceSquared(const sf::Color &lhs, const sf::Color &rhs);

    static std::vector<std::string> getDir(const std::string &dir);

    static bool fileExist(const std::string &path);

    static bool isFloat(const std::string &s);

    static bool isFloat(const std::u32string &s);

    [[nodiscard]] static uint64_t power(const uint64_t base,
                                        const uint64_t exponent);

    static bool isPosInt(const std::string_view &s);

    static bool isPosInt(const std::u32string_view &s);

    static uint64_t str32ToLui(const std::u32string &s);

    static uint64_t str32HexToLui(const std::u32string &s);

    static float32_t str32ToF(const std::u32string &s);

    static std::u32string luiTo32Str(uint64_t n);

    static std::u32string luiTo32StrHex(uint64_t n);

    static std::u32string fTo32Str(float32_t n);

    static std::string getKeyWordLine(const std::string_view &line);

    static std::u32string getKeyWordLine(const std::u32string_view &line);

    static std::pair<std::string, std::string>
    getKeyValueLine(const std::string_view &line);

    static std::pair<std::u32string, std::u32string>
    getKeyValueLine(const std::u32string_view &line);

    [[nodiscard]] ATTR_PURE static bool
    hasSuffixInList(const std::string_view &str, const std::string *const begin,
                    const std::string *const end);

    static std::vector<std::string> split(const std::string &s,
                                          const char delim);

    static std::vector<std::string> split(const std::string_view &s,
                                          const std::string_view &delim);

    static std::vector<std::u32string> split(const std::u32string &s,
                                             const char32_t delim);

    static std::vector<std::u32string> split(const std::u32string_view &s,
                                             const std::u32string_view &delim);

    static std::back_insert_iterator<std::u32string>
    utf8ToUtf32(std::string::const_iterator be,
                const std::string::const_iterator en,
                std::back_insert_iterator<std::u32string> output);

    static std::back_insert_iterator<std::string>
    utf32ToUtf8(std::u32string::const_iterator be,
                const std::u32string::const_iterator en,
                std::back_insert_iterator<std::string> output);
};

} // namespace segment01

#endif // FUNC_HPP
