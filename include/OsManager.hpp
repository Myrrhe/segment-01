/*
 * This file manage the differences between several OS.
 * Copyright (C) 2020  Myrrhe <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef OSMANAGER_HPP
#define OSMANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "StaticObject.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

#ifdef __linux__
#define GNU_CONST [[gnu::const]]
#define GNU_PURE [[gnu::pure]]
#elif _WIN32
#define GNU_CONST
#define GNU_PURE
#elif _OSX

#endif // __linux__

namespace segment01
{
////////////////////////////////////////////////////////////
/// \brief Static class for the OS
///
////////////////////////////////////////////////////////////
class OsManager final : public StaticObject
{
public:
    static sf::Vector2<uint64_t> getMonitorSize();
    [[nodiscard]] static int64_t getWallpaperStyle();

    static const char SlashC;
    static const std::string Slash;
    static const std::string StrIcon;
};

} // namespace segment01

#endif // OSMANAGER_HPP
