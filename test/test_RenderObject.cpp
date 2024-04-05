#include <iostream>
#include <SFML/Graphics.hpp>

#include <SFUI.hpp>

int main()
{
    sfu::Window window;
    window.creat(sf::VideoMode(800, 600), "SFML Title");
    window.setWindow(window.getWindow());

    sf::Texture texture1;
    sf::Texture texture2;
    texture1.loadFromFile("resources\\cross.png");
    texture2.loadFromFile("resources\\circle.png");
    sf::Sprite sprite1(texture1), sprite2(texture2);

    sfu::RenderObject obj1, obj2, obj;
    obj.push_back(obj1);
    obj.push_back(obj2);

    obj1.push_back(sprite1);
    obj2.push_back(sprite2);

    obj1.move(50, 50);

    sfu::SimpleImage image(obj);
    image.setSize(sf::Vector2f(sprite1.getLocalBounds().width, sprite1.getLocalBounds().height));
    image.setPosition(sf::Vector2f(200, 150));

    window.push_back(image);
    // image.setFather(window);
    // image.setTarget(window.getWindow());

    while (window.getWindow().isOpen())
    {
        sf::Event event;
        while (window.getWindow().pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::EventType::Closed:
                    window.getWindow().close();
                    break;

                case sf::Event::EventType::MouseMoved:
                    // window.setOffset(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
        
                    // std::cout << image.getGlobalView(window.getWindow()).getCenter().x << " ";
                    // std::cout << image.getGlobalView(window.getWindow()).getCenter().y << "\n";
                    // std::cout << image.getGlobalView(window.getWindow()).getSize().x << " ";
                    // std::cout << image.getGlobalView(window.getWindow()).getSize().y << "\n";
                    // std::cout << image.getGlobalView(window.getWindow()).getViewport().left << " ";
                    // std::cout << image.getGlobalView(window.getWindow()).getViewport().top << " ";
                    // std::cout << image.getGlobalView(window.getWindow()).getViewport().width << " ";
                    // std::cout << image.getGlobalView(window.getWindow()).getViewport().height << "\n\n";

                    // std::cout << image.getGlobalPosition().x << " ";
                    // std::cout << image.getGlobalPosition().y << "\n";
                    // std::cout << image.getGlobalOffset().x << " ";
                    // std::cout << image.getGlobalOffset().y << "\n";
                    // std::cout << image.getGlobalSize().x << " ";
                    // std::cout << image.getGlobalSize().y << "\n\n";


                    break;
                
                default:
                    break;
            }
        }

        window.getWindow().clear(sf::Color::White);

        window.draw();
        // obj.draw(window.getWindow());
        // image.draw();

        window.getWindow().display();

    }
    

    return 0;
}
