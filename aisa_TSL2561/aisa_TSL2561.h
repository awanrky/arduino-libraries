#ifndef _aisa_TSL2561_H_
#define _aisa_TSL2561_H_

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561.h>

class aisa_TSL2561
{
private:

    uint8_t i2cAddress;
    int32_t sensorId;

    Adafruit_TSL2561 * tsl;
    bool initialized;
    sensors_event_t event;

    uint16_t broadband;
    uint16_t infrared;

    void initialize(uint8_t address, int32_t id);
    bool takeLuminosityReading();
    bool takeLuxReading();

public:

    aisa_TSL2561(uint8_t address, int32_t id);
    aisa_TSL2561(uint8_t address);
    aisa_TSL2561();

    bool takeReading();
    int getLux(bool takeReading = true);
    int getInfrared(bool takeReading = true);
    int getBroadband(bool takeReading = true);

};

#endif