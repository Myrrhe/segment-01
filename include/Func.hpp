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

    [[nodiscard]] [[gnu::pure]] static sf::Color
    colorBalance(const sf::Color &lhs, const sf::Color &rhs,
                 const float64_t coeff);

    [[nodiscard]] [[gnu::pure]] static float64_t
    colorDistanceSquared(const sf::Color &lhs, const sf::Color &rhs);

    static std::vector<std::string> getDir(const std::string &dir);

    static bool fileExist(const std::string &path);

    static std::string getKeyWordLine(const std::string_view &line);

    static std::u32string getKeyWordLine(const std::u32string_view &line);

    [[nodiscard]] [[gnu::pure]] static bool
    hasSuffixInList(const std::string_view &str, const std::string *const begin,
                    const std::string *const end);
};

} // namespace segment01

#endif // FUNC_HPP
