#ifndef SFUI_CONTROL_SIMPLE_IMAGE_HPP
#define SFUI_CONTROL_SIMPLE_IMAGE_HPP

#include <Control.hpp>

namespace sfu
{


class SimpleImage : public Control
{
public:

    SimpleImage();
    SimpleImage(const sf::Drawable& drawable);

    void render(sf::RenderTarget& target) const override;
    void setDrawableTarget(const sf::Drawable& drawable);

protected:

    void processEvent(const sf::Event& event) override;

private:

    const sf::Drawable* m_drawable;

};


}

#endif