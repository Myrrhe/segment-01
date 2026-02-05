/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
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

#include "ScreenConnected.hpp"

namespace segment01
{

ScreenConnected::ScreenConnected()
    : name(L""), bounds(sf::Rect<float32_t>(sf::Vector2<float32_t>(0, 0),
                                            sf::Vector2<float32_t>(0, 0))),
      refreshRate(0), dpi(sf::Vector2<uint32_t>(0, 0))
{
}

ScreenConnected::ScreenConnected(const std::wstring &newName,
                                 const sf::Rect<float32_t> &newBounds,
                                 const uint32_t newRefreshRate,
                                 const sf::Vector2<uint32_t> &newDpi)
    : name(newName), bounds(newBounds), refreshRate(newRefreshRate), dpi(newDpi)
{
}

ScreenConnected::ScreenConnected(const ScreenConnected &right) = default;

ScreenConnected::~ScreenConnected() = default;

ScreenConnected &
ScreenConnected::operator=(const ScreenConnected &right) = default;

ScreenConnected::ScreenConnected(ScreenConnected &&right) noexcept = default;
ScreenConnected &
ScreenConnected::operator=(ScreenConnected &&right) noexcept = default;

void ScreenConnected::initialize()
{
    // Nothing to do
}

void ScreenConnected::deleteAll()
{
    // Nothing to do
}

} // namespace segment01
