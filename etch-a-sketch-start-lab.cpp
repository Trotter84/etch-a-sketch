// CSC 195 Spring 2026
// Etch-a-Sketch drawing Lab
//
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int main()
{
    const int WINDOW_HEIGHT = 800u;
    const int WINDOW_WIDTH = 600u;

    sf::RenderWindow window(sf::VideoMode({WINDOW_HEIGHT, WINDOW_WIDTH}), "Etch-a-Sketch");
    window.setFramerateLimit(60);

    // Persistent canvas — can be drawn to without clearing so the trail remains
    sf::RenderTexture canvas(sf::Vector2u{WINDOW_HEIGHT, WINDOW_WIDTH});
    canvas.clear(sf::Color(128, 128, 128));
    canvas.display();
    sf::Sprite canvasSprite(canvas.getTexture());

    bool penDown = true;

    float radius = 5.f;
    float posX = 0.f;
    float posY = 0.f;

    int r = 0;
    int g = 0;
    int b = 0;

    // initialize outline point for pen up
    sf::CircleShape outline(radius);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color(r, g, b));
    outline.setOutlineThickness(2.f);

    // initialize our drawing point
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color(r, g, b));
    shape.setPosition({posX, posY});
    sf::Clock clock;

    std::srand(std::time(nullptr));

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
                    r = std::rand() % 256;
                    g = std::rand() % 256;
                    b = std::rand() % 256;
                    shape.setFillColor(sf::Color(r, g, b));
                    outline.setOutlineColor(sf::Color(r, g, b));
                    break;
                case sf::Keyboard::Key::Hyphen:
                    if (radius > 1.f)
                    {
                        radius = radius - 1.f;
                        shape.setRadius(radius);
                        outline.setRadius(radius);
                    }
                    break;
                case sf::Keyboard::Key::Equal:
                    if (radius < 22.f)
                    {
                        radius = radius + 1.f;
                        shape.setRadius(radius);
                        outline.setRadius(radius);
                    }
                    break;
                case sf::Keyboard::Key::R:
                    canvas.clear(sf::Color(128, 128, 128));
                    canvas.display();
                    break;
                case sf::Keyboard::Key::P:
                    penDown = !penDown;
                    break;
                default:
                    break;
                }
            }
        }
        float dt = clock.restart().asSeconds();
        float speed = 150.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
        {
            speed = 300.f;
        }
        else
        {
            speed = 150.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            posY -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            posY += speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            posX -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            posX += speed * dt;

        posX = std::clamp(posX, 0.f, float(WINDOW_HEIGHT) - radius * 2.f);
        posY = std::clamp(posY, 0.f, float(WINDOW_WIDTH) - radius * 2.f);

        shape.setPosition({posX, posY});
        outline.setPosition({posX, posY});

        // Stamp shape onto the persistent canvas
        if (penDown)
        {
            canvas.draw(shape);
            canvas.display();
        }

        // Render the canvas to the window each frame
        window.clear();
        canvasSprite.setTexture(canvas.getTexture());
        window.draw(canvasSprite);
        window.draw(outline);
        window.display();
    }
    return 0;
}