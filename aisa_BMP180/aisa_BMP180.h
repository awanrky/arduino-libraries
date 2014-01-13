#ifndef _AISA_BMP180_H
#define _AISA_BMP180_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

enum
{
	AISA_BMP180_ERROR_STATE_NONE				= 0,
	AISA_BMP180_ERROR_STATE_SENSOR_NOT_FOUND 	= 1,
	AISA_BMP180_ERROR_STATE_SENSOR_ERROR		= 2
};

class aisa_BMP180
{
private:
	bool isInitialized;

	String sensorName;
	int errorState;

	Adafruit_BMP085_Unified * bmp;

	void setErrorStateSensorError();
	void setErrorStateSensorNotFound();
	void clearErrorState();

public:
	aisa_BMP180(String name);

	String getSensorName();

	float getDegreesCelcius();
	float getHectoPascals();
	float getAltitudeInMeters();
	float getAltitudeInMeters(float seaLevelPressure);

	int getErrorState();

};

#endif