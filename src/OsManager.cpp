/*
 * This file manage the differences between several OS.
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

#include "OsManager.hpp"
#include "Func.hpp"
#include "Logger.hpp"
#include <GL/glu.h>
#include <codecvt>
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>

#ifdef __linux__
#include <ctime>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

#elif _WIN32
#include <windows.h>
#include <direct.h>
#include <psapi.h>
#include <winnt.h>
#include <wtypes.h> // Need to be put before psapi.h

#elif _OSX

#endif // __linux__

#include <shcore.h>

namespace segment01
{
#ifdef __linux__
const char OsManager::SlashC = '/';
const std::string OsManager::StrIcon = "iconl64.png";
#elif _WIN32
const char OsManager::SlashC = '\\';
const std::string OsManager::StrIcon = "iconw128.png";
#elif _OSX

#endif // __linux__

const std::string OsManager::Slash = std::string(1, OsManager::SlashC);

sf::Vector2<uint64_t> OsManager::getMonitorSize()
{
#ifdef __linux__
    Display *disp = XOpenDisplay(nullptr);
    Screen *scrn = DefaultScreenOfDisplay(disp);
    return sf::Vector2<uint64_t int>(static_cast<uint64_t>(scrn->width),
                                     static_cast<uint64_t>(scrn->height));
#elif _WIN32
    RECT desktop;
    auto res = sf::Vector2<uint64_t>(0, 0);
    if (::GetWindowRect(::GetDesktopWindow(), &desktop) != FALSE)
    {
        res = sf::Vector2<uint64_t>(static_cast<uint64_t>(desktop.bottom),
                                    static_cast<uint64_t>(desktop.right));
    }
    return res;
#elif _OSX

#endif // __linux__
}

int64_t OsManager::getWallpaperStyle()
{
#ifdef __linux__
#elif _WIN32
    HKEY hKey = nullptr;
    if (::RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0,
                        KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        return -1;
    }

    std::string value(16, '\0');
    DWORD valueLength = sizeof(value);
    if (::RegQueryValueExA(hKey, "WallpaperStyle", nullptr, nullptr,
                           reinterpret_cast<LPBYTE>(value.data()),
                           &valueLength) != ERROR_SUCCESS)
    {
        ::RegCloseKey(hKey);
        return -1;
    }

    ::RegCloseKey(hKey);
    // Remove null terminator
    return std::stol(std::string(value.data(), valueLength - 1));
#elif _OSX
#endif // __linux__
}
} // namespace segment01
