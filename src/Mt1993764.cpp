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

#include "Mt1993764.hpp"
namespace segment01
{
Mt1993764::Mt1993764() : mt(), index(0) { seed(Mt1993764::DefaultSeed); }
Mt1993764::Mt1993764(const uint64_t s) : mt(), index(0) { seed(s); }

Mt1993764::Mt1993764(const Mt1993764 &right) = default;
Mt1993764::Mt1993764(Mt1993764 &&right) noexcept = default;
Mt1993764 &Mt1993764::operator=(const Mt1993764 &right) = default;
Mt1993764 &Mt1993764::operator=(Mt1993764 &&right) noexcept = default;
Mt1993764::~Mt1993764() = default;

void Mt1993764::seed(const uint64_t s)
{
    mt[0] = s;
    for (size_t i = 1; i < n; ++i)
    {
        mt[i] = 6364136223846793005ULL * (mt[i - 1] ^ (mt[i - 1] >> 62)) + i;
    }
    index = n;
}

uint64_t Mt1993764::operator()()
{
    if (index >= n)
    {
        twist();
    }
    ++index;
    uint64_t x = mt[index];
    // Tempering
    x ^= (x >> 29) & 6'148'914'691'236'517'205ULL;
    x ^= (x << 17) & 8'202'884'508'482'404'352ULL;
    x ^= (x << 37) & 18'444'473'444'759'240'704ULL;
    x ^= (x >> 43);
    return x;
}

void Mt1993764::twist()
{
    for (std::size_t i = 0; i < n; ++i)
    {
        const uint64_t x =
            (mt[i] & upper_mask) + (mt[(i + 1) % n] & lower_mask);
        uint64_t xA = x >> 1;
        if (x % 2 != 0)
        {
            xA ^= matrix_a;
        }
        mt[i] = mt[(i + m) % n] ^ xA;
    }
    index = 0;
}

} // namespace segment01
