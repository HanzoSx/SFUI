#ifndef SFUI_CONTROL_BUTTON_HPP
#define SFUI_CONTROL_BUTTON_HPP

#include <Control.hpp>

namespace sfu
{

class ButtonEvent : public ControlEvent
{
public:

    static const int Pressed         = ControlEvent::count + 0;
    static const int KeyStateChanged = ControlEvent::count + 1;

protected:

    static const int count           = ControlEvent::count + 2;

};


class Button : public Control
{
public:

    Button();

    enum KeyState
    {
        free,
        hover,
        press
    };
    KeyState getKeyState(const sf::Mouse::Button button) const;
    bool isKeyStateChanged(const sf::Mouse::Button button) const;
    bool isPressed(const sf::Mouse::Button button) const;

protected:

    void processEvent(const sf::Event& event) override;

private:
    
    KeyState m_keystate[sf::Mouse::ButtonCount];
    bool m_changed[sf::Mouse::ButtonCount];
    bool m_pressed[sf::Mouse::ButtonCount];

};


}



#endif
