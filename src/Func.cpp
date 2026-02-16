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

#include "Func.hpp"
#include "Logger.hpp"
#include <algorithm>
#include <charconv>
#include <chrono>
#include <cmath>
#include <dirent.h>
#include <fstream>
#include <locale>
#include <sstream>

namespace segment01
{
std::string Func::printVideoMode(const sf::VideoMode &videoMode)
{
    std::string res = "(" + std::to_string(videoMode.size.x) + " px, " +
                      std::to_string(videoMode.size.y) + " px, " +
                      std::to_string(videoMode.bitsPerPixel) + " bpp)";
    return res;
}

sf::Image Func::hBITMAPToImage(const HBITMAP hBitmap)
{
    static constexpr WORD biBitCount = 32;
    static constexpr std::size_t stepPixel = 4;
    static constexpr std::size_t offsetPixel = 2;
    BITMAP bmp;
    sf::Image res;
    if (0 != ::GetObject(hBitmap, sizeof(BITMAP), &bmp))
    {
        // Handle error: failed to get bitmap object
        const int32_t width = bmp.bmWidth;
        const int32_t height = bmp.bmHeight;

        // Préparer la structure pour GetDIBits
        BITMAPINFO bmi = {};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = width;
        // Négatif pour éviter l'image inversée verticalement
        bmi.bmiHeader.biHeight = -height;
        bmi.bmiHeader.biPlanes = 1;
        // Force RGBA (BGRA en réalité)
        bmi.bmiHeader.biBitCount = biBitCount;
        bmi.bmiHeader.biCompression = BI_RGB;

        // Allouer un buffer
        const auto nbPixels = static_cast<std::size_t>(width * height * 4);
        std::vector<uint8_t> pixels(nbPixels);

        const HDC hdc = ::GetDC(nullptr);

        if (const int32_t scanLines =
                ::GetDIBits(hdc, hBitmap, 0, static_cast<uint32_t>(height),
                            pixels.data(), &bmi, DIB_RGB_COLORS);
            0 != scanLines)
        {
            if (const int32_t releaseResult = ::ReleaseDC(nullptr, hdc);
                1 == releaseResult)
            {
                // SFML attend du RGBA, mais Windows fournit du
                // BGRA → convertir
                for (std::size_t i = 0; i < nbPixels; i += stepPixel)
                {
                    // B <-> R
                    std::swap(pixels[i], pixels[i + offsetPixel]);
                    // G reste inchangé
                    // A reste inchangé (souvent 0xFF si non transparent)
                }

                res.resize(sf::Vector2<uint32_t>(static_cast<uint32_t>(width),
                                                 static_cast<uint32_t>(height)),
                           pixels.data());
            }
            else
            {
                // Handle error: failed to release DC
            }
        }
        else
        {
            // Handle error: failed to get bitmap bits
        }
    }
    else
    {
        // Handle error: failed to get bitmap object
    }

    return res;
}

sf::Color Func::colorBalance(const sf::Color &lhs, const sf::Color &rhs,
                             const float64_t coeff)
{
    const float64_t oneMinusCoeff = 1.0 - coeff;
    return sf::Color(
        static_cast<uint8_t>(lhs.r * coeff + rhs.r * oneMinusCoeff),
        static_cast<uint8_t>(lhs.g * coeff + rhs.g * oneMinusCoeff),
        static_cast<uint8_t>(lhs.b * coeff + rhs.b * oneMinusCoeff),
        static_cast<uint8_t>(lhs.a * coeff + rhs.a * oneMinusCoeff));
}

float64_t Func::colorDistanceSquared(const sf::Color &lhs, const sf::Color &rhs)
{
    return (lhs.r - rhs.r) * (lhs.r - rhs.r) +
           (lhs.g - rhs.g) * (lhs.g - rhs.g) +
           (lhs.b - rhs.b) * (lhs.b - rhs.b);
}

std::vector<std::string> Func::getDir(const std::string &dir)
{
    std::vector<std::string> res = {};
    DIR *dp = nullptr;
    dirent const *dirp = nullptr;
    if (nullptr == (dp = ::opendir(dir.c_str())))
    {
        static_cast<void>(Logger().info("Error opening " + dir));
    }
    else
    {
        while ((dirp = ::readdir(dp)) != nullptr)
        {
            static_cast<void>(
                res.emplace_back(static_cast<std::string>(dirp->d_name)));
        }
        const int32_t err = ::closedir(dp);
        if (-1 == err)
        {
            static_cast<void>(Logger().info("Error closing " + dir));
        }
    }
    return res;
}

bool Func::fileExist(const std::string &path)
{
    const std::ifstream infile(path);
    return infile.good();
}

bool Func::isFloat(const std::string &s)
{
    std::basic_istringstream<char, std::char_traits<char>, std::allocator<char>>
        iss(s);
    float32_t f = 0;
    iss >> std::noskipws >> f;
    // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is
    // set
    return iss.eof() && (!iss.fail());
}

bool Func::isFloat(const std::u32string &s)
{
    static constexpr char32_t maxAscii = 0x7F;
    bool res = true;
    float32_t value = 0.0f;

    std::string tmp;
    tmp.reserve(s.size());
    for (const char32_t c : s)
    {
        res = res && c <= maxAscii;
        tmp.push_back(static_cast<char>(c));
    }

    if (res)
    {
        const char *const begin = tmp.data();
        const char *const end = tmp.data() + tmp.size();
        const auto [ptr, ec] = std::from_chars(begin, end, value);
        res = ec == std::errc() && ptr == end;
    }

    return res;
}

uint64_t Func::power(const uint64_t base, const uint64_t exponent)
{
    uint64_t res = 1;
    if (0 != exponent)
    {
        res = base;
        for (uint64_t i = 1; i < exponent; ++i)
        {
            res *= base;
        }
    }
    return res;
}

bool Func::isPosInt(const std::string_view &s)
{
    bool res = false;
    if (!s.empty())
    {
        res = true;
        const std::locale loc;
        const auto *const sEnd = s.end();
        for (auto *it = s.begin(); it != sEnd; ++it)
        {
            res = res && std::isdigit(*it, loc);
        }
    }
    return res;
}

bool Func::isPosInt(const std::u32string_view &s)
{
    bool res = false;
    if (!s.empty())
    {
        res = true;
        const std::locale loc;
        const auto *const sEnd = s.end();
        for (auto *it = s.begin(); it != sEnd; ++it)
        {
            const char32_t c = *it;
            res = res && (c >= U'0' && c <= U'9');
        }
    }
    return res;
}

uint64_t Func::str32ToLui(const std::u32string &s)
{
    static constexpr uint64_t baseTen = 10;
    uint64_t res = 0;
    if (isPosInt(s))
    {
        const std::size_t sizeS = s.size();
        for (std::size_t i = 0; i < sizeS; ++i)
        {
            res += (s[i] - U'0') * power(baseTen, s.size() - 1 - i);
        }
    }
    return res;
}

uint64_t Func::str32HexToLui(const std::u32string &s)
{
    static constexpr uint64_t baseTen = 10;
    static constexpr uint64_t baseSixteen = 16;
    uint64_t res = 0;
    const std::size_t sizeS = s.size();
    for (std::size_t i = 0; i < sizeS; ++i)
    {
        uint64_t val = 0;
        if ((s[i] >= U'0') && (s[i] <= U'9'))
        {
            val = s[i] - U'0';
        }
        else if ((s[i] >= U'a') && (s[i] <= U'f'))
        {
            val = (baseTen + s[i]) - U'a';
        }
        else if ((s[i] >= U'A') && (s[i] <= U'F'))
        {
            val = (baseTen + s[i]) - U'A';
        }
        else
        {
            // Error, do nothing
        }
        res += val * power(baseSixteen, s.size() - 1 - i);
    }
    return res;
}

float32_t Func::str32ToF(const std::u32string &s)
{
    float32_t res = 0.0f;
    if (isFloat(s))
    {
        float32_t fracFactor = 0.1f;
        std::size_t i = 0;
        bool negative = false;
        bool afterPoint = false;
        if (s[i] == U'-')
        {
            negative = true;
            ++i;
        }
        const std::size_t sizeS = s.size();
        for (; i < sizeS; ++i)
        {
            if (s[i] == U'.')
            {
                afterPoint = true;
            }
            else
            {
                res += static_cast<float32_t>(s[i] - U'0') * fracFactor;
                if (!afterPoint)
                {
                    res *= 10.0f;
                }
                else
                {
                    fracFactor *= 0.1f;
                }
            }
        }
        if (negative)
        {
            res *= -1.0f;
        }
    }
    return res;
}

std::u32string Func::luiTo32Str(uint64_t n)
{
    static constexpr uint64_t baseTen = 10;
    std::u32string res = U"";
    do
    {
        res = std::u32string(1, (static_cast<char32_t>(n % baseTen) + U'0')) +
              res;
    } while ((n /= baseTen) > 0);
    return res;
}

std::u32string Func::luiTo32StrHex(uint64_t n)
{
    static constexpr uint64_t baseTen = 10;
    static constexpr uint64_t baseSixteen = 16;
    std::u32string res;
    do
    {
        if (const uint64_t digit = n % baseSixteen; digit <= baseTen - 1)
        {
            res = std::u32string(1, static_cast<char32_t>(digit) + U'0') + res;
        }
        else
        {
            res = std::u32string(1, static_cast<char32_t>(digit - baseTen) +
                                        U'a') +
                  res;
        }
        n /= baseSixteen;
    } while (n > 0);
    return res;
}

std::u32string Func::fTo32Str(float32_t n)
{
    std::u32string res = U"";
    do
    {
        res = std::u32string(
                  1, (static_cast<char32_t>(std::fmod(n, 10.0f)) + U'0')) +
              res;
    } while ((n /= 10.0f) > 1.0f);
    return res;
}

std::string Func::getKeyWordLine(const std::string_view &line)
{
    const std::size_t posEq = line.find("=", 0);
    std::string res = "";
    if (std::string::npos != posEq)
    {
        res = line.substr(0, posEq);
    }
    return res;
}

std::u32string Func::getKeyWordLine(const std::u32string_view &line)
{
    const std::size_t posEq = line.find(U"=", 0);
    std::u32string res = U"";
    if (std::u32string::npos != posEq)
    {
        res = line.substr(0, posEq);
    }
    return res;
}

std::pair<std::string, std::string>
Func::getKeyValueLine(const std::string_view &line)
{
    const std::size_t posEq = line.find("=", 0);
    std::pair<std::string, std::string> res = {"", ""};
    if (std::string::npos != posEq)
    {
        res.first = line.substr(0, posEq);
        res.second = line.substr(posEq + 1, std::string::npos);
    }
    return res;
}

std::pair<std::u32string, std::u32string>
Func::getKeyValueLine(const std::u32string_view &line)
{
    const std::size_t posEq = line.find(U"=", 0);
    std::pair<std::u32string, std::u32string> res = {U"", U""};
    if (std::u32string::npos != posEq)
    {
        res.first = line.substr(0, posEq);
        res.second = line.substr(posEq + 1, std::u32string::npos);
    }
    return res;
}

bool Func::hasSuffixInList(const std::string_view &str,
                           const std::string *const begin,
                           const std::string *const end)
{
    const std::size_t strSize = str.size();
    bool res = false;
    for (const std::string *ptr = begin; ptr != end; ++ptr)
    {
        res = res || (ptr->size() <= strSize &&
                      std::equal(ptr->rbegin(), ptr->rend(), str.rbegin()));
    }
    return res;
}

std::vector<std::string> Func::split(const std::string &s, const char delim)
{
    std::vector<std::string> res;
    std::back_insert_iterator<std::vector<std::string>> result =
        std::back_inserter(res);
    std::stringstream ss(s, std::ios_base::in | std::ios_base::out);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
    return res;
}

std::vector<std::string> Func::split(const std::string_view &s,
                                     const std::string_view &delim)
{
    std::vector<std::string> res = {};
    std::size_t posStart = 0;
    std::size_t posEnd = 0;
    const std::size_t delimLen = delim.length();
    while ((posEnd = s.find(delim, posStart)) != std::string::npos)
    {
        static_cast<void>(
            res.emplace_back(s.substr(posStart, posEnd - posStart)));
        posStart = posEnd + delimLen;
    }
    static_cast<void>(res.emplace_back(s.substr(posStart, std::string::npos)));
    return res;
}

std::vector<std::u32string> Func::split(const std::u32string &s,
                                        const char32_t delim)
{
    std::vector<std::u32string> res;
    std::back_insert_iterator<std::vector<std::u32string>> result =
        std::back_inserter(res);
    std::basic_stringstream<char32_t, std::char_traits<char32_t>> ss(
        s, std::ios_base::in | std::ios_base::out);
    std::u32string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
    return res;
}

std::vector<std::u32string> Func::split(const std::u32string_view &s,
                                        const std::u32string_view &delim)
{
    std::vector<std::u32string> res = {};
    std::size_t posStart = 0;
    std::size_t posEnd = 0;
    const std::size_t delimLen = delim.length();
    while ((posEnd = s.find(delim, posStart)) != std::u32string::npos)
    {
        static_cast<void>(
            res.emplace_back(s.substr(posStart, posEnd - posStart)));
        posStart = posEnd + delimLen;
    }
    static_cast<void>(
        res.emplace_back(s.substr(posStart, std::u32string::npos)));
    return res;
}

std::back_insert_iterator<std::u32string>
Func::utf8ToUtf32(std::string::const_iterator be,
                  const std::string::const_iterator en,
                  std::back_insert_iterator<std::u32string> output)
{
    // Some useful precomputed data
    static constexpr uint8_t maxTrailingBytes = 5;
    static constexpr uint8_t sizeShift = 6;
    static constexpr std::array<uint8_t, 256> trailing = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
         3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5}};
    static constexpr std::array<char32_t, 6> offsets = {
        {0x00'00'00'00, 0x00'00'30'80, 0x00'0E'20'80, 0x03'C8'20'80,
         0xFA'08'20'80U, 0x82'08'20'80U}};
    while (be < en)
    {
        char32_t codepoint = 0;
        // decode the character
        if (const uint8_t trailingBytes =
                trailing[static_cast<uint64_t>(static_cast<uint8_t>(*be))];
            (be + trailingBytes) < en)
        {
            if (trailingBytes <= maxTrailingBytes)
            {
                for (uint8_t i = 0; i <= trailingBytes; ++i)
                {
                    if (i == trailingBytes)
                    {
                        codepoint += static_cast<uint8_t>(*be++);
                    }
                    else
                    {
                        (codepoint += static_cast<uint8_t>(*be++)) <<=
                            sizeShift;
                    }
                }
            }
            codepoint -= offsets[trailingBytes];
        }
        else
        {
            // Incomplete character
            be = en;
        }
        *output++ = codepoint;
    }
    return output;
}

