

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561.h>

#include "aisa_TSL2561.h"

void aisa_TSL2561::initialize(uint8_t address, int32_t id)
{
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

void aisa_TSL2561::getLuminosity()
{
    broadband = 0;
    infrared = 0;

    tsl->getLuminosity(&broadband, &infrared);
}

aisa_TSL2561::aisa_TSL2561(uint8_t address, int32_t id)
{
    initialize(address, id);
}

aisa_TSL2561::aisa_TSL2561(uint8_t address)
{
    initialize(address, 2112);
}

aisa_TSL2561::aisa_TSL2561()
{
    initialize(TSL2561_ADDR_FLOAT, 2112);
}

bool aisa_TSL2561::takeReading()
{
    if(!initialized) { return false; }
    tsl->getEvent(&event);
}

int aisa_TSL2561::getLux()
{
    return event.light;
}

int aisa_TSL2561::getInfrared()
{
    getLuminosity();
    return infrared;
}

int aisa_TSL2561::getBroadband()
{
    getLuminosity();
    return broadband;
}

void aisa_TSL2561::toSerial()
{
    Serial.print("TSL2561--Lux: ");
    Serial.print(getLux());
    Serial.print(", Broadband: ");
    Serial.print(getBroadband());
    Serial.print(", Infrared: ");
    Serial.print(getInfrared());
    Serial.println(".");
}