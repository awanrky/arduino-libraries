#include "aisa_BMP180.h"

aisa_BMP180::aisa_BMP180(String name)
{
	sensorName = name;
	clearErrorState();
	bmp = new Adafruit_BMP085_Unified(10085);

	isInitialized = false;
	if(bmp->begin())
	{
		isInitialized = true;
	}
}

String aisa_BMP180::getSensorName()
{
	return sensorName;
}

float aisa_BMP180::getDegreesCelcius()
{
	float temperature;

	if (!isInitialized) 
	{
		setErrorStateSensorNotFound();
		return -999.999;
	}
	
	bmp->getTemperature(&temperature);
	clearErrorState();
	return temperature;
}

float aisa_BMP180::getHectoPascals()
{
	sensors_event_t event;

	if (!isInitialized)
	{
		setErrorStateSensorNotFound();
		return 0.0;
	}

	bmp->getEvent(&event);

	if (event.pressure)
	{
		clearErrorState();
		return event.pressure;
	}
	setErrorStateSensorError();
	return 0.0;
}

float aisa_BMP180::getAltitudeInMeters(float seaLevelPressure)
{
	float pressure;
	float temperature;

	if (!isInitialized)
	{
		setErrorStateSensorNotFound();
		return 0.0;
	}

	pressure = this->getHectoPascals();
	if (pressure == 0)
	{
		setErrorStateSensorError();
		return -999.999;
	}

	temperature = this->getDegreesCelcius();
	if (temperature < -999)
	{
		setErrorStateSensorError();
		return -999.999;
	}

	clearErrorState();
	return bmp->pressureToAltitude(seaLevelPressure, pressure, temperature);
}

float aisa_BMP180::getAltitudeInMeters()
{
	return this->getAltitudeInMeters(SENSORS_PRESSURE_SEALEVELHPA);
}

int aisa_BMP180::getErrorState()
{
	return errorState;
}

void aisa_BMP180::setErrorStateSensorError()
{
	errorState = AISA_BMP180_ERROR_STATE_SENSOR_ERROR;
}

void aisa_BMP180::setErrorStateSensorNotFound()
{
	errorState = AISA_BMP180_ERROR_STATE_SENSOR_NOT_FOUND;
}

void aisa_BMP180::clearErrorState()
{
	errorState = AISA_BMP180_ERROR_STATE_NONE;
}