#include <Shapes.hpp>

namespace sfu
{


CircleFan::CircleFan(float radius, size_t pointCount, float fanAngle, float startAngle) :
m_radius    (radius),
m_pointCount(pointCount),
m_fanAngle  (fanAngle),
m_startAngle(startAngle)
{
    update();
}

void CircleFan::setRadius(float radius)
{
    m_radius = radius;
    update();
}

void CircleFan::setPointCount(size_t pointCount)
{
    m_pointCount = pointCount;
    update();
}

void CircleFan::setFanAngle(float fanAngle)
{
    m_fanAngle = fanAngle;
    update();
}

void CircleFan::setStartAngle(float startAngle)
{
    m_startAngle = startAngle;
    update();
}

float CircleFan::getRadius() const
{
    return m_radius;
}

float CircleFan::getFanAngle() const
{
    return m_fanAngle;
}

float CircleFan::getStartAngle() const
{
    return m_startAngle;
}

size_t CircleFan::getPointCount() const
{
    return m_pointCount + 2;
}

sf::Vector2f CircleFan::getPoint(size_t index) const
{
    if (index == 0) return sf::Vector2f(m_radius, m_radius);

    float angle = static_cast<float>(index - 1) * m_fanAngle / static_cast<float>(m_pointCount) + m_startAngle;
    float x = std::cos(angle) * m_radius;
    float y = - std::sin(angle) * m_radius;

    return sf::Vector2f(m_radius + x, m_radius + y);
}


}
