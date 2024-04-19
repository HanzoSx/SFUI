#include <Control.hpp>

namespace sfu
{

Control::Control() : m_able(true), m_visiable(true), m_window(nullptr), m_inbound(false) {}


void Control::handleEvent(const sf::Event& event)
{
    if (m_able)
        processEvent(event);
}

int Control::pollEvent()
{
    int eventID = m_event.front();
    m_event.pop();
    return eventID;
}

bool Control::inBound() const
{
    if (m_window == nullptr) return false;
    return NestView::inBound(*m_window);
}

void Control::enable() { m_able = true; }

void Control::disable() { m_able = false;}

void Control::setEnabled(const bool enable) { m_able = enable; }

void Control::visiable() { m_visiable = true; }

void Control::invisiable() { m_visiable = false; }

void Control::setVisiabled(const bool visiabled) { m_visiable = visiabled; }

void Control::setRenderWindow(sf::RenderWindow& window)
{
    m_window = &window;
    if (m_inbound = inBound()) push_event(ControlEvent::MouseEntered);
}

bool Control::isable() const { return m_able; }

bool Control::isvisiable() const { return m_visiable; }

sf::RenderWindow& Control::getRenderWindow() const
{
    if (m_window == nullptr)
    {
        NestView *ptrFather = const_cast<NestView*>(getViewFather());
        if (ptrFather != nullptr)
        {
            Control *ptrControl = static_cast<Control*>(ptrFather);
            return ptrControl->getRenderWindow();
        }
    }
    return *m_window;
}

void Control::processEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::EventType::MouseMoved:
        {
            bool temp = inBound();
            if (temp != m_inbound)
            {
                push_event(m_inbound ? ControlEvent::MouseLeft : ControlEvent::MouseEntered);
                m_inbound = temp;
            }
            break;
        }
        
        default:
            break;
    }
}

void Control::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_visiable)
    {
        target.setView(getGlobalView(target));
        render(target);
    }
}

void Control::push_event(int eventID)
{
    m_event.push(eventID);
}

}
