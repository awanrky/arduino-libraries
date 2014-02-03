#ifndef _AISA_DHT_H
#define _AISA_DHT_H

#include <Arduino.h>
#include <DHT.h>

//
//    FILE: dht.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.08
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// see dht.cpp file
// 

// #ifndef dht_h
// #define dht_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define DHT_LIB_VERSION "0.1.08"

#define DHTLIB_OK       0
#define DHTLIB_ERROR_CHECKSUM -1
#define DHTLIB_ERROR_TIMEOUT  -2
#define DHTLIB_INVALID_VALUE  -999

class dht
{
public:
  // int read11(uint8_t pin);
  //   int read21(uint8_t pin);
    int read22(uint8_t pin);

  double humidity;
  double temperature;

private:
  uint8_t bits[5];  // buffer to receive data
  int read(uint8_t pin);
};
// #endif
//
// END OF FILE
//


class aisa_DHT
{
private:
    int pin;                // analog - 10mV / degree C with a 500mV offset (offset to allow for negative temperatures)

    float temperature;
    float humidity;
    String sensorName;

    dht DHT;

public:

    aisa_DHT(String name, int digitalPin);

    int getPin();

    void getReading();

    float getTemperature(bool takeReading = true);
    float getHumidity(bool takeReading = true);

};

#endif