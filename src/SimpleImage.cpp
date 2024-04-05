#include <SimpleImage.hpp>

namespace sfu
{

SimpleImage::SimpleImage() {}

SimpleImage::SimpleImage(const sf::Drawable& drawable) : m_drawable(&drawable) {}

void SimpleImage::render(sf::RenderTarget& target) const
{
    target.draw(*m_drawable);
}

void SimpleImage::setDrawableTarget(const sf::Drawable& drawable)
{
    m_drawable = &drawable;
}

void SimpleImage::processEvent(const sf::Event& event) {}


}