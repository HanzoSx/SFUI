#include "NestView.hpp"

namespace sfu
{


NestView::NestView(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Vector2f& offset) : m_father(nullptr)
{
    m_size = size;
    m_position = position;
    m_offset = offset;
}

void NestView::setViewSize(const sf::Vector2f& size)
{
    m_size = size;
}

void NestView::setViewOffset(const sf::Vector2f& offset)
{
    m_offset = offset;
}

void NestView::setViewPosition(const sf::Vector2f& position)
{
    m_position = position;
}

void NestView::setViewFather()
{
    m_father = nullptr;
}

void NestView::setViewFather(const NestView& father)
{
    m_father = &father;
}

const sf::Vector2f NestView::getViewLocalSize() const
{
    return m_size;
}

const sf::Vector2f NestView::getViewLocalOffset() const
{
    return m_offset;
}

const sf::Vector2f NestView::getViewLocalPosition() const
{
    return m_position;
}

const sf::Vector2f NestView::getViewGlobalSize() const
{
    if (m_father == nullptr) return m_size;
    sf::Vector2f father_size = m_father->getViewGlobalSize();
    sf::Vector2f father_offset = m_father->getViewGlobalOffset();
    sf::Vector2f size;
    size.x = std::min(m_position.x + m_size.x, father_offset.x + father_size.x) - std::max(m_position.x, father_offset.x);
    size.y = std::min(m_position.y + m_size.y, father_offset.y + father_size.y) - std::max(m_position.y, father_offset.y);
    return size;
}

const sf::Vector2f NestView::getViewGlobalOffset() const
{
    if (m_father == nullptr) return m_offset;
    sf::Vector2f father_offset = m_father->getViewGlobalOffset();
    sf::Vector2f offset;
    offset.x = m_offset.x + std::max(0.f, father_offset.x - m_position.x);
    offset.y = m_offset.y + std::max(0.f, father_offset.y - m_position.y);
    return offset;
}

const sf::Vector2f NestView::getViewGlobalPosition() const
{
    if (m_father == nullptr) return m_position;
    sf::Vector2f father_position = m_father->getViewGlobalPosition();
    sf::Vector2f father_offset = m_father->getViewGlobalOffset();
    sf::Vector2f position;
    position.x = father_position.x + std::max(0.f, m_position.x - father_offset.x);
    position.y = father_position.y + std::max(0.f, m_position.y - father_offset.y);
    return position;
}

const NestView* NestView::getViewFather() const
{
    return m_father;
}

sf::View NestView::getGlobalView(const sf::RenderTarget& target) const
{
    sf::View view;
    sf::Vector2f global_size = getViewGlobalSize();
    sf::Vector2f global_offset = getViewGlobalOffset();
    sf::Vector2f global_position = getViewGlobalPosition();
    view.reset(sf::FloatRect(
        global_offset.x,
        global_offset.y,
        global_size.x,
        global_size.y
    ));
    sf::Vector2u size = target.getSize();
    view.setViewport(sf::FloatRect(
        global_position.x / size.x,
        global_position.y / size.y,
        global_size.x / size.x,
        global_size.y / size.y
    ));
    return view;
}

sf::Vector2f NestView::getLocalCursorPos(const sf::RenderWindow& window) const
{
    return window.mapPixelToCoords(sf::Mouse::getPosition(window), getGlobalView(window));
}

bool NestView::inBound(const sf::RenderWindow& window) const
{
    sf::FloatRect bound(sf::Vector2f(0, 0), getViewGlobalSize());
    return bound.contains(getLocalCursorPos(window));
}



}

