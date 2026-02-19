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

#include "FontManager.hpp"
#include "Func.hpp"
#include "Logger.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"

namespace segment01
{

const std::array<std::string, 2> FontManager::fontExtensions = {
    {".ttf", ".otf"}};
std::unordered_map<std::string, sf::Font> FontManager::fonts;

void FontManager::initialize()
{
    std::vector<std::string> allFont =
        Func::getDir(PathManager::getPath(PathManager::Dir::FONT));
    const std::size_t nbFile = allFont.size();
    for (std::size_t i = 0; i < nbFile; ++i)
    {
        auto font = sf::Font();
        if (Func::hasSuffixInList(allFont[i], fontExtensions.begin(),
                                  fontExtensions.end()))
        {
            if (font.openFromFile(PathManager::getPath(PathManager::Dir::FONT) +
                                  OsManager::Slash + allFont[i]))
            {
                fonts[allFont[i]] = font;
            }
            else
            {
                static_cast<void>(
                    Logger().info("Error loading font: " + allFont[i]));
            }
        }
    }
}

const sf::Font *FontManager::getFont(const std::string &str)
{
    sf::Font const *res = nullptr;
    if (const std::unordered_map<std::string, sf::Font>::iterator it =
            fonts.find(str);
        it != fonts.end())
    {
        res = &it->second;
    }
    return res;
}

} // namespace segment01
