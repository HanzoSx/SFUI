#include <Window.hpp>

namespace sfu
{


Window::Window() : m_type(Type::childwindow), m_window(nullptr) {}

Window::~Window()
{
    if (m_window != nullptr)
        delete m_window;
}

void Window::render(sf::RenderTarget& target) const
{
    for (size_t i = 0; i < getElementCount(); ++ i)
        target.draw((*this)[i]);
}

void Window::onElementInserted(Control& element)
{
    element.setViewFather(*this);
    element.setRenderWindow(getRenderWindow());
}

Window::Type Window::getType() const
{
    return m_type;
}

void Window::creat(sf::VideoMode mode, const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings)
{
    m_type = Type::renderwindow;
    if (m_window == nullptr)
        m_window = new sf::RenderWindow;
    m_window->create(mode, title, style, settings);
    setRenderWindow(*m_window);
    update();
}

sf::RenderWindow& Window::getWindow() const
{
    return (sf::RenderWindow&)*this;
}

void Window::update()
{
    if (m_type == Type::renderwindow)
    {
        setViewOffset(sf::Vector2f(0, 0));
        setViewPosition(sf::Vector2f(0, 0));
        sf::Vector2u winsize = m_window->getSize();
        setViewSize(sf::Vector2f(winsize.x, winsize.y));
        setViewFather();
    }
}

Window::operator sf::RenderWindow&() const
{
    return *m_window;
}

void Window::processEvent(const sf::Event& event)
{
    Control::processEvent(event);
    enableDelayedProcessing();
    for (int i = 0; i < getElementCount(); ++ i)
        (*this)[i].handleEvent(event);
    disableDelayedProcessing();
}



}
