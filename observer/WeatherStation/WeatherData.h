#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		cout << "Current Temperature " << data.temperature << endl;
		cout << "Current Humidity " << data.humidity << endl;
		cout << "Current Pressure " << data.pressure << endl;
		cout << "----------------------------------------" << endl;
	}
};

class CWeatherStatistic
{

public:
	CWeatherStatistic(std::string const& statisticName)
		: m_minValue(std::numeric_limits<double>::infinity())
		, m_maxValue(-std::numeric_limits<double>::infinity())
		, m_accValue(0)
		, m_countAcc(0)
		, m_statisticName(statisticName)
	{
	}

	void Update(double const& newValue)
	{
		if (m_minValue > newValue)
		{
			m_minValue = newValue;
		}
		if (m_maxValue < newValue)
		{
			m_maxValue = newValue;
		}

		m_accValue += newValue;
		++m_countAcc;
	}

	void PrintStatistics() const
	{
		cout << "[" << m_statisticName << "]" << endl;
		cout << "Max: " << m_maxValue << endl;
		cout << "Min: "  << m_minValue << endl;
		cout << "Average: " << m_accValue / m_countAcc << endl;
		cout << "----------------------------------------" << endl;
	}

private:
	double m_minValue;
	double m_maxValue;
	double m_accValue;
	unsigned m_countAcc;
	std::string m_statisticName;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
		: m_temperatureStat("Temperature")
		, m_humidityStat("Humidity")
		, m_pressureStat("Pressure")
	{
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStat.Update(data.temperature);
		m_humidityStat.Update(data.humidity);
		m_pressureStat.Update(data.pressure);

		m_temperatureStat.PrintStatistics();
		m_humidityStat.PrintStatistics();
		m_pressureStat.PrintStatistics();
	}

	CWeatherStatistic m_temperatureStat;
	CWeatherStatistic m_humidityStat;
	CWeatherStatistic m_pressureStat;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature()const
	{
		return m_temperature;
	}

	double GetHumidity()const
	{
		return m_humidity;
	}

	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
