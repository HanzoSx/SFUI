#include <iostream>
#include <algorithm>

#include <SFUI.hpp>
#include <GoogleLikeButton.hpp>

int main()
{
    sfu::Window UIwindow;
    UIwindow.creat(sf::VideoMode(800, 600), "GoogleLike Button");
    sf::RenderWindow &window = UIwindow.getWindow();

    sf::RectangleShape rect(sf::Vector2f(40, 30));
    rect.setPosition(0, 0);
    rect.setFillColor(sf::Color::Blue);

    sfu::GoogleLikeButton button(rect, 60, 40);
    button.setViewPosition(sf::Vector2f(100, 20));
    UIwindow.push_back(button);

    // DynamicParameter dp(0); // *

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
                
                default:
                    break;
            }

            UIwindow.handleEvent(event);
            // if (button.isPressed(sf::Mouse::Button::Left))
            // {
            //     std::cout << "click\n";
            //     if (button.isSelect()) button.Unselect();
            //         else button.Select();
            // }
        }
        
        window.clear(sf::Color::White);
        window.draw(UIwindow);
        window.display();
    }
    

    return 0;
}
