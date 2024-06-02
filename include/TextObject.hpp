#pragma once

#include <Control.hpp>

class TextObject : public sfu::Control
{
public:

    TextObject();
    
    void setString(const sf::String &string);
    void setFont(sf::Font &font);
    void setCharacterSize(unsigned int size);
    void setFillColor(const sf::Color &color);

    sf::FloatRect getBound() const;
    sf::FloatRect getCharacterBound(unsigned int index) const;

protected:

    void processEvent(const sf::Event& event) override;
    void render(sf::RenderTarget& target) const override;

private:

    void update();
    mutable sf::Text m_text;

};

