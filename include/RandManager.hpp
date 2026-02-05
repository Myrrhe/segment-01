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

#ifndef RANDMANAGER_HPP
#define RANDMANAGER_HPP
#include "StaticObject.hpp"
#include <array>
#include <cstdint>
#include <random>

namespace segment01
{

class RandManager final : public StaticObject
{
public:
    enum class IdRand : uint32_t
    {
        MAIN
    };

    static void setMain(const std::size_t index, const bool giveNewSeed,
                        const uint_fast32_t newMainSeed);
    [[nodiscard]] [[gnu::pure]] static uint_fast32_t getMainSeed();
    [[nodiscard]] static uint64_t getRand(const std::size_t index);
    [[nodiscard]] [[gnu::const]] static uint64_t getMax();

private:
    static std::array<std::mt19937, 1> mt;

    static uint_fast32_t mainSeed;
};
} // namespace segment01

#endif // RANDMANAGER_HPP
