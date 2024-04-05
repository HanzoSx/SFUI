#include <iostream>
#include <iomanip>
#include <string>
#include <ElementHierarchyManager.hpp>

template <typename T>
void show(ElementHierarchyManager<T>& elementHM)
{
    for (int i = 0; i < elementHM.getSize(); ++ i)
        std::cout << std::setw(14) << elementHM[i];
    std::cout << "\n";

    for (int i = 0; i < elementHM.getSize(); ++ i)
        std::cout << std::setw(14) << &elementHM[i];
    std::cout << "\n";
    
    for (int i = 0; i < elementHM.getSize(); ++ i)
        std::cout << std::setw(14) << elementHM.getElementInfo(i).level;
    std::cout << "\n";
}

std::vector<int*> v;
int& Ele(int val)
{
    for (auto& it : v)
        if (*it == val) return *it;
    v.push_back(new int(val));
    return *v.back();
}

int main()
{
    ElementHierarchyManager<int> intHM;
    
    while (true)
    {
        std::string opt;
        int element;
        int level;
        int delta;
        size_t place;

        std::cin >> opt;
        if (opt == "insert")
        {
            std::cin >> element >> level;
            intHM.insert(Ele(element), level);
        }
        else if (opt == "push_front")
        {
            std::cin >> element;
            intHM.push_front(Ele(element));
        }
        else if (opt == "push_back")
        {
            std::cin >> element;
            intHM.push_back(Ele(element));
        }
        else if (opt == "reindex")
        {
            intHM.reindex();
        }
        else if (opt == "moveLevel")
        {
            std::cin >> level >> delta;
            intHM.moveLevel(level, delta);
        }
        else if (opt == "moveElement")
        {
            std::cin >> element >> delta;
            intHM.moveElement(Ele(element), delta);
        }
        else if (opt == "moveUpLevel")
        {
            std::cin >> level;
            intHM.moveUpLevel(level);
        }
        else if (opt == "moveDownLevel")
        {
            std::cin >> level;
            intHM.moveDownLevel(level);
        }
        else if (opt == "moveFrontLevel")
        {
            std::cin >> level;
            intHM.moveFrontLevel(level);
        }
        else if (opt == "moveBackLevel")
        {
            std::cin >> level;
            intHM.moveBackLevel(level);
        }
        else if (opt == "moveUpElement")
        {
            std::cin >> element;
            intHM.moveUpElement(Ele(element));
        }
        else if (opt == "moveDownElement")
        {
            std::cin >> element;
            intHM.moveDownElement(Ele(element));
        }
        else if (opt == "moveFrontElement")
        {
            std::cin >> element;
            intHM.moveFrontElement(Ele(element));
        }
        else if (opt == "moveBackElement")
        {
            std::cin >> element;
            intHM.moveBackElement(Ele(element));
        }
        else if (opt == "getSize")
        {
            std::cout << intHM.getElementCount() << "\n";
        }
        else if (opt == "getElementLevel")
        {
            std::cin >> element;
            std::cout << intHM.getElementLevel(Ele(element)) << "\n";
        }
        else if (opt == "getLevelElement")
        {
            std::cin >> level;
            if (intHM.getLevelElement(level))
                std::cout << intHM.getLevelElement(level) << "\n";
        }
        else if (opt == "getElementInfo")
        {
            std::cin >> place;
            std::cout << intHM.getElementInfo(place).element << "  " << 
                intHM.getElementInfo(place).level << "\n";
        }
        else if (opt == "[]")
        {
            std::cin >> place;
            if (intHM[place])
                std::cout << intHM[place] << "\n";
        }
        else if (opt == "eraseElement")
        {
            std::cin >> element;
            intHM.eraseElement(Ele(element));
        }
        else if (opt == "eraseLevel")
        {
            std::cin >> level;
            intHM.eraseLevel(level);
        }
        else if (opt == "pop_front")
        {
            intHM.pop_front();
        }
        else if (opt == "pop_back")
        {
            intHM.pop_back();
        }
        else if (opt == "enable")
        {
            intHM.enableDelayedProcessing();
        }
        else if (opt == "disable")
        {
            intHM.disableDelayedProcessing();
        }
        else
        {
            std::cout << "Unknow opt\n";
        }
    
        show(intHM);
    }


    // system("pause");
    return 0;
}