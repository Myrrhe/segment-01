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

#include "Logger.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

int main(int /*argc*/, char **argv, char ** /*options*/)
{
    static_cast<void>(segment01::Logger().info("aaa"));
    static_cast<void>(
        segment01::Logger().info(segment01::OsManager::getExecutablePath()));
    static_cast<void>(segment01::Logger().info(argv[0]));
    static_cast<void>(segment01::Logger().info(sizeof(wchar_t)));
#ifdef _DEBUG
    std::cout << "Mode Debug, logs visibles dans la console\n";
#else
    // Rediriger vers un fichier ou ignorer
#endif
    segment01::OsManager::setProcessDPIAware();
    segment01::PathManager::setPath(argv[0]);
    sf::RenderWindow window(sf::VideoMode(sf::Vector2<uint32_t>(200, 200)),
                            "SFML works!");
    sf::CircleShape shape(100.f);
    
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    // segment01::Engine::launch();
    return 0;
}
