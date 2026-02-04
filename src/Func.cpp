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

#include "Func.hpp"
#include <algorithm>
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
        bmi.bmiHeader.biBitCount = 32;
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
                for (size_t i = 0; i < nbPixels; i += 4)
                {
                    // B <-> R
                    std::swap(pixels[i], pixels[i + 2]);
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
        std::cout << "Error opening " << dir << "\n";
    }
    else
    {
        while ((dirp = ::readdir(dp)) != nullptr)
        {
            (void)res.emplace_back(static_cast<std::string>(dirp->d_name));
        }
        const int32_t err = ::closedir(dp);
        if (-1 == err)
        {
            std::cout << "Error closing " << dir << "\n";
        }
    }
    return res;
}

bool Func::fileExist(const std::string &path)
{
    const std::ifstream infile(path);
    return infile.good();
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

} // namespace segment01
