#ifndef _AISA_TMP36_H
#define _AISA_TMP36_H

#include <Arduino.h>

class aisa_TMP36
{
private:
    int pin;                 // analog - 10mV / degree C with a 500mV offset (offset to allow for negative temperatures)
    float suppliedVoltage;   // 3.3 or 5.0 (depending on voltage supplied to sensor)
    int readingDelay;        // takes two readings, with delay in between, to see if readings become more consistent

    int analogReading;
    float voltage;

public:
    aisa_TMP36(int analogPin, float voltagePin, int delay);

    void takeReading();

    int getPin();
    float getSuppliedVoltage();

    void setReadingDelay(int delay);
    int getReadingDelay();

    float getVoltage(bool takeReading = true);
    float getCelcius(bool takeReading = true);

};

#endif