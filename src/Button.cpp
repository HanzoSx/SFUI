#include <Button.hpp>

namespace sfu
{


Button::Button()
{
    for (auto& it : m_keystate)
        it = KeyState::free;
    for (auto& it : m_pressed)
        it = false;
    // handleEvent(sf::Event());
}

void Button::processEvent(const sf::Event& event)
{
    Control::processEvent(event);
    
    bool pressed = false;
    bool changed = false;

    for (int i = 0; i < sf::Mouse::Button::ButtonCount; ++ i)
    {
        auto key = static_cast<sf::Mouse::Button>(i);
        KeyState state = m_keystate[i];
        m_pressed[i] = false;
        m_changed[i] = false;

        if (!inBound())
            m_keystate[i] = KeyState::free;
        else if (m_keystate[i] != KeyState::press and !sf::Mouse::isButtonPressed(key))
            m_keystate[i] = KeyState::hover;

        if (state != m_keystate[i])
            m_changed[i] = changed = true;
    }

    switch (event.type)
    {
        case sf::Event::EventType::MouseButtonPressed:
            if (m_keystate[event.mouseButton.button] == KeyState::hover)
            {
                m_keystate[event.mouseButton.button] = KeyState::press;
                m_changed[event.mouseButton.button] = changed = true;
            }
            break;

        case sf::Event::EventType::MouseButtonReleased:
            if (m_keystate[event.mouseButton.button] == KeyState::press)
            {
                m_keystate[event.mouseButton.button] = KeyState::hover;
                m_pressed[event.mouseButton.button] = pressed = true;
                m_changed[event.mouseButton.button] = changed = true;
            }
            break;
        
        default:
            break;
    }
    
    if (pressed) push_event(ButtonEvent::Pressed);
    if (changed) push_event(ButtonEvent::KeyStateChanged);
}

Button::KeyState Button::getKeyState(const sf::Mouse::Button button) const
{
    return m_keystate[button];
}

bool Button::isKeyStateChanged(const sf::Mouse::Button button) const
{
    return m_changed[button];
}

bool Button::isPressed(const sf::Mouse::Button button) const
{
    return m_pressed[button];
}


}
