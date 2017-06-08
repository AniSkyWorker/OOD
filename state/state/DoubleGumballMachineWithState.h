#pragma once
#include "IDoubleGumballMachine.h"
#include <iostream>
#include <boost\format.hpp>

namespace with_dynamic_state_d
{
class IState
{
public:
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarters() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual void Refill(unsigned numBalls) = 0;
	virtual std::string ToString()const = 0;

	virtual ~IState() = default;
};

class IDoubleGumballMachineContext
{
public:
	virtual void ReleaseGumball() = 0;
    virtual void SetGumballs(unsigned numBalls) = 0;
    virtual void CollectQuarter() = 0;
    virtual void SpendQuarter() = 0;
    virtual void ReturnQuarters() = 0;
	virtual unsigned GetGumballCount()const = 0;
	virtual unsigned GetQuarterCount() const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IDoubleGumballMachineContext() = default;
};

class CSoldState : public IState
{
public:
	CSoldState(IDoubleGumballMachineContext& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}
	void InsertQuarter() final
	{
		m_gumballMachine.CollectQuarter();
	}
	void EjectQuarters() final
	{
		m_gumballMachine.ReturnQuarters();
	}
	void TurnCrank() final
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() final
	{
		m_gumballMachine.ReleaseGumball();
		if (m_gumballMachine.GetGumballCount() == 0)
		{
			std::cout << "Out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else if (m_gumballMachine.GetQuarterCount() == 0)
		{
			m_gumballMachine.SetNoQuarterState();
		}
		else
		{
			m_gumballMachine.SetHasQuarterState();
		}
	}
	std::string ToString() const final
	{
		return "gumball is comin`";
	}
	void Refill(unsigned ballCount) final
	{
		m_gumballMachine.SetGumballs(ballCount);
	}
private:
    IDoubleGumballMachineContext& m_gumballMachine;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IDoubleGumballMachineContext& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}
	void InsertQuarter() final
	{
		std::cout << "Sorry, machine is sold out\n";
	}
	void EjectQuarters() final
	{
		if (m_gumballMachine.GetQuarterCount() == 0)
		{
			std::cout << "No more quarters in machine\n";
		}
		else
		{
			m_gumballMachine.ReturnQuarters();
		}
	}
	void TurnCrank() final
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() final
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const final
	{
		return "sold out";
	}
	void Refill(unsigned numBalls) final
	{
		m_gumballMachine.SetGumballs(numBalls);
		if (m_gumballMachine.GetGumballCount() > 0)
		{
			if (m_gumballMachine.GetQuarterCount() > 0)
			{
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
	}
private:
    IDoubleGumballMachineContext& m_gumballMachine;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IDoubleGumballMachineContext& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}
	void InsertQuarter() final
	{
		m_gumballMachine.CollectQuarter();
	}
	void EjectQuarters() final
	{
		m_gumballMachine.ReturnQuarters();
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() final
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SpendQuarter();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() final
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const final
	{
		return "waiting for turn of crank";
	}
	void Refill(unsigned numBalls) final
	{
		m_gumballMachine.SetGumballs(numBalls);
	}
private:
    IDoubleGumballMachineContext& m_gumballMachine;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IDoubleGumballMachineContext & gumballMachine)
		: m_gumballMachine(gumballMachine)
	{}
	void InsertQuarter() final
	{
		m_gumballMachine.CollectQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarters() final
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() final
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() final
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const final
	{
		return "waiting for quarter";
	}
	void Refill(unsigned numBalls) final
	{
		m_gumballMachine.SetGumballs(numBalls);
	}
private:
    IDoubleGumballMachineContext& m_gumballMachine;
};

class CDoubleGumballMachine 
    : private IDoubleGumballMachineContext
    , public IDoubleGumballMachine
{
public:
	CDoubleGumballMachine(unsigned ballCount)
		: m_gumballCount(ballCount)
	{
		if (m_gumballCount > 0)
		{
			SetNoQuarterState();
		}
		else
		{
			SetSoldOutState();
		}
	}
	void EjectQuarters() final
	{
		m_currentState->EjectQuarters();
	}
	void InsertQuarter() final
	{
		m_currentState->InsertQuarter();
	}
	void TurnCrank() final
	{
		m_currentState->TurnCrank();
		m_currentState->Dispense();
	}
	std::string ToString()const final
	{
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Coins: %3% 
Machine is %4%
)");
		return (fmt % m_gumballCount % (m_gumballCount != 1 ? "s" : "") % m_coinsCount % m_currentState->ToString()).str();
	}
    void Refill(unsigned numBalls) final
    {
        m_currentState->Refill(numBalls);
    }
private:
    unsigned GetGumballCount() const final
    {
        return m_gumballCount;
    }
    unsigned GetQuarterCount() const final
    {
        return m_coinsCount;
    }
	void SetGumballs(unsigned numBalls) final
	{
		m_gumballCount = numBalls;
        if (m_gumballCount == 0)
        {
            SetSoldOutState();
        }
	}
	void ReleaseGumball() final
	{
		if (m_gumballCount != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_gumballCount;
		}
	}
	void CollectQuarter() final
	{
		if (m_coinsCount < 5)
		{
			++m_coinsCount;
			std::cout << "You inserted a quarter\n";
		}
		else
		{
			std::cout << "You can't add more than 5 coins" << std::endl;
		}
	}
	void SpendQuarter() final
	{
		if (m_coinsCount != 0)
		{
			--m_coinsCount;
		}
	}
	void ReturnQuarters() final
	{
		auto fmt = boost::format("%1% quater%2% returned");
		std::cout <<
			fmt % m_coinsCount % (m_coinsCount == 0 ? "" : "s") << std::endl;
		m_coinsCount = 0;
	}
	void SetSoldOutState() final
	{
		m_currentState.reset(new CSoldOutState(*this));
	}
	void SetNoQuarterState() final
	{
		m_currentState.reset(new CNoQuarterState(*this));
	}
	void SetSoldState() final
	{
		m_currentState.reset(new CSoldState(*this));
	}
	void SetHasQuarterState() final
	{
		m_currentState.reset(new CHasQuarterState(*this));
	}
private:
	unsigned m_gumballCount = 0;
	unsigned m_coinsCount = 0;
	std::unique_ptr<IState> m_currentState;
};
}
