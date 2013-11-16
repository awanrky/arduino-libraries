#include "aisa_TMP36.h"

aisa_TMP36::aisa_TMP36(int analogPin, float voltagePin, int delay)
{
    pin = analogPin;
    suppliedVoltage = voltagePin;
    readingDelay = delay;
}

void aisa_TMP36::takeReading()
{    
    analogReading = analogRead(pin);
    delay(readingDelay);
    analogReading = analogRead(pin);
    voltage = analogReading * suppliedVoltage / 1024.0;
}

int aisa_TMP36::getPin()
{
    return pin;
}

float aisa_TMP36::getSuppliedVoltage()
{
    return suppliedVoltage;
}

void aisa_TMP36::setReadingDelay(int delay)
{
    readingDelay = delay;
}

int aisa_TMP36::getReadingDelay()
{
    return readingDelay;
}

float aisa_TMP36::getVoltage(bool takeReading)
{
    if (takeReading)
    {
        this->takeReading();
    }
    return voltage;
}

float aisa_TMP36::getCelcius(bool takeReading)
{
    return (this->getVoltage(takeReading) - 0.5) * 100;
}

// float aisa_TMP36::fahrenheit()
// {
//     return (celcius() * 9.0 / 5.0) + 32.0;
// }

