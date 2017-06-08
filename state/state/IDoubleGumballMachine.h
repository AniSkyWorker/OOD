#pragma once
#include <string>

class IDoubleGumballMachine
{
public:
    virtual void InsertQuarter() = 0;
    virtual void EjectQuarters() = 0;
    virtual void TurnCrank() = 0;
    virtual void Refill(unsigned numBalls) = 0;
    virtual std::string ToString()const = 0;

    virtual ~IDoubleGumballMachine() = default;
};