#ifndef _AISA_TMP36_H
#define _AISA_TMP36_H

#include <Arduino.h>

class aisa_TMP36
{
public:
    int pin;                 // analog - 10mV / degree C with a 500mV offset (offset to allow for negative temperatures)
    float suppliedVoltage;   // 3.3 or 5.0 (depending on voltage supplied to sensor)
    int readingDelay;        // takes two readings, with delay in between, to see if readings become more consistent

    int analogReading;

    aisa_TMP36(int analogPin, float voltagePin, int delay);

    void setReading(int reading);
    void takeReading();
    float voltage();
    float celcius();
    float fahrenheit();
    void toSerial();

};

#endif