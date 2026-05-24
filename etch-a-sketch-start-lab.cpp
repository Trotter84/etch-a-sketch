// CSC 195 Spring 2026
// Etch-a-Sketch drawing Lab
//
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <ctime>
int main()
{
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Etch-a-Sketch");
    window.setFramerateLimit(60);
    // Persistent canvas — can be drawn to without clearing so the trail remains
    sf::RenderTexture canvas(sf::Vector2u{800u, 600u});
    canvas.clear(sf::Color(128, 128, 128));
    canvas.display();
    sf::Sprite canvasSprite(canvas.getTexture());
    float radius = 5.f;
    float posX = 0.f;
    float posY = 0.f;
    // initialize our drawing point
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition({posX, posY});
    sf::Clock clock;
    // main game loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto *key = event->getIf<sf::Event::KeyPressed>())
            {
                switch (key->code)
                {
                case sf::Keyboard::Key::C:
                    // TODO - change shape color
                    break;
                case sf::Keyboard::Key::Hyphen:
                    // TODO - change shape size
                    break;
                case sf::Keyboard::Key::Equal:
                    // TODO - change shape size
                    break;
                case sf::Keyboard::Key::R:
                    // TODO - reset/clear screen
                    break;
                case sf::Keyboard::Key::P:
                    // TODO - lift drawing point up/down
                    break;
                default:
                    break;
                }
            }
        }
        float dt = clock.restart().asSeconds();
        float speed = 150.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            posY -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            posY += speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            posX -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            posX += speed * dt;
        // TODO: Keep the shape fully within the window
        shape.setPosition({posX, posY});
        // Stamp shape onto the persistent canvas
        canvas.clear(sf::Color(128, 128, 128));
        canvas.draw(shape);
        canvas.display();
        // Render the canvas to the window each frame
        window.clear();
        canvasSprite.setTexture(canvas.getTexture());
        window.draw(canvasSprite);
        window.display();
    }
    return 0;
}