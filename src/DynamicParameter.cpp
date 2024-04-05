#include <DynamicParameter.hpp>

#include <SFML/System/Clock.hpp>

DynamicParameter::DynamicParameter(float Parameter) : m_changing(false) { set(Parameter); }

void DynamicParameter::set(float Parameter) { stop(); m_parameter = Parameter; }

float DynamicParameter::get() const
{
    if (!m_changing) return m_parameter;
    float elapsed_seconds = m_clock.getElapsedTime().asSeconds();
    float current_parameter;
    switch (m_model)
    {
        case Model::SpeedModel:
            current_parameter = m_parameter + elapsed_seconds * m_speed;
            break;
        
        case Model::TimelimitModel:
            current_parameter = m_parameter + elapsed_seconds / m_timelimit * ( m_endvalue - m_parameter );
            break;

        default:
            break;
    }

    if (m_endvalue - m_parameter >= 0 and current_parameter >= m_endvalue or
        m_endvalue - m_parameter <= 0 and current_parameter <= m_endvalue)
    {
        current_parameter = m_endvalue;
        m_parameter = m_endvalue;
        m_changing = false;
    }
    return current_parameter;
}

void DynamicParameter::speedTO(float End_value, float Speed)
{
    stop(); m_changing = true;
    m_model = Model::SpeedModel;
    m_endvalue = End_value; m_speed = Speed;
    m_clock.restart();
}

void DynamicParameter::timeTO(float End_value, float Timelimit)
{
    stop(); m_changing = true;
    m_model = Model::TimelimitModel;
    m_endvalue = End_value; m_timelimit = Timelimit;
    m_clock.restart();
}

void DynamicParameter::speedHT(float Start_value, float End_value, float Speed)
{
    set(Start_value);
    speedTO(End_value, Speed);
}

void DynamicParameter::timeHT(float Start_value, float End_value, float Timelimit)
{
    set(Start_value);
    timeTO(End_value, Timelimit);
}

bool DynamicParameter::isChanging() const { get(); return m_changing; }
void DynamicParameter::stop() { m_parameter = get(); m_changing = false; }

DynamicParameter::operator float()
{
    return get();
}
