#ifndef _aisa_TSL2561_H_
#define _aisa_TSL2561_H_

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561.h>

class aisa_TSL2561
{
public:
	uint8_t	i2cAddress;
	int32_t	sensorId;

	Adafruit_TSL2561 * tsl;
    bool initialized;
    sensors_event_t event;

    uint16_t broadband;
    uint16_t infrared;

    aisa_TSL2561(uint8_t address, int32_t id);
    aisa_TSL2561(uint8_t address);
    aisa_TSL2561();

    bool takeReading();
    int getLux();
    int getInfrared();
    int getBroadband();
    void toSerial();

private:
	void initialize(uint8_t address, int32_t id);
	void getLuminosity();

};

#endif