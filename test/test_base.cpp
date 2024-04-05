#include <iostream>

class Base
{
public:
    virtual void print()
    {
        std::cout << "Base print\n";
    }
};


class Son1 : public Base
{
public:
    void print() override
    {
        std::cout << "Son1 print\n";
    }
};


class Son2 : public Base
{
public:
    void print() override
    {
        std::cout << "Son2 print\n";
    }
};

class Son : public Son1, public Son2
{
public:

};


int main()
{
    Son SonObj;
    // SonObj.Son1::Base::print(); error
    return 0;
}