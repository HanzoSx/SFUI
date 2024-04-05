#include <iostream>

class ControlEvent
{
public:

    static const int MouseIn = 0;
    static const int MouseOut = 1;

protected:

    static const int count = 2;

};


class ButtonEvent : public ControlEvent
{
public:

    static const int Click = ControlEvent::count;
    static const int Relese = ControlEvent::count + 1;

protected:

    static const int count = ControlEvent::count + 2;

};

int main()
{
    std::cout << ControlEvent::MouseIn << "\n";
    std::cout << ControlEvent::MouseOut << "\n";

    std::cout << ButtonEvent::MouseIn << "\n";
    std::cout << ButtonEvent::MouseOut << "\n";

    std::cout << ButtonEvent::Click << "\n";
    std::cout << ButtonEvent::Relese << "\n";
    return 0;
}
