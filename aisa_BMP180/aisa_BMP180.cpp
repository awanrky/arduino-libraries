#include "aisa_BMP180.h"

aisa_BMP180::aisa_BMP180(String name)
{
	sensorName = name;
	bmp = new Adafruit_BMP085_Unified(10085);

	isInitialized = false;
	if(bmp->begin())
	{
		isInitialized = true;
	}
}


float aisa_BMP180::getTemperature()
{
	float temperature;

	if (!isInitialized) 
	{
		return -999.999;
	}
	
	bmp->getTemperature(&temperature);
	return temperature;
}

float aisa_BMP180::getBarometricPressure()
{
	sensors_event_t event;

	if (!isInitialized)
	{
		return 0.0;
	}

	bmp->getEvent(&event);

	if (event.pressure)
	{
		return event.pressure;
	}
	return 0.0;
}

float aisa_BMP180::getAltitude(float seaLevelPressure)
{
	float pressure;
	float temperature;

	pressure = this->getBarometricPressure();
	if (pressure == 0)
	{
		return -999.999;
	}

	temperature = this->getTemperature();
	if (temperature < -999)
	{
		return -999.999;
	}

	return bmp->pressureToAltitude(seaLevelPressure, pressure, temperature);
}

float aisa_BMP180::getAltitude()
{
	return this->getAltitude(SENSORS_PRESSURE_SEALEVELHPA);
}

String aisa_BMP180::getErrorState()
{
	if (isInitialized)
	{
		return "Sensor Error";
	}
	return "Sensor Not Found";
}