#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <NestView.hpp>

namespace sfu
{

class Visual : public sf::Drawable, public NestView
{
public:
    Visual() = default;
    Visual(const Visual&) = default;
    Visual(Visual&&) = default;

    Visual& operator=(const Visual&) = default;
    Visual& operator=(Visual&&) = default;

    virtual ~Visual() = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

};
    
} // namespace sfu
