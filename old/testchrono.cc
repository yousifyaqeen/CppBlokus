#include <SFML/Graphics.hpp>
#include "Chronometer.hpp"
#include <cmath>

int main (int, const char**)
{
    // Create a chronometer
    sftools::Chronometer chrono;

    // Create the main window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(300, 300), "Chronometer", sf::Style::Close, settings);

    sf::Vector2f const center = window.getView().getCenter();
    float const clockRadius = 100.f;

    sf::CircleShape clockFrame(clockRadius, 100);

    // Setup the clock frame
    sf::FloatRect clockBounds = clockFrame.getLocalBounds();
    sf::Vector2f clockSize(clockBounds.width, clockBounds.height);
    clockFrame.setOrigin(clockSize / 2.f);
    clockFrame.setPosition(center);
    clockFrame.setOutlineThickness(4);
    clockFrame.setOutlineColor(sf::Color::Black);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            // Handle the chronometer's commands
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::T:
                        chrono.toggle(); // start/pause according to the current state of the chrono
                        break;

                    case sf::Keyboard::P:
                        chrono.pause(); // pause it if it was running
                        break;

                    case sf::Keyboard::R:
                        chrono.resume(); // resume it if it was paused
                        break;

                    case sf::Keyboard::S:
                        chrono.reset(); // reset the chrono but do not start it
                        break;

                    case sf::Keyboard::D:
                        chrono.reset(true); // reset and restart the chrono
                        break;

                    case sf::Keyboard::A:
                        chrono.add(sf::seconds(5)); // add 5 sec to the chrono
                        break;

                    default:
                        break;
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw the frame
        window.draw(clockFrame);

        // Display the clock hand :

        sf::Time time = chrono; // or chrono.getElapsedTime();
        int seconds = time.asSeconds(); // discard decimals
        float angle = M_PI * 2 / 60.f * seconds; // in RAD
        sf::Vector2f clockHandVector = sf::Vector2f(std::sin(angle), - std::cos(angle)) * clockRadius;
        // Create two vertices
        sf::Vector2f clockHandStart = center;
        sf::Vector2f clockHandEnd = clockHandStart + clockHandVector;
        sf::Vertex vertices[2] =
        {
            sf::Vertex(clockHandStart, sf::Color::Red),
            sf::Vertex(clockHandEnd, sf::Color::Red)
        };
        window.draw(vertices, 2, sf::PrimitiveType::Lines);

        window.display();
    }

    return EXIT_SUCCESS;
}
