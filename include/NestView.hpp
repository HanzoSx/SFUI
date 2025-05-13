#pragma once

#include <SFML/Graphics/View.hpp>

namespace sfu {

class NestView {
public:
    NestView();
    NestView(const sf::Vector2f& position, const sf::Vector2f& size, 
             const sf::Vector2f& offset = {0.f, 0.f});

    NestView(const NestView&) = default;
    NestView(NestView&&) = default;
    NestView& operator=(const NestView&) = default;
    NestView& operator=(NestView&&) = default;

    virtual ~NestView() = default;

    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
    void setOffset(const sf::Vector2f& offset);

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;
    const sf::Vector2f& getOffset() const;
    // const sf::FloatRect getVisiableRect() const;

    NestView& operator* (const NestView& other) const;

    const sf::View& getView() const;
    operator sf::View() const;

    void onParentChanged(NestView &parent);
    
private:
    sf::Vector2f m_position, m_size, m_offset;
    mutable bool m_needUpdate;
    mutable sf::Vector2f m_global_position, m_global_size, m_global_offset;
    mutable sf::View m_view;
};

} // namespace sfu