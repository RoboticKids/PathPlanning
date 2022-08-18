#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Discrete World");
    // window.setFramerateLimit(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Check mouse click
            if (event.type == sf::Event::MouseButtonReleased)
            {
                // Left click for setting start/goal/obstacle
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    //TODO: add sequence for start/goal/obstacle
                    std::cout << "left click\n";
                }
                // Remove obstacle with right click
                else if (event.mouseButton.button == sf::Mouse::Button::Right)
                {
                    std::cout << "right click\n";
                }
                else
                {
                }
            }
            // Start algorithm with "space" keyboard
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                std::cout << "Space\n";
                // TODO: Start an algorithm
            }

        }
        // Update

        // Draw
        window.clear();

        window.display();
    }

    return 0;
}
