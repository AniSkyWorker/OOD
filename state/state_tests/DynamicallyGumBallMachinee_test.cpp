#include "stdafx.h"
#include "../state/GumBallMachineWithDynamicallyCreatedState.h"

using namespace with_dynamic_state;

void CheckMachineStateCorrectness(CGumballMachine& machine, unsigned expectedBalls, std::string state)
{
    auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
    BOOST_CHECK_EQUAL(machine.ToString(), (fmt % expectedBalls % (expectedBalls != 1 ? "s" : "") % state).str());
}

struct GumBallMachineWithDynamicallyCreatedStateFixture
{
	CGumballMachine machine;

	GumBallMachineWithDynamicallyCreatedStateFixture()
		: machine(5)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(GumBallMachineWithDynamicallyCreatedState, GumBallMachineWithDynamicallyCreatedStateFixture)

    struct when_has_quarter_state_can : GumBallMachineWithDynamicallyCreatedStateFixture
    {
    when_has_quarter_state_can()
	    {
		    machine.InsertQuarter();
	    }
    };

    BOOST_FIXTURE_TEST_SUITE(when_has_quarter_state_can_, when_has_quarter_state_can)
        BOOST_AUTO_TEST_CASE(eject_all_quarters)
        {
	        machine.EjectQuarter();
            CheckMachineStateCorrectness(machine, 5, "waiting for quarter");
        }
        BOOST_AUTO_TEST_CASE(not_insert_quarters)
        {
	        machine.InsertQuarter();
            CheckMachineStateCorrectness(machine, 5, "waiting for turn of crank");
        }
        BOOST_AUTO_TEST_CASE(turn_crank_and_use_quarter)
        {
	        machine.TurnCrank();
            CheckMachineStateCorrectness(machine, 4, "waiting for quarter");
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(when_no_quarter_state_can_)
        BOOST_AUTO_TEST_CASE(insert_quarter)
        {
	        machine.InsertQuarter();
            CheckMachineStateCorrectness(machine, 5, "waiting for turn of crank");
        }
        BOOST_AUTO_TEST_CASE(eject_quarter_and_nothing_happened)
        {
	        machine.EjectQuarter();
            CheckMachineStateCorrectness(machine, 5, "waiting for quarter");
        }
        BOOST_AUTO_TEST_CASE(turn_crank_and_nothing_happened)
        {
            CheckMachineStateCorrectness(machine, 5, "waiting for quarter");
	        machine.TurnCrank();
            CheckMachineStateCorrectness(machine, 5, "waiting for quarter");
        }
    BOOST_AUTO_TEST_SUITE_END()

    struct when_sold_out_state_can : GumBallMachineWithDynamicallyCreatedStateFixture
    {
	    when_sold_out_state_can()
	    {
		    for (unsigned i = 0; i < 5; ++i)
		    {
			    machine.InsertQuarter();
			    machine.TurnCrank();
		    }
	    }
    };

    BOOST_FIXTURE_TEST_SUITE(when_sold_out_state_can_, when_sold_out_state_can)
        BOOST_AUTO_TEST_CASE(insert_quarter)
        {
	        machine.InsertQuarter();
            CheckMachineStateCorrectness(machine, 0, "sold out");
        }
        BOOST_AUTO_TEST_CASE(eject_quarter)
        {
	        machine.EjectQuarter();
            CheckMachineStateCorrectness(machine, 0, "sold out");
        }
        BOOST_AUTO_TEST_CASE(not_turn_crank)
        {
	        machine.TurnCrank();
            CheckMachineStateCorrectness(machine, 0, "sold out");
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()