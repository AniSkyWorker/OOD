#include "WeatherData.h"

int main()
{
	CWeatherData wd("in");

	CDisplay display;
	wd.RegisterObserver(display, 10);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 100);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay, 100);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	return 0;
}