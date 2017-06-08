#pragma once
#include "IDoubleGumballMachine.h"
#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class CDoubleGumballMachineNaive : public IDoubleGumballMachine
{
public:
	enum class State
	{
		SoldOut,
		NoQuarter,
		HasQuarter,
		Sold
	};

	CDoubleGumballMachineNaive(unsigned ballCount)
		: m_gumballCount(ballCount)
		, m_state(ballCount > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter() final
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			CollectQuarter();
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			CollectQuarter();
			break;
		case State::Sold:
			CollectQuarter();
			break;
		}
	}

	void EjectQuarters() final
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			ReturnQuarters();
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			if (m_quarterCount == 0)
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
			else
			{
				ReturnQuarters();
				m_state = State::NoQuarter;
			}
			break;
		case State::SoldOut:
			if (m_quarterCount == 0)
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
			else
			{
				ReturnQuarters();
			}
			break;
		}
	}

    void TurnCrank() final
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			std::cout << "You turned...\n";
			SpendQuarter();
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}
	void Refill(unsigned numBalls)
	{
		m_gumballCount = numBalls;
        if (m_gumballCount > 0)
        {
            if (m_quarterCount > 0)
            {
                m_state = State::HasQuarter;
            }
            else
            {
                m_state = State::NoQuarter;
            }
        }
        else
        {
            m_state = State::SoldOut;
        }
	}
	std::string ToString()const
	{
		std::string state =
			(m_state == State::SoldOut) ? "sold out" :
			(m_state == State::NoQuarter) ? "waiting for quarter" :
			(m_state == State::HasQuarter) ? "waiting for turn of crank"
			: "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Coins: %3% 
Machine is %4%
)");
        return (fmt % m_gumballCount % (m_gumballCount != 1 ? "s" : "") % m_quarterCount % state).str();
	}

private:
    unsigned GetGumballCount() const
    {
        return m_gumballCount;
    }

    unsigned GetQuarterCount() const
    {
        return m_quarterCount;
    }
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot\n";
			--m_gumballCount;
			if (m_gumballCount == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				m_state = State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
			ReleaseGumball();
			if (m_gumballCount == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else if (m_quarterCount == 0)
			{
				m_state = State::NoQuarter;
			}
			else
			{
				m_state = State::HasQuarter;
			}
			break;
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
			break;
		}
	}
	void CollectQuarter()
	{
		if (m_quarterCount < 5)
		{
			++m_quarterCount;
			std::cout << "You inserted a quarter\n";
		}
		else
		{
			std::cout << "You can't add more than 5 coins" << std::endl;
		}
	}
	void SpendQuarter()
	{
		if (m_quarterCount != 0)
		{
			--m_quarterCount;
		}
	}
    void ReturnQuarters()
    {
        auto fmt = boost::format("%1% quater%2% returned");
        std::cout << fmt % m_quarterCount % (m_quarterCount == 0 ? "" : "s") << std::endl;
        m_quarterCount = 0;
    }
	void ReleaseGumball()
	{
		if (m_gumballCount != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_gumballCount;
		}
	}
	unsigned m_gumballCount;
	unsigned m_quarterCount = 0;
	State m_state = State::SoldOut;
};
}