#include "stdafx.h"

using namespace std;
typedef std::function<void()> Behavior;

namespace FlyBehaviorTypes
{

Behavior FlyWithWings()
{
	int flightCount = 0;
	return [flightCount]() mutable {
		cout << "I'm flying with wings!" << endl
			<< "It's my " << ++flightCount << " flight" << endl;
	};
}

void FlyNoWay()
{
}

}

namespace SoundBehaviorTypes
{

void Quack()
{
	cout << "Quack! Quack!" << endl;
}
void Squeak()
{
	cout << "Squeek!" << endl;
}

void SoundNoWay()
{
}

}

namespace DanceBehaviorTypes
{

void DanceWaltz()
{
	cout << "I'm dancing waltz!" << endl;
}

void DanceMinuet()
{
	cout << "I'm dancing minuet!" << endl;
}
	
void DanceNoWay()
{
}

}

class CDuck
{
public:
	CDuck(Behavior const& flyBehavior,
		Behavior const& quackBehavior,
		Behavior const& danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
		, m_flyBehavior(flyBehavior)
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		assert(m_flyBehavior);
	}

	void Sound() const
	{
		m_quackBehavior();
	}

	void Swim() const
	{
		cout << "I'm swimming!" << endl;
	}

	void Fly()
	{
		m_flyBehavior();
	}

	void Dance() const
	{
		m_danceBehavior();
	}

	virtual void Display() const = 0;
	virtual ~CDuck() {};

private:
	Behavior m_flyBehavior;
	Behavior m_quackBehavior;
	Behavior m_danceBehavior;
};

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(FlyBehaviorTypes::FlyWithWings(), SoundBehaviorTypes::Quack, DanceBehaviorTypes::DanceWaltz)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck!" << endl;
	}
};

class CRedheadDuck : public CDuck
{
public:
	CRedheadDuck()
		: CDuck(FlyBehaviorTypes::FlyWithWings(), SoundBehaviorTypes::Quack, DanceBehaviorTypes::DanceMinuet)
	{
	}

	void Display() const override
	{
		cout << "I'm redhead duck!" << endl;
	}
};

class CDeckoyDuck : public CDuck
{
public:
	CDeckoyDuck()
		: CDuck(FlyBehaviorTypes::FlyNoWay, SoundBehaviorTypes::SoundNoWay, DanceBehaviorTypes::DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm deckoy duck!" << endl;
	}
};

class CRubberDuck : public CDuck
{
public:
	CRubberDuck()
		: CDuck(FlyBehaviorTypes::FlyNoWay, SoundBehaviorTypes::Squeak, DanceBehaviorTypes::DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm rubber duck!" << endl;
	}
};

class CModelDuck : public CDuck
{
public:
	CModelDuck()
		: CDuck(FlyBehaviorTypes::FlyNoWay, SoundBehaviorTypes::Quack, DanceBehaviorTypes::DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(CDuck const& duck)
{
	duck.Display();
}

void PlayWithDuck(CDuck & duck)
{
	DrawDuck(duck);
	duck.Sound();
	duck.Dance();
	duck.Fly();
	duck.Fly();
}

void main()
{
	CMallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);
	CRedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	CRubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	CDeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	CModelDuck modelDuck;
	PlayWithDuck(modelDuck);
}