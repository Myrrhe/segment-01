#include "Logger.hpp"
#include "OsManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

int main(int /*argc*/, char ** /*argv*/, char ** /*options*/)
{
    segment01::Logger().info("aaa");
#ifdef _DEBUG
    std::cout << "Mode Debug, logs visibles dans la console\n";
#else
    // Rediriger vers un fichier ou ignorer
#endif
    segment01::OsManager::setProcessDPIAware();
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
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
