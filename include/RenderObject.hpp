#ifndef SFUI_RENDER_OBJECT_HPP
#define SFUI_RENDER_OBJECT_HPP

#include <list>
#include <SFML/Graphics.hpp>

#include <ElementHierarchyManager.hpp>

namespace sfu
{


class RenderObject : public sf::Drawable, public sf::Transformable, public ElementHierarchyManager<sf::Drawable>
{
public:

    RenderObject();
    RenderObject(sf::FloatRect bound);

    ~RenderObject();

    void setBound(sf::FloatRect bound);

    sf::RenderStates& states();
    sf::FloatRect getBound() const;

private:

    // states is unused, m_states instead
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::FloatRect m_bound;
    sf::RenderStates m_states;

};


class RenderOperations
{
public:


};


}


#endif