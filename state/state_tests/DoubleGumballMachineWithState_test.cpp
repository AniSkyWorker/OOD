#include "stdafx.h"
#include "DoubleGumballFixtures.h"

void CheckMachineStateCorrectness(IDoubleGumballMachine& machine, unsigned expectedCoins, unsigned expectedBalls, std::string state)
{
    auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Coins: %3% 
Machine is %4%
)");
    BOOST_CHECK_EQUAL(machine.ToString(), (fmt % expectedBalls % (expectedBalls != 1 ? "s" : "") % expectedCoins % state).str());
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(has_coins_and_balls_by_init, T, when_no_quarter_can_, T)
{
    CheckMachineStateCorrectness(*machine, 0, 5, "waiting for quarter");
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(eject_all_coins, T, when_has_quarter_can_, T)
{
    CheckMachineStateCorrectness(*machine, 1, 5, "waiting for turn of crank");
	machine->EjectQuarters();
    CheckMachineStateCorrectness(*machine, 0, 5, "waiting for quarter");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(insert_quarters_while_coins_count_less_than_5, T, when_has_quarter_can_, T)
{
	for (unsigned i = 0; i < 10; ++i)
	{
		machine->InsertQuarter();
	}
    CheckMachineStateCorrectness(*machine, 5, 5, "waiting for turn of crank");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(turn_crank_and_use_1_quarter, T, when_has_quarter_can_, T)
{
	machine->TurnCrank();
    CheckMachineStateCorrectness(*machine, 0, 4, "waiting for quarter");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(be_refilled, T, when_has_quarter_can_, T)
{
	machine->Refill(4);
    CheckMachineStateCorrectness(*machine, 1, 4, "waiting for turn of crank");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(not_insert_quarter, T, when_sold_out_can_, T)
{
    CheckMachineStateCorrectness(*machine, 1, 0, "sold out");
    machine->InsertQuarter();
    CheckMachineStateCorrectness(*machine, 1, 0, "sold out");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(eject_all_quarters, T, when_sold_out_can_, T)
{
    machine->EjectQuarters();
    CheckMachineStateCorrectness(*machine, 0, 0, "sold out");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(turn_crank, T, when_sold_out_can_, T)
{
    machine->TurnCrank();
    CheckMachineStateCorrectness(*machine, 1, 0, "sold out");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(insert_quarter, T, when_no_quarter_can_, T)
{
    CheckMachineStateCorrectness(*machine, 0, 5, "waiting for quarter");
	machine->InsertQuarter();
    CheckMachineStateCorrectness(*machine, 1, 5, "waiting for turn of crank");

}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(eject_quarter_and_nothing_happened, T, when_no_quarter_can_, T)
{
    CheckMachineStateCorrectness(*machine, 0, 5, "waiting for quarter");
	machine->EjectQuarters();
    CheckMachineStateCorrectness(*machine, 0, 5, "waiting for quarter");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(turn_crank_and_nothing_happened, T, when_no_quarter_can_, T)
{
	machine->TurnCrank();
    CheckMachineStateCorrectness(*machine, 0, 5, "waiting for quarter");
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(be_refilled_and_quarter_count_not_changes, T, when_no_quarter_can_, T)
{
	machine->Refill(4);
    CheckMachineStateCorrectness(*machine, 0, 4, "waiting for quarter");
}