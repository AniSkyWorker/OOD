#include "stdafx.h"

using namespace std;

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

struct ISoundBehavior
{
	virtual ~ISoundBehavior() {};
	virtual void Sound() = 0;
};

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};

namespace FlyBehaviorTypes
{
	class CFlyWithWings : public IFlyBehavior
	{
	public:
		CFlyWithWings() : m_flightsCount(0)
		{
		}

		void Fly() override
		{
			cout << "I'm flying with wings!" << endl
				<< "It's my " << ++m_flightsCount << " flight" << endl;
		}

	private:
		size_t m_flightsCount;
	};

	class CFlyNoWay : public IFlyBehavior
	{
	public:
		void Fly() override {}
	};
}

namespace SoundBehaviorTypes
{
	class CQuack : public ISoundBehavior
	{
	public:
		void Sound() override
		{
			cout << "Quack! Quack!" << endl;
		}
	};

	class CSqueak : public ISoundBehavior
	{
	public:
		void Sound() override
		{
			cout << "Squeek!" << endl;
		}
	};

	class CSoundNoWay : public ISoundBehavior
	{
	public:
		void Sound() override {}
	};
}

namespace DanceBehaviorTypes
{
	class CDanceWaltz : public IDanceBehavior
	{
	public:
		void Dance() override
		{
			cout << "I'm dancing waltz!" << endl;
		}
	};

	class CDanceMinuet : public IDanceBehavior
	{
	public:
		void Dance() override
		{
			cout << "I'm dancing minuet!" << endl;
		}
	};

	class CDanceNoWay : public IDanceBehavior
	{
	public:
		void Dance() override {}
	};
}

class CDuck
{
public:
	CDuck(unique_ptr<IFlyBehavior> && flyBehavior,
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
	virtual ~CDuck() {};

private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<ISoundBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(make_unique<FlyBehaviorTypes::CFlyWithWings>(), make_unique<SoundBehaviorTypes::CQuack>(), make_unique<DanceBehaviorTypes::CDanceWaltz>())
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
		: CDuck(make_unique<FlyBehaviorTypes::CFlyWithWings>(), make_unique<SoundBehaviorTypes::CQuack>(), make_unique<DanceBehaviorTypes::CDanceMinuet>())
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
		: CDuck(make_unique<FlyBehaviorTypes::CFlyNoWay>(), make_unique<SoundBehaviorTypes::CSoundNoWay>(), make_unique<DanceBehaviorTypes::CDanceNoWay>())
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
		: CDuck(make_unique<FlyBehaviorTypes::CFlyNoWay>(), make_unique<SoundBehaviorTypes::CSqueak>(), make_unique<DanceBehaviorTypes::CDanceNoWay>())
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
		: CDuck(make_unique<FlyBehaviorTypes::CFlyNoWay>(), make_unique<SoundBehaviorTypes::CQuack>(), make_unique<DanceBehaviorTypes::CDanceNoWay>())
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