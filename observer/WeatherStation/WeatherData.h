﻿#pragma once
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
	void Update(SWeatherInfo const& data, std::string const& stationName) override
	{
		stationName.empty() ? cout << "[Nameless station]" : cout << "[" << stationName << "]";
		cout << endl;
		cout << "Current Temperature " << data.temperature << endl;
		cout << "Current Humidity " << data.humidity << endl;
		cout << "Current Pressure " << data.pressure << endl;
		cout << "----------------------------------------" << endl;
	}
};

class CWeatherStatistic
{

public:
	CWeatherStatistic()
		: m_minValue(std::numeric_limits<double>::infinity())
		, m_maxValue(-std::numeric_limits<double>::infinity())
		, m_accValue(0)
		, m_countAcc(0)
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

	void PrintStatistics(string const& statisticName) const
	{
		cout << "[" << statisticName << "]" << endl;
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
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data, std::string const& stationName) override
	{

		m_temperatureStat.Update(data.temperature);
		m_humidityStat.Update(data.humidity);
		m_pressureStat.Update(data.pressure);

		stationName.empty() ? cout << "[Nameless station]" : cout << "[" << stationName << "]";
		cout << endl;

		m_temperatureStat.PrintStatistics("Temperature");
		m_humidityStat.PrintStatistics("Humidity");
		m_pressureStat.PrintStatistics("Pressure");
	}

	CWeatherStatistic m_temperatureStat;
	CWeatherStatistic m_humidityStat;
	CWeatherStatistic m_pressureStat;

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string stationName = "") : CObservable(stationName)
	{
	}

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