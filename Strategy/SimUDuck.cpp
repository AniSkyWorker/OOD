#include "stdafx.h"

using namespace std;

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	FlyWithWings() : m_flightsCount(0)
	{
	}

	void Fly() override
	{
		cout << "I'm flying with wings!" << endl
			<< "It's my "<< ++m_flightsCount << " flight" << endl;
	}

private:
	size_t m_flightsCount;
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};

struct ISoundBehavior
{
	virtual ~ISoundBehavior() {};
	virtual void Sound() = 0;
};

class Quack : public ISoundBehavior
{
public:
	void Sound() override
	{
		cout << "Quack! Quack!" << endl;
	}
};

class Squeak : public ISoundBehavior
{
public:
	void Sound() override
	{
		cout << "Squeek!" << endl;
	}
};

class SoundNoWay : public ISoundBehavior
{
public:
	void Sound() override {}
};

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};

class DanceWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancing waltz!" << endl;
	}
};

class DanceMinuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancing minuet!" << endl;
	}
};

class DanceNoWay : public IDanceBehavior
{
public:
	void Dance() override {}
};

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior> && flyBehavior,
		unique_ptr<ISoundBehavior> && quackBehavior,
		unique_ptr<IDanceBehavior> && danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(move(danceBehavior))
		, m_flyBehavior(move(flyBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		assert(m_flyBehavior);
	}

	void Sound() const
	{
		m_quackBehavior->Sound();
	}

	void Swim() const
	{
		cout << "I'm swimming!" << endl;
	}

	void Fly()
	{
		m_flyBehavior->Fly();
	}

	void Dance() const
	{
		m_danceBehavior->Dance();
	}

	virtual void Display() const = 0;
	virtual ~Duck() {};

private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<ISoundBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<Quack>(), make_unique<DanceWaltz>())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck!" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<Quack>(), make_unique<DanceMinuet>())
	{
	}

	void Display() const override
	{
		cout << "I'm redhead duck!" << endl;
	}
};
class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<SoundNoWay>(), make_unique<DanceNoWay>())
	{
	}

	void Display() const override
	{
		cout << "I'm deckoy duck!" << endl;
	}

};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<Squeak>(), make_unique<DanceNoWay>())
	{
	}

	void Display() const override
	{
		cout << "I'm rubber duck!" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<Quack>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck & duck)
{
	DrawDuck(duck);
	duck.Sound();
	duck.Dance();
	duck.Fly();
	duck.Fly();
}

void main()
{
	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);
	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
}