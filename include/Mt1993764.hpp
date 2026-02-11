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

#ifndef MT1993764_HPP
#define MT1993764_HPP
#include <array>
#include <cstdint>
#include <iostream>

namespace segment01
{

class Mt1993764
{
public:
    static constexpr std::size_t n = 312;
    static constexpr std::size_t m = 156;
    static constexpr uint64_t matrix_a = 13'043'109'905'998'158'313ULL;
    static constexpr uint64_t upper_mask = 18'446'744'071'562'067'968ULL;
    static constexpr uint64_t lower_mask = 2'147'483'647ULL;

    explicit Mt1993764();
    explicit Mt1993764(const uint64_t s);
    Mt1993764(const Mt1993764 &right);
    Mt1993764(Mt1993764 &&right) noexcept;
    Mt1993764 &operator=(const Mt1993764 &right);
    Mt1993764 &operator=(Mt1993764 &&right) noexcept;
    ~Mt1993764();

    void seed(const uint64_t s);

    uint64_t operator()();

    [[nodiscard]] static constexpr uint64_t max() { return UINT64_MAX; }

    static constexpr uint64_t DefaultSeed = 5489ULL;

private:
    std::array<uint64_t, n> mt;
    std::size_t index;

    void twist();
};

} // namespace segment01

#endif // MT1993764_HPP
