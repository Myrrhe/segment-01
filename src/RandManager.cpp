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

#include "RandManager.hpp"
#include "OsManager.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>

namespace segment01
{

// std::array<std::mersenne_twister_engine<uint_fast32_t, 32UL, 624UL, 397UL,
// 31UL,
//                                         0x99'08'b0'dfU, 11UL, 0xff'ff'ff'ffU,
//                                         7UL, 0x9d'2c'56'80U, 15UL,
//                                         0xef'c6'00'00U, 18UL,
//                                         1'812'433'253U>,
//            1UL>
//     RandManager::mt;
std::array<Mt1993764, 1UL> RandManager::mt;

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
    // return decltype(mt)::value_type::max();
    return Mt1993764::max();
}

} // namespace segment01
