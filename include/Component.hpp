#pragma once

#include <unordered_set>

namespace sfu
{

template<typename T>
class Component
{
public:
    Component();
    Component(const Component&) = default;
    Component(Component&&) = default;
    Component& operator=(const Component&) = default;
    Component& operator=(Component&&) = default;

    virtual ~Component() = default; 

    void setParent(T* parent);
    T* getParent() const;

    void addChild(T* child);
    void removeChild(T* child);
    const std::unordered_set<T*>& getChildren() const;

private:
    T* m_parent; 
    std::unordered_set<T*> m_child; 
};

} // namespace sfu
