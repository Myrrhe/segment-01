/*
 * This class check the state of the mouse wheel.
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

#include "Mt19937_64.hpp"

namespace segment01
{

Mt19937_64::Mt19937_64(const uint64_t s) : mt(), index(0) { seed(s); }

Mt19937_64::Mt19937_64(const Mt19937_64 &right) = default;
Mt19937_64 &Mt19937_64::operator=(const Mt19937_64 &right) = default;
Mt19937_64::Mt19937_64(Mt19937_64 &&right) noexcept = default;
Mt19937_64 &Mt19937_64::operator=(Mt19937_64 &&right) noexcept = default;
Mt19937_64::~Mt19937_64() = default;

void Mt19937_64::seed(const uint64_t s)
{
    mt[0] = s;
    for (size_t i = 1; i < n; ++i)
    {
        mt[i] = 6364136223846793005ULL * (mt[i - 1] ^ (mt[i - 1] >> 62)) + i;
    }
    index = n;
}

uint64_t Mt19937_64::operator()()
{
    if (index >= n)
    {
        twist();
    }
    index++;
    uint64_t x = mt[index];
    // Tempering
    x ^= (x >> 29) & 0x5555555555555555ULL;
    x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
    x ^= (x << 37) & 0xFFF7EEE000000000ULL;
    x ^= (x >> 43);
    return x;
}

void Mt19937_64::twist()
{
    for (std::size_t i = 0; i < n; i++)
    {
        uint64_t x = (mt[i] & upper_mask) + (mt[(i + 1) % n] & lower_mask);
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
