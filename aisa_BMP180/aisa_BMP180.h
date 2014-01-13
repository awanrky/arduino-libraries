#ifndef _AISA_BMP180_H
#define _AISA_BMP180_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

class aisa_BMP180
{
private:
	bool isInitialized;

	String sensorName;

	Adafruit_BMP085_Unified * bmp;

public:
	aisa_BMP180(String name);

	float getTemperature();
	float getBarometricPressure();
	float getAltitude();
	float getAltitude(float seaLevelPressure);

	String getErrorState();

};

#endif