#ifndef SFUI_ELEMENT_HIERARCHY_MANAGER_HPP
#define SFUI_ELEMENT_HIERARCHY_MANAGER_HPP

#include <iostream>
#include <vector>

template <typename T>
class ElementHierarchyManager
{
public:

    ElementHierarchyManager() : m_delayedProcessing(false) {}
    ~ElementHierarchyManager() {}

    struct ElementInfo
    {
        T* element;
        int level;
    };

    virtual void onElementInserted(T& element) {}

    void insert(T& element, int level)
    {
        if (m_delayedProcessing)
        {
            Processes temp;
            temp.type = Processes::Type::insert;
            temp.parameter.element = &element;
            temp.parameter.level = level;
            m_processes.push_back(temp);
            return;
        }

        onElementInserted(element);

        m_vect.push_back(ElementInfo());
        auto rit = m_vect.rbegin() + 1;
        for (; rit != m_vect.rend(); ++ rit)
            if ((*rit).level >= level)
                *(rit - 1) = *rit;
            else
                break;
        *(rit - 1) = {&element, level};
        for (auto it = rit.base(); it != m_vect.end(); ++ it)
            if ((it - 1)->level == it->level)
                it->level ++;
    }
    void push_front(T& element)
    {
        insert(element, m_vect.empty() ? 1 : m_vect.front().level - 1);
    }
    void push_back(T& element)
    {
        insert(element, m_vect.empty() ? 1 : m_vect.back().level + 1);
    }

    void reindex()
    {
        if (m_delayedProcessing)
        {
            Processes temp;
            temp.type = Processes::Type::reindex;
            m_processes.push_back(temp);
            return;
        }

        int index = 0;
        for (auto it = m_vect.begin(); it != m_vect.end(); ++ it)
            it->level = ++ index;
    }
    void moveElement(typename std::vector<ElementInfo>::iterator it, int delta)
    {
        if (delta > 0) ++ it;
        while (delta and it != m_vect.end() and it != m_vect.begin())
        {
            std::swap(it->element, (it - 1)->element);
            it += delta > 0 ? 1 : -1;   
            delta += delta > 0 ? -1 : 1;
        }
    }
    void moveLevel(int level, int delta)
    {
        if (m_delayedProcessing)
        {
            Processes temp;
            temp.type = Processes::Type::move_level;
            temp.parameter.level = level;
            temp.parameter.delta = delta;
            m_processes.push_back(temp);
            return;
        }

        for (auto it = m_vect.begin(); it != m_vect.end(); ++ it)
            if (it->level == level)
                moveElement(it, delta);
    }
    void moveElement(T& element, int delta)
    {
        if (m_delayedProcessing)
        {
            Processes temp;
            temp.type = Processes::Type::move_element;
            temp.parameter.element = &element;
            temp.parameter.delta = delta;
            m_processes.push_back(temp);
            return;
        }

        for (auto it = m_vect.begin(); it != m_vect.end(); ++ it)
            if (it->element == &element)
                moveElement(it, delta);
    }
    void moveUpLevel(int level) { moveLevel(level, -1); }
    void moveDownLevel(int level) { moveLevel(level, 1); }
    void moveFrontLevel(int level) { moveLevel(level, -getElementCount()); }
    void moveBackLevel(int level) { moveLevel(level, getElementCount()); }
    void moveUpElement(T& element) { moveElement(element, -1); }
    void moveDownElement(T& element) { moveElement(element, 1); }
    void moveFrontElement(T& element) { moveElement(element, -getElementCount()); }
    void moveBackElement(T& element) { moveElement(element, getElementCount()); }

    int getElementCount() const { return m_vect.size(); }
    int getElementLevel(T& element) const
    {
        for (auto it = m_vect.begin(); it != m_vect.end(); ++ it)
            if (it->element == &element)
                return it->level;
        std::cerr << "[ElementHM] getElementLevel : Can't found element\n";
        return 0;
    }
    T& getLevelElement(int level)
    {
        for (auto it = m_vect.begin(); it != m_vect.end(); ++ it)
            if (it->level == level)
                return *(it->element);
        std::cerr << "[ElementHM] getLevelElement : Can't found element\n";
        return *(m_vect.back().element);
    }
    const ElementInfo& getElementInfo(const size_t place) const
    {
        if (place < 0 or place >= m_vect.size())
        {
            std::cerr << "[ElementHM] getElementInfo : Out of range\n";
        }
        return m_vect.at(place);
    }
    T& at(const size_t place) const
    {
        if (place < 0 or place >= m_vect.size())
        {
            std::cerr << "[ElementHM] operator [] : Out of range\n";
            // return ?;
        }
        return *(m_vect.at(place).element);
    }
    T& operator [] (const size_t place) const
    {
        if (place < 0 or place >= m_vect.size())
        {
            std::cerr << "[ElementHM] operator [] : Out of range\n";
            // return ?;
        }
        return *(m_vect.at(place).element);
    }

    void eraseElement(T& element)
    {
        if (m_delayedProcessing)
        {
            Processes temp;
            temp.type = Processes::Type::erase_element;
            temp.parameter.element = &element;
            m_processes.push_back(temp);
            return;
        }

        for (auto it = m_vect.begin(); it != m_vect.end(); ++ it)
            if (it->element == &element)
            {
                m_vect.erase(it);
                return;
            }
        std::cerr << "[ElementHM] erase : Can't find element\n";
    }
    void eraseLevel(int level)
    {
        if (m_delayedProcessing)
        {
            Processes temp;
            temp.type = Processes::Type::erase_level;
            temp.parameter.level = level;
            m_processes.push_back(temp);
            return;
        }

        for (auto it = m_vect.begin(); it != m_vect.end(); ++ it)
            if (it->level == level)
            {
                m_vect.erase(it);
                return;
            }
        std::cerr << "[element] erase : Can't find level\n";
    }
    void pop_front()
    {
        if(m_delayedProcessing)
        {
            Processes temp;
            temp.type = Processes::Type::pop_front;
            m_processes.push_back(temp);
            return;
        }

        if (!m_vect.empty())
        {
            for (auto it = m_vect.begin(); it != m_vect.end() - 1; ++ it)
                *it = *(it + 1);
            m_vect.pop_back();
        }
    }
    void pop_back()
    {
        if (m_delayedProcessing)
        {
            Processes temp;
            temp.type = Processes::Type::pop_back;
            m_processes.push_back(temp);
            return;
        }

        if (!m_vect.empty())
        {
            m_vect.pop_back();
        }
    }

    void enableDelayedProcessing()
    {
        if (m_delayedProcessing) return;
        m_delayedProcessing = true;
    }
    void disableDelayedProcessing()
    {
        if (!m_delayedProcessing) return;
        m_delayedProcessing = false;
        for (auto process : m_processes)
        {
            switch (process.type)
            {
                case Processes::Type::reindex:
                    reindex();
                    break;

                case Processes::Type::insert:
                    insert(*process.parameter.element, process.parameter.level);
                    break;

                case Processes::Type::move_level:
                    moveLevel(process.parameter.level, process.parameter.delta);
                    break;
                
                case Processes::Type::move_element:
                    moveElement(*process.parameter.element, process.parameter.delta);
                    break;

                case Processes::Type::erase_level:
                    eraseLevel(process.parameter.level);
                    break;
                
                case Processes::Type::erase_element:
                    eraseElement(*process.parameter.element);
                    break;
                
                case Processes::Type::pop_front:
                    pop_front();
                    break;
                    
                case Processes::Type::pop_back:
                    pop_back();
                    break;


                default:
                    break;
            }
        }
        m_processes.clear();
    }

private:

    std::vector<ElementInfo> m_vect;

    bool m_delayedProcessing;
    struct Processes
    {
        enum Type
        {
            reindex,
            insert,
            move_level,
            move_element,
            erase_level,
            erase_element,
            pop_front,
            pop_back
        }   type;
        struct Parameter
        {
            T* element;
            int level;
            int delta;
        }   parameter;
    };
    
    std::vector<Processes> m_processes;

};

#endif