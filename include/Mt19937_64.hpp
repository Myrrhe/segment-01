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

#ifndef MT1993764_HPP
#define MT1993764_HPP
#include <cstdint>
#include <array>
#include <iostream>

namespace segment01 {

class Mt19937_64 {
public:
    static constexpr std::size_t n = 312;
    static constexpr std::size_t m = 156;
    static constexpr uint64_t matrix_a = 0xB5026F5AA96619E9ULL;
    static constexpr uint64_t upper_mask = 0xFFFFFFFF80000000ULL;
    static constexpr uint64_t lower_mask = 0x7FFFFFFFULL;

    Mt19937_64();
    explicit Mt19937_64(const uint64_t seed = 5489ULL);
    Mt19937_64(const Mt19937_64 &right);
    Mt19937_64 &operator=(const Mt19937_64 &right);
    Mt19937_64(Mt19937_64 &&right) noexcept;
    Mt19937_64& operator=(Mt19937_64 &&right) noexcept;
    ~Mt19937_64();

    uint64_t operator()();

private:
    std::array<uint64_t, n> mt;
    std::size_t index;

    void twist() {
        for (std::size_t i = 0; i < n; i++) {
            uint64_t x = (mt[i] & upper_mask) + (mt[(i+1) % n] & lower_mask);
            uint64_t xA = x >> 1;
            if (x % 2 != 0) {
                xA ^= matrix_a;
            }
            mt[i] = mt[(i + m) % n] ^ xA;
        }
        index = 0;
    }
};

} // namespace segment01

#endif // MT1993764_HPP