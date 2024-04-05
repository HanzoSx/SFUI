#ifndef SFUI_DYNAMIC_PARAMETER_HPP
#define SFUI_DYNAMIC_PARAMETER_HPP

#include <SFML/System/Clock.hpp>    

class DynamicParameter
{
public:

    // 设置初值
    DynamicParameter(float Parameter = 0.f);

    // 设置值并停止变化
    void set(float Parameter = 0.f);
    // 获取值
    float get() const;

    // 以恒定速度向终值变化
    void speedTO(float End_value, float Speed = 1.f);
    // 以固定时间向终值变化
    void timeTO(float End_value, float Timelimit = 1.f);

    // 以恒定速度从初值向终值变化
    void speedHT(float Start_value, float End_value, float Speed = 1.f);
    // 以固定时间从初值向终值变化
    void timeHT(float Start_value, float End_value, float Timelimit = 1.f);

    // 值是否正在变化
    bool isChanging() const;
    // 停止变化
    void stop();

    // 获取值
    operator float();

private:

    // 记录值，或变化时的初值
    mutable float m_parameter;
    // 记录终值
    float m_endvalue;
    // 循环次数（未使用）
    unsigned int m_loop;

    // 是否正在变化
    mutable bool m_changing;
    // 值变化的模式
    enum Model {SpeedModel, TimelimitModel} m_model;
    // 速度模式下的速度，时间模式下的变化总时间
    float m_speed, m_timelimit;

    sf::Clock m_clock;

};




#endif