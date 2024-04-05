#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Title");

    sf::RectangleShape rect(sf::Vector2f(400, 300));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(200, 150);

    sf::CircleShape circle(100, 40);
    circle.setRadius(100);
    circle.setOrigin(sf::Vector2f(100, 100));
    circle.setPosition(sf::Vector2f(400, 300));

    sf::Texture texture;
    texture.loadFromFile("resources\\cross.png");
    sf::Sprite sprite(texture);


    sf::Shader shader;
    shader.loadFromFile("shader.frag", sf::Shader::Type::Fragment);

    sf::Vector2i pos;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
                
                case sf::Event::EventType::MouseMoved:
                    pos = sf::Mouse::getPosition(window);
                    // pos = window.mapCoordsToPixel(sf::Vector2f(pos.x, pos.y));
                    std::cout << pos.x << " " << pos.y << "\n";
                    break;

                default:
                    break;
            }
        }
        
        window.clear();

        // sf::View view(sf::FloatRect(200, 150, 800, 600));
        // view.setViewport(sf::FloatRect(0, 0, 1, 1));
        // window.setView(view);

        shader.setUniform("mouse_position", sf::Vector2f(pos.x, 600 - pos.y));
        // window.draw(circle, &shader);
        window.draw(sprite, &shader);
        window.draw(sprite);


        window.display();

    }

    
    return 0;
}