std::back_insert_iterator<std::string>
Func::utf32ToUtf8(std::u32string::const_iterator be,
                  const std::u32string::const_iterator en,
                  std::back_insert_iterator<std::string> output)
{
    // Some useful precomputed data
    static const std::array<uint8_t, 7> firstBytes = {
        {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC}};
    while (be < en)
    {
        // Valid character
        // Get the number of bytes to write
        char32_t input = *be++;
        std::size_t bytestoWrite = 1;
        if (input < 0x80)
        {
            bytestoWrite = 1;
        }
        else if (input < 0x800)
        {
            bytestoWrite = 2;
        }
        else if (input < 0x1'00'00)
        {
            bytestoWrite = 3;
        }
        else if (input <= 0x00'10'FF'FF)
        {
            bytestoWrite = 4;
        }
        else
        {
            // Nothing to do
        }

        // Extract the bytes to write
        std::array<uint8_t, 4> bytes;
        if (bytestoWrite <= 4)
        {
            for (std::size_t i = 1; i <= bytestoWrite; ++i)
            {
                if (i == bytestoWrite)
                {
                    bytes[bytestoWrite - i] =
                        static_cast<uint8_t>(input | firstBytes[bytestoWrite]);
                }
                else
                {
                    bytes[bytestoWrite - i] =
                        static_cast<uint8_t>((input | 0x80) & 0xBF);
                    input >>= 6;
                }
            }
        }
        // Add them to the output
        output = std::copy(bytes.data(), bytes.data() + bytestoWrite, output);
    }
    return output;
}

std::u32string Func::str8Tostr32(const std::string_view &s)
{
    std::u32string res = U"";
    std::string str = {s.begin(), s.end()};
    static_cast<void>(
        utf8ToUtf32(str.begin(), str.end(), std::back_inserter(res)));
    return res;
}

std::string Func::str32Tostr8(const std::u32string_view &s)
{
    std::string res = "";
    std::u32string str = {s.begin(), s.end()};
    static_cast<void>(
        utf32ToUtf8(str.begin(), str.end(), std::back_inserter(res)));
    return res;
}

} // namespace segment01
