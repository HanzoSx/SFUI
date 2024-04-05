#ifndef SFUI_NEST_VIEW_HPP
#define SFUI_NEST_VIEW_HPP

#include <SFML/Graphics.hpp>

namespace sfu
{


class NestView
{
public:

    NestView(
        const sf::Vector2f& size = sf::Vector2f(0, 0),
        const sf::Vector2f& position = sf::Vector2f(0, 0),
        const sf::Vector2f& offset = sf::Vector2f(0, 0)
    );

    // 设置视口大小
    void setViewSize(const sf::Vector2f& size);
    //设置视口在纹理采样的起点（左上角）
    void setViewOffset(const sf::Vector2f& offset);
    // 设置视口在父级窗口的位置
    void setViewPosition(const sf::Vector2f& position);

    // 设置父级窗口为空
    void setViewFather();
    // 设置父级窗口
    void setViewFather(const NestView& father);

    // 获取当前视口的大小
    const sf::Vector2f getViewLocalSize() const;
    // 获取当前视口在纹理采样的起点
    const sf::Vector2f getViewLocalOffset() const;
    // 获取当前视口在父级窗口的位置
    const sf::Vector2f getViewLocalPosition() const;

    // 获取视口的全局大小
    const sf::Vector2f getViewGlobalSize() const;
    // 获取视口的全局在纹理采样的起点
    const sf::Vector2f getViewGlobalOffset() const;
    // 获取视口的全局位置
    const sf::Vector2f getViewGlobalPosition() const;

    // 获取父级窗口指针
    const NestView* getViewFather() const;
    // 获取全局视口在 target 下的 sf::View 格式
    sf::View getGlobalView(const sf::RenderTarget& target) const;

    // 获取视口在 window 下的光标位置在纹理中的像素坐标
    sf::Vector2f getLocalCursorPos(const sf::RenderWindow& window) const;
    // 获取视口在 window 下光标位置是否在视口内
    bool inBound(const sf::RenderWindow& window) const;

private:
    
    const NestView* m_father;
    sf::Vector2f m_size, m_position, m_offset;

};


}


#endif