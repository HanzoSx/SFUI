#ifndef SFUI_CONTROL_WINDOW_HPP
#define SFUI_CONTROL_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <Control.hpp>
#include <ElementHierarchyManager.hpp>

namespace sfu
{

class WindowEvent : public ControlEvent
{
public:

protected:

    static const int count = ControlEvent::count + 0;

};


class Window : public Control, public ElementHierarchyManager<Control>
{
public:
    
    Window();
    ~Window();

    // 有新增控件
    void onElementInserted(Control& element) override;

    enum Type
    {
        childwindow,
        renderwindow
    };
    // 获取窗口的类型
    Type getType() const;

    // 创建渲染窗口，设置窗口类型为 renderwindow
    void creat(sf::VideoMode mode, const sf::String &title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
    // 获取 sf::RenderWindow（必须在 renderwindow 类型中）
    sf::RenderWindow& getWindow() const;
    // 更新 NestView 参数以适应 RenderWindow 的大小
    void update();

    operator sf::RenderWindow&() const;

protected:

    void processEvent(const sf::Event& event) override;

    void render(sf::RenderTarget& target) const override;

private:

    Type m_type;
    sf::RenderWindow* m_window;

};


}

#endif
