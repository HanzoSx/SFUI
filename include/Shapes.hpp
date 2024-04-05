#ifndef SFUI_SHAPES_HPP
#define SFUI_SHAPES_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

namespace sfu
{
const float pi = 3.141592654f;

class CircleFan : public sf::Shape
{
public:

    CircleFan(float radius = 0, size_t pointCount = 30, float fanAngle = 2.f * pi, float startAngle = 0.f);

    void setRadius(float radius);
    void setPointCount(size_t pointCount);
    void setFanAngle(float fanAngle);
    void setStartAngle(float startAngle);

    float getRadius() const;
    float getFanAngle() const;
    float getStartAngle() const;
    size_t getPointCount() const override;
    sf::Vector2f getPoint(size_t index) const override;


private:

    float m_radius;
    size_t m_pointCount;
    float m_fanAngle;
    float m_startAngle;

};


}


#endif