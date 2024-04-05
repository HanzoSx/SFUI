#include <RenderObject.hpp>

#include <algorithm>

namespace sfu
{

RenderObject::RenderObject() {}

RenderObject::RenderObject(sf::FloatRect bound)
{
    setBound(bound);
}
RenderObject::~RenderObject() {}


void RenderObject::setBound(sf::FloatRect bound)
{
    m_bound = bound;
}

sf::RenderStates& RenderObject::states()
{
    return m_states;
}

sf::FloatRect RenderObject::getBound() const
{
    return m_bound;
}

void RenderObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (getElementCount() > 0)
    {
        states = m_states;
        states.transform = getTransform();
        for (size_t i = 0; i < getElementCount(); ++ i)
            target.draw(at(i), states);
    }
}


}
