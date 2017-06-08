#include "stdafx.h"
#include "DoubleGumballMachineWithState.h"
#include "NaiveDoubleGumballMachine.h"

using namespace std;

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType & m)
{
	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.EjectQuarters();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarters();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;
	
	m.EjectQuarters();
	cout << m.ToString() << endl;
}

void TestGumballMachineWithState()
{
	with_dynamic_state_d::CDoubleGumballMachine m(5);
	TestGumballMachine(m);
}
void TestNaiveGumballMachine()
{
	naive::CDoubleGumballMachineNaive m(5);
	TestGumballMachine(m);
}


int main()
{
	TestNaiveGumballMachine();
	cout << "\n-----------------\n";
	TestGumballMachineWithState();

}