/*
 * A basic function library.
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

#ifndef FUNC_HPP
#define FUNC_HPP
#include "StaticObject.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <windows.h>

namespace segment01
{
class Func final : public StaticObject
{
public:
    static constexpr float64_t m_e = 2.71828182845904523536;
    static constexpr float64_t m_log2e = 1.44269504088896340736;
    static constexpr float64_t m_log10e = 0.434294481903251827651;
    static constexpr float64_t m_ln2 = 0.693147180559945309417;
    static constexpr float64_t m_ln10 = 2.30258509299404568402;
    static constexpr float64_t m_pi = 3.14159265358979323846;
    static constexpr float64_t m_2pi = 6.28318530717958647692;
    static constexpr float64_t m_pi_2 = 1.57079632679489661923;
    static constexpr float64_t m_pi_4 = 0.785398163397448309616;
    static constexpr float64_t m_1_pi = 0.318309886183790671538;
    static constexpr float64_t m_2_pi = 0.636619772367581343076;
    static constexpr float64_t m_2_sqrtpi = 1.12837916709551257390;
    static constexpr float64_t m_sqrt2 = 1.41421356237309504880;
    static constexpr float64_t m_1_sqrt2 = 0.707106781186547524401;
    static constexpr float64_t m_epsilon = 0.00000000000000000001;

    static constexpr float64_t m_1_60s = 1.0 / 60.0;

    static constexpr float32_t m_e_f = 2.71828182845904523536f;
    static constexpr float32_t m_log2e_f = 1.44269504088896340736f;
    static constexpr float32_t m_log10e_f = 0.434294481903251827651f;
    static constexpr float32_t m_ln2_f = 0.693147180559945309417f;
    static constexpr float32_t m_ln10_f = 2.30258509299404568402f;
    static constexpr float32_t m_pi_f = 3.14159265358979323846f;
    static constexpr float32_t m_2pi_f = 6.28318530717958647692f;
    static constexpr float32_t m_pi_2_f = 1.57079632679489661923f;
    static constexpr float32_t m_pi_4_f = 0.785398163397448309616f;
    static constexpr float32_t m_1_pi_f = 0.318309886183790671538f;
    static constexpr float32_t m_2_pi_f = 0.636619772367581343076f;
    static constexpr float32_t m_2_sqrtpi_f = 1.12837916709551257390f;
    static constexpr float32_t m_sqrt2_f = 1.41421356237309504880f;
    static constexpr float32_t m_1_sqrt2_f = 0.707106781186547524401f;
    static constexpr float32_t m_epsilon_f = 0.00000000000000000001f;

    static constexpr float32_t m_1_60sf = 1.0f / 60.0f;

    static std::string printVideoMode(const sf::VideoMode &videoMode);

    static sf::Image hBITMAPToImage(const HBITMAP hBitmap);

    [[nodiscard]] [[gnu::pure]] static sf::Color
    colorBalance(const sf::Color &lhs, const sf::Color &rhs,
                 const float64_t coeff);

    [[nodiscard]] [[gnu::pure]] static float64_t
    colorDistanceSquared(const sf::Color &lhs, const sf::Color &rhs);

    static std::vector<std::string> getDir(const std::string &dir);

    static bool fileExist(const std::string &path);

    static std::string getKeyWordLine(const std::string_view &line);

    static std::u32string getKeyWordLine(const std::u32string_view &line);

    [[gnu::pure]] static bool hasSuffixInList(const std::string_view &str,
                                              const std::string *const begin,
                                              const std::string *const end);
};

} // namespace segment01

#endif // FUNC_HPP
