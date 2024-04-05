#include <SFUI.hpp>

int main()
{
    sfu::Window window;
    window.creat(sf::VideoMode(800, 600), "TITLE");

    sfu::CircleFan fan(250, 60);
    // fan.setOrigin(250, 250);
    fan.setPosition(150, 50);
    fan.setFillColor(sf::Color(0, 0, 0, 200));

    float radius = 180.f;
    sf::CircleShape circle(radius, 60);
    circle.setOrigin(radius, radius);
    circle.setPosition(400, 300);
    circle.setFillColor(sf::Color::White);

    sf::Clock clock;
    DynamicParameter dp;
    dp.set(0);

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
                
                default:
                    break;
            }
        }

        float time = clock.getElapsedTime().asSeconds() * 3;
        fan.setFanAngle(std::sin(time) * 2 + 2.5);
        fan.setStartAngle(time * 2.4 - std::sin(time) * 2);
        
        window.getWindow().clear(sf::Color::White);
        window.getWindow().draw(fan);
        window.getWindow().draw(circle);
        window.getWindow().display();

    }
    
    return 0;
}