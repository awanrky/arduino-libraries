#include "aisa_TMP36.h"

aisa_TMP36::aisa_TMP36(int analogPin, float voltagePin, int delay)
{
    pin = analogPin;
    suppliedVoltage = voltagePin;
    readingDelay = delay;
}

void aisa_TMP36::setReading(int reading)
{
    analogReading = reading;
}

void aisa_TMP36::takeReading()
{
    analogReading = analogRead(pin);
    delay(readingDelay);
    analogReading = analogRead(pin);
}

float aisa_TMP36::voltage()
{
    return analogReading * suppliedVoltage / 1024.0;
}

float aisa_TMP36::celcius()
{
    return (voltage() - 0.5) * 100;
}

float aisa_TMP36::fahrenheit()
{
    return (celcius() * 9.0 / 5.0) + 32.0;
}

void aisa_TMP36::toSerial()
{
    Serial.print("TMP36--volts: ");
    Serial.print(voltage());
    Serial.print(", Degrees C: ");
    Serial.print(celcius());
    Serial.print(", Degrees Fahreinheit: ");
    Serial.print(fahrenheit());
    Serial.println(".");
}
