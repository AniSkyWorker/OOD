#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{

	}

	double GetCost() const override 
	{
		return 60; 
	}
};

enum class CoffeePortions
{
	Double,
	Classic
};

namespace CoffeeType 
{

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(CoffeePortions const& portion = CoffeePortions::Classic)
		: CCoffee("Capuccino")
		, m_portion(portion)
	{}

	double GetCost() const override
	{
		return m_portion == CoffeePortions::Double ? 120 : 80;
	}

private:
	CoffeePortions m_portion;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortions const& portion = CoffeePortions::Classic)
		:CCoffee("Latte")
		, m_portion(portion)
	{}

	double GetCost() const override
	{
		return m_portion == CoffeePortions::Double ? 130 : 90;
	}

	CoffeePortions m_portion;
};

}

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 30;
	}
};

namespace TeaType
{

class CPuer : public CTea
{
public:
	CPuer()
		: CTea("Puer")
	{}
};

class СRedTea : public CTea
{
public:
	СRedTea()
		: CTea("Red tea")
	{}
};

class CBlackTea : public CTea
{
public:
	CBlackTea()
		: CTea("Black tea")
	{}
};

class CGreenTea : public CTea
{
public:
	CGreenTea()
		: CTea("Green tea")
	{}
};

}

enum class MilkshakePortions
{
	Small,
	Medium,
	Large
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortions const& portion = MilkshakePortions::Medium)
		: CBeverage("Milkshake")
		, m_portion(portion)
	{}

	double GetCost() const override 
	{ 
		return (m_portion == MilkshakePortions::Small) ? 50 : ((m_portion == MilkshakePortions::Medium) ? 60 : 80);
	}

	MilkshakePortions m_portion;
};
