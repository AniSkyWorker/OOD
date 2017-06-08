#pragma once
#include "../state/NaiveDoubleGumballMachine.h"
#include "../state/DoubleGumballMachineWithState.h"

using namespace naive;
using namespace with_dynamic_state_d;

struct NaiveDoubleGumballMachineFixture
{
    std::unique_ptr<IDoubleGumballMachine> machine;

    NaiveDoubleGumballMachineFixture()
        : machine(std::make_unique<CDoubleGumballMachineNaive>(5))
    {
    }
};

struct DoubleGumballMachineFixture
{
    std::unique_ptr<IDoubleGumballMachine> machine;

    DoubleGumballMachineFixture()
        : machine(std::make_unique<CDoubleGumballMachine>(5))
    {
    }
};

typedef boost::mpl::vector<NaiveDoubleGumballMachineFixture, DoubleGumballMachineFixture> when_no_quarter_can_;

struct naive_when_has_quarter_state_ : NaiveDoubleGumballMachineFixture
{
    naive_when_has_quarter_state_()
    {
        machine->InsertQuarter();
    }
};

struct when_has_quarter_state : DoubleGumballMachineFixture
{
    when_has_quarter_state()
    {
        machine->InsertQuarter();
    }
};

typedef boost::mpl::vector<when_has_quarter_state, naive_when_has_quarter_state_> when_has_quarter_can_;

struct naive_when_sold_out_state_ : NaiveDoubleGumballMachineFixture
{
    naive_when_sold_out_state_()
    {
        machine->InsertQuarter();
        machine->Refill(0);
    }
};

struct when_sold_out_state_ : DoubleGumballMachineFixture
{
    when_sold_out_state_()
    {
        machine->InsertQuarter();
        machine->Refill(0);
    }
};

typedef boost::mpl::vector<naive_when_sold_out_state_, when_sold_out_state_> when_sold_out_can_;
