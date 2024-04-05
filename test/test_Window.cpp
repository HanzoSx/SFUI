#include <SFUI.hpp>

int main()
{
    sfu::Window window;
    window.creat(sf::VideoMode(800, 600), "TITLE");
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
        
        window.getWindow().clear(sf::Color::White);
        window.getWindow().display();

    }
    
    return 0;
}