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

#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP
#include "StaticObject.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace segment01
{

////////////////////////////////////////////////////////////
/// \brief Manage the fonts.
///
////////////////////////////////////////////////////////////
class FontManager final : public StaticObject
{
public:
    static void initialize();
    static const sf::Font *getFont(const std::string &str);

    static const std::array<std::string, 2> fontExtensions;

private:
    static std::unordered_map<std::string, sf::Font> fonts;
};
} // namespace segment01

#endif // FONTMANAGER_HPP
