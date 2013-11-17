#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561.h>

#include "aisa_TSL2561.h"

aisa_TSL2561::aisa_TSL2561(String name, uint8_t address, int32_t id)
{
    initialize(name, address, id);
}

aisa_TSL2561::aisa_TSL2561(String name, uint8_t address)
{
    initialize(name, address, 2112);
}

aisa_TSL2561::aisa_TSL2561(String name)
{
    initialize(name, TSL2561_ADDR_FLOAT, 2112);
}

String aisa_TSL2561::getPinName()
{
    char * buffer = "dxxxxx";
    sprintf(buffer, "%d", (int)i2cAddress);
    return buffer;
}

String aisa_TSL2561::getSensorName()
{
    return sensorName;
}

int aisa_TSL2561::getSensorId()
{
    return sensorId;
}

bool aisa_TSL2561::takeReading()
{
    return this->takeLuxReading() && this->takeLuminosityReading();   
}

int aisa_TSL2561::getLux(bool takeReading)
{
    if (takeReading)
    {
        this->takeLuxReading();
    }
    return event.light;
}

int aisa_TSL2561::getInfrared(bool takeReading)
{
    if (takeReading)
    {
        this->takeLuminosityReading();
    }
    return infrared;
}

int aisa_TSL2561::getBroadband(bool takeReading)
{
    if (takeReading)
    {
        this->takeLuminosityReading();
    }
    return broadband;
}

void aisa_TSL2561::initialize(String name, uint8_t address, int32_t id)
{
    sensorName = name;
    i2cAddress = address;
    sensorId = id;
    tsl = new Adafruit_TSL2561(address, id);

    /* You can also manually set the gain or enable auto-gain support */
    // tsl->setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
    // tsl->setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
    tsl->enableAutoGain(true);          /* Auto-gain ... switches automatically between 1x and 16x */

    /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
    tsl->setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
//        tsl->setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
//        tsl->setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

    initialized = false;
    if(tsl->begin())
    {
        initialized = true;
    }
}

bool aisa_TSL2561::takeLuminosityReading()
{
    if(!initialized) { return false; }
    broadband = 0;
    infrared = 0;

    tsl->getLuminosity(&broadband, &infrared);
    return true;
}

bool aisa_TSL2561::takeLuxReading()
{
    if(!initialized) { return false; }
    tsl->getEvent(&event);
    return true;
}