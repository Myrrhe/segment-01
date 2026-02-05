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

#include "RandManager.hpp"
#include "OsManager.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>

namespace segment01
{

std::array<std::mt19937, 1> RandManager::mt;

uint_fast32_t RandManager::mainSeed;

void RandManager::setMain(const std::size_t index, const bool giveNewSeed,
                          const uint_fast32_t newMainSeed)
{
    if (giveNewSeed)
    {
        mainSeed = newMainSeed;
    }
    else
    {
        mainSeed = static_cast<uint_fast32_t>(::time(nullptr));
    }

    mt[index].seed(mainSeed);
}

uint_fast32_t RandManager::getMainSeed() { return mainSeed; }

uint64_t RandManager::getRand(const std::size_t index) { return mt[index](); }

uint64_t RandManager::getMax()
{
    return decltype(mt)::value_type::max();
}

} // namespace segment01
