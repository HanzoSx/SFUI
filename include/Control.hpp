#ifndef SFUI_CONTROL_HPP
#define SFUI_CONTROL_HPP

#include <queue>

#include <SFML/Graphics.hpp>
#include <NestView.hpp>

namespace sfu
{

class ControlEvent
{
public:

    static const int MouseEntered = 0;
    static const int MouseLeft    = 1;

protected:

    static const int count        = 2;

};


class Control : public NestView, public sf::Drawable
{
public:

    Control();

    // 处理事件
    void handleEvent(const sf::Event& event);
    // 获取事件
    int pollEvent();

    // 获取设定窗口（如果没有则返回false）下鼠标指针是否在判定框内（默认为NestView视口框）
    virtual bool inBound() const;

    // 启用事件响应
    void enable();
    // 禁用事件响应
    void disable();
    // 设置是否响应事件
    void setEnabled(const bool enabled);

    // 使控件可见
    void visiable();
    // 使控件不可见
    void invisiable();
    // 设置控件是否可见
    void setVisiabled(const bool visiabled);
    
    // 设置控件响应事件对应的窗口
    void setRenderWindow(sf::RenderWindow& window);

    // 获取控件是否响应事件
    bool isable() const;
    // 获取控件是否可见
    bool isvisiable() const;
    // 获取控件响应事件对应的窗口
    sf::RenderWindow& getRenderWindow() const;

protected:

    virtual void processEvent(const sf::Event& event);

    // 渲染虚函数
    virtual void render(sf::RenderTarget& target) const = 0;
    // 重载 Drawable 类 draw 函数
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // 向事件队列加入事件
    void push_event(int eventID);

private:

    std::queue<int> m_event;

    bool m_able, m_visiable;
    bool m_inbound;
    sf::RenderWindow *m_window;

};


}

#endif