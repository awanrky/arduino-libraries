#ifndef _AISA_DHT_H
#define _AISA_DHT_H

#include <Arduino.h>
#include <DHT.h>

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 85

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

class DHT {
 private:
  uint8_t data[6];
  uint8_t _pin, _type, _count;
  boolean read(void);
  unsigned long _lastreadtime;
  boolean firstreading;

 public:
  DHT(uint8_t pin, uint8_t type, uint8_t count=6);
  void begin(void);
  float readTemperature(bool S=false);
  float convertCtoF(float);
  float readHumidity(void);

};

class aisa_DHT
{
private:
    int pin;                // analog - 10mV / degree C with a 500mV offset (offset to allow for negative temperatures)
    int dhtType;            // DHT11, DHT22, DHT21, AM2301

    float temperature;
    float humidity;
  String sensorName;

    DHT * dht;

public:

    aisa_DHT(String name, int digitalPin, int type);

    int getPin();
    int getDhtType();

    void takeReading();

    float getTemperature(bool takeReading = true);
    float getHumidity(bool takeReading = true);
  String getPinName();
  String getSensorName();

};

#endif